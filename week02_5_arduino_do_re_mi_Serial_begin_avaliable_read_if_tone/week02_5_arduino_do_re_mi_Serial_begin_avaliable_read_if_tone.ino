// week02_5_arduino_do_re_mi_Serial_begin_avaliable_read_if_tone
// 我想把 Arduino 跟 Processing 結合
// 在 Processing 按下 key 1 2 3 對應 Arduino 的 Do Re Mi 使用 USB SERIAL
// 寫完程式，用 Tool-SerialMonitor 來傳送 1 2 3 很麻煩 (等一下關掉)
//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // USB Serial 開始傳輸 , 速度 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){ // 如果 USB Serial 有收到資料
      char c = Serial.read(); // 就讀進來
      if (c == '1') tone(8, 523, 100); // Do 1秒
      if (c == '2') tone(8, 587, 100); // Re 1秒
      if (c == '3') tone(8, 659, 100); // Mi 1秒
    }
}
