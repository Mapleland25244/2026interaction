#include "PCM8.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// 脈寬限制在 16~239：
// 溢位和比較中斷至少要相隔約 13 個時脈，太靠近 0 或 255 時兩個中斷會撞在一起，
// 造成整個週期反相的爆音，所以兩端各留 16 的餘裕。
#define DUTY_MIN   16
#define DUTY_RANGE 224          // DUTY_MIN + 223 = 239

static const unsigned char *pcmData;
static volatile unsigned int pcmLen;
static volatile unsigned int pcmPos;
static volatile bool    playing = false;
static volatile uint8_t volume  = 255;
static volatile uint8_t rampLevel;   // 開頭淡入用
static volatile uint8_t lastDuty;    // 結尾淡出用
static volatile uint8_t phase;       // 0 = 淡入, 1 = 播放, 2 = 淡出

static inline uint8_t toDuty(uint8_t s) {
  int16_t v = (int16_t)s - 128;
  v = (v * (int16_t)volume) >> 8;
  v += 128;
  return DUTY_MIN + (uint8_t)(((uint16_t)v * DUTY_RANGE) >> 8);
}

// ---- 模擬 PWM：只有一條 sbi / cbi 指令，不動到 SREG，所以可以用 naked ISR ----
ISR(TIMER1_OVF_vect, ISR_NAKED) {
  asm volatile("sbi %0, %1 \n\t reti"
               :: "I"(_SFR_IO_ADDR(PCM8_PORT)), "I"(PCM8_BIT));
}

ISR(TIMER1_COMPB_vect, ISR_NAKED) {
  asm volatile("cbi %0, %1 \n\t reti"
               :: "I"(_SFR_IO_ADDR(PCM8_PORT)), "I"(PCM8_BIT));
}

// ---- 8 kHz 換樣本（Timer2 COMPB；Arduino 的 tone() 用的是 COMPA，所以不衝突）----
// ISR_NOBLOCK：一進來就重新開中斷，讓上面兩個 PWM 中斷可以插隊，避免脈寬抖動
ISR(TIMER2_COMPB_vect, ISR_NOBLOCK) {
  if (phase == 1) {
    unsigned int pos = pcmPos;
    if (pos < pcmLen) {
      uint8_t d = toDuty(pgm_read_byte(pcmData + pos));
      OCR1B = d;
      lastDuty = d;
      pcmPos = pos + 1;
    } else {
      phase = 2;
    }
  } else if (phase == 0) {             // 從靜音慢慢升到第一個樣本，減少開頭的「啪」
    uint8_t target = toDuty(pgm_read_byte(pcmData));
    if (rampLevel < target) OCR1B = ++rampLevel;
    else phase = 1;
  } else {                             // 慢慢降回靜音，減少結尾的「啪」
    if (lastDuty > DUTY_MIN) OCR1B = --lastDuty;
    else pcm8Stop();
  }
}

#if PCM8_PAUSE_MILLIS
static uint8_t savedTIMSK0;
#endif

void pcm8Play(const unsigned char *data, unsigned int len) {
  if (len == 0) return;
  pcm8Stop();
  cli();

  pcmData   = data;
  pcmLen    = len;
  pcmPos    = 0;
  rampLevel = DUTY_MIN;
  lastDuty  = DUTY_MIN;
  phase     = 0;

  PCM8_PORT &= ~_BV(PCM8_BIT);
  PCM8_DDR  |=  _BV(PCM8_BIT);

  // Timer1：8-bit Fast PWM (mode 5)、不接 OC1A/OC1B 腳、不除頻 → 16 MHz / 256 = 62.5 kHz
  TCCR1A  = _BV(WGM10);
  TCCR1B  = _BV(WGM12) | _BV(CS10);
  OCR1B   = DUTY_MIN;
  TCNT1   = 0;
  TIFR1   = _BV(OCF1B) | _BV(TOV1);
  TIMSK1  = _BV(OCIE1B) | _BV(TOIE1);

  // Timer2：CTC、除 8、計 250 → 16 MHz / 8 / 250 = 8 kHz
  ASSR   &= ~(_BV(EXCLK) | _BV(AS2));
  TCCR2A  = _BV(WGM21);
  TCCR2B  = _BV(CS21);
  OCR2A   = F_CPU / 8 / PCM8_SAMPLE_RATE - 1;
  OCR2B   = 0;
  TCNT2   = 0;
  TIFR2   = _BV(OCF2B);
  TIMSK2  = _BV(OCIE2B);

#if PCM8_PAUSE_MILLIS
  savedTIMSK0 = TIMSK0;
  TIMSK0 &= ~_BV(TOIE0);
#endif

  playing = true;
  sei();          // 播放靠中斷進行，一定要開
}

void pcm8Stop(void) {
  uint8_t oldSREG = SREG;
  cli();

  TIMSK1 &= ~(_BV(OCIE1B) | _BV(TOIE1));
  TIMSK2 &= ~_BV(OCIE2B);
  PCM8_PORT &= ~_BV(PCM8_BIT);

  if (playing) {
    // 還原成 Arduino 開機時的設定，讓 tone()、analogWrite() 播完後能正常使用
    TCCR1A = _BV(WGM10);
    TCCR1B = _BV(CS11) | _BV(CS10);
    TCCR2A = _BV(WGM20);
    TCCR2B = _BV(CS22);
#if PCM8_PAUSE_MILLIS
    TIMSK0 = savedTIMSK0;
#endif
  }
  playing = false;
  SREG = oldSREG;
}

bool pcm8IsPlaying(void) {
  return playing;
}

void pcm8SetVolume(uint8_t vol) {
  volume = vol;
}
