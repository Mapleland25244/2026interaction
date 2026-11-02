// week09_2_arduino_ai_makerUNO_PCM8
// Q5: 可以讓聲音再更大聲嗎？
// A5: 新版 wav2pcm.py 加了 --max 響度增強，範例鈴聲大約大聲 7 dB；要大聲很多，就得外接擴大板和喇叭。
/*
 * MakerUNO：用板上蜂鳴器 (pin 8) 播放 PCM 音效
 *  - 按下板上按鈕 (D2) 播放一次音效
 *  - 同一個資料夾內要有：PCM8.h、PCM8.cpp、sound.h（由 wav2pcm.py 產生）
 *  - 不需要安裝任何函式庫
 *  - 記得把 MakerUNO 的蜂鳴器開關切到 ON
 */
#include "PCM8.h"
#include "sound.h"

const int BUTTON_PIN = 2;     // MakerUNO 內建按鈕，按下為 LOW

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pcm8SetVolume(255);                 // 0~255
  pcm8Play(sample, sample_len);       // 開機先播一次
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW && !pcm8IsPlaying()) {
    pcm8Play(sample, sample_len);

    while (digitalRead(BUTTON_PIN) == LOW);   // 等放開按鈕
    delay(50);                                // 簡單防彈跳
  }

  // 播放是在背景用中斷進行的，這裡可以做別的事
  // 例如播完後接一段 tone()：
  //   if (!pcm8IsPlaying()) { tone(8, 1000, 100); }
}
