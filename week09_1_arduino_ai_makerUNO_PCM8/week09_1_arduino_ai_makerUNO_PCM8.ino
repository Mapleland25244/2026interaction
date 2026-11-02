// week09_1_arduino_ai_makerUNO_PCM8
// 想要讓 MakerUNO 發出更多元的聲音，不要只是用單調的 tone()
// 老師要示範，用 AI 一步步找出答案
// Q1: MakerUNO 本身可以用 pin 8 的 buzzer 利用 tone() 來發出單調的聲音。
// 有辦法發出比較精彩的聲音嗎? ex. wav or mp3
// (註: 老師教 AI 要10問10答、百問百答，所以現在要一步步練習問、互動，找到答案)
// A1: MP3 要外接 DFPlayer Mini 模組，WAV 可以用 SD 卡加 TMRpcm、PCM 存在 Flash 或 Mozzi 合成，其中 DFPlayer 最推薦。
// Q2: 請幫我找 PCM 相關的 libraries 我想試試看
// A2: 提供 wav2pcm.py 把 8 kHz 單聲道 WAV 轉成 sound.h，再用 PCM 函式庫從 pin 11 播放約 3 秒內的音效。
// Q3: 能不能修改 PCM，讓它用 pin 8 或其他技術播放？
// A3: 改寫成 PCM8，用計時器中斷模擬 PWM，讓板上 pin 8 的蜂鳴器直接播放，而且可以和 tone() 寫在同一個程式。
// Q4: 生成範例 sound.h
// A4: 合成一段約 1.5 秒的 C6–E6–G6–C7 上行鈴聲並轉成 sound.h，附上 chime.wav 可以先試聽。
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
