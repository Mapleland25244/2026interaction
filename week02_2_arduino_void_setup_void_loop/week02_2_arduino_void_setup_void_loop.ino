// week02_2_arduino_void_setup_void_loop
// 你的第一個 Arduino 的程式(會亮、會有聲音)
void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT); // 第8個腳，要發出 Buzzer 聲音
}
// 勾勾(Ctrl-R編譯程式) 箭頭往右(Ctrl-U上傳到電路板)
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8, HIGH); // 送出高電位
  delay(1000); // 等 1000ms 
  digitalWrite(8, LOW); // 送出低電位
  delay (1000); // 等 1000ms
}
