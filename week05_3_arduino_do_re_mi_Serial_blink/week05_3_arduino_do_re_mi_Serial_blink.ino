// week05_3_arduino_do_re_mi_Serial_blink
// 修改自 week05_2_arduino_do_re_mi_Serial_tone_noTone
void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT); // Buzzer 8 聲音
  pinMode(10,OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13, OUTPUT);

  
  Serial.begin(9600); // USB Serial 開始傳輸 , 速度 9600 bps
  tone(8, 523, 100); delay(200); // 等一下聲音出來，不要滑過去 // Do 0.1秒
  tone(8, 587, 100); delay(200); // 等一下聲音出來，不要滑過去 // Re 0.1秒
  tone(8, 659, 100); delay(200); // 等一下聲音出來，不要滑過去 // Mi 0.1秒
  tone(8, 587, 100); delay(200); // 等一下聲音出來，不要滑過去 // Re 0.1秒
  tone(8, 523, 100); delay(200); // 等一下聲音出來，不要滑過去 // Do 0.1秒
}
char c = '0'; // 0:沒聲音 1:Do 2:Re 3:Mi
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){ // 如果 USB Serial 有收到資料
    c = Serial.read(); // 就讀進來
  }
  for (int i=10; i<=13; i++) digitalWrite(i, LOW); // 先都暗下來
  if (c >= '0' && c <= '3') digitalWrite(c-'0'+10, HIGH);
  if (c == '0') noTone(8); // 不要發聲音
  if (c == '1') tone(8, 523, 100); // Do 1秒 
  if (c == '2') tone(8, 587, 100); // Re 1秒
  if (c == '3') tone(8, 659, 100); // Mi 1秒
  
}
