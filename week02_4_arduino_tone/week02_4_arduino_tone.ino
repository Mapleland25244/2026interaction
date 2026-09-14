// week02_4_arduino_tone
void setup() { // 設定的函式
  // put your setup code here, to run once:
  // 只做一次
  pinMode(8, OUTPUT);
  tone(8, 523, 500); // Do 1秒
  delay(500);
  tone(8, 587, 500); // Re 1秒
  delay(500);
  tone(8, 659, 500); // Mi 1秒
  delay(500);
  tone(8, 523, 500); // Do 1秒
  delay(600);
  tone(8, 523, 500); // Do 1秒
  delay(500);
  tone(8, 587, 500); // Re 1秒
  delay(500);
  tone(8, 659, 500); // Mi 1秒
  delay(500);
  tone(8, 523, 500); // Do 1秒
  delay(600);
  tone(8, 659, 500); // Mi 1秒
  delay(500);
  tone(8, 698, 500); // Fa 1秒
  delay(500);
  tone(8, 784, 500); // So 1秒
  delay(600);
  tone(8, 659, 500); // Mi 1秒
  delay(500);
  tone(8, 698, 500); // Fa 1秒
  delay(500);
  tone(8, 784, 500); // So 1秒
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 重複做
}
