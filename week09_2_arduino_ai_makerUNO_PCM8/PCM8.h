/*
 * PCM8 — 在「任意腳位」播放 8-bit / 8000 Hz PCM 音效（預設 pin 8 = MakerUNO 蜂鳴器）
 *
 * 改寫自 Michael Smith / David Mellis 的 PCM 函式庫。
 * 原版用 Timer2 的硬體 PWM，只能從 pin 11 (OC2A) 輸出。
 * 本版改成「用計時器中斷模擬 PWM」：
 *   - Timer1 以 62.5 kHz 跑 8-bit Fast PWM，但不接任何腳位
 *       溢位中斷  → 把輸出腳拉 HIGH
 *       比較中斷  → 把輸出腳拉 LOW
 *     兩個中斷之間的時間 = 脈寬 = 樣本值，效果等同硬體 PWM
 *   - Timer2 以 8 kHz 換下一個樣本
 *   使用的中斷向量和 tone() / Servo 不重複，同一個程式裡可以同時呼叫 tone()（但不能同時發聲）
 *   兩個中斷都用 naked ISR + 單一 sbi/cbi 指令，每次只花約 13 個時脈，
 *   總共約佔 CPU 10%。
 *
 * 播放期間 Timer1、Timer2 被佔用：tone()、Servo、pin 3/9/10/11 的 analogWrite 不能用。
 * （Servo 函式庫會長期佔用 Timer1，不建議和 PCM8 一起用）
 * 播完 (或 pcm8Stop) 後會把兩個計時器還原成 Arduino 預設值，tone() 等就能再用。
 */
#ifndef PCM8_H
#define PCM8_H

#include <Arduino.h>

// ===== 輸出腳位設定：要換腳位就改這三行 =====
// pin 8  = PORTB, DDRB, 0      pin 12 = PORTB, DDRB, 4
// pin 2  = PORTD, DDRD, 2      pin 7  = PORTD, DDRD, 7
// pin A0 = PORTC, DDRC, 0      （UNO 上每個數位腳都可以）
#define PCM8_PORT PORTB
#define PCM8_DDR  DDRB
#define PCM8_BIT  0

// 設為 1 會在播放期間暫停 millis() 的中斷，可以消除約 1 kHz 的細微雜音，
// 但播放中 millis()、delay() 會停住（播完自動恢復）。
#define PCM8_PAUSE_MILLIS 0

#define PCM8_SAMPLE_RATE 8000

#ifdef __cplusplus
extern "C" {
#endif

// data：PROGMEM 中的 unsigned 8-bit 樣本；len：樣本數
void pcm8Play(const unsigned char *data, unsigned int len);
void pcm8Stop(void);
bool pcm8IsPlaying(void);
void pcm8SetVolume(uint8_t vol);   // 0~255，預設 255

#ifdef __cplusplus
}
#endif

#endif
