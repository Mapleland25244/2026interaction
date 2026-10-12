// week06_1_arduino_pin_2_button_INPUT_PULLUP

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP); // 預設 pin 2 是 button
  pinMode(8, OUTPUT); // 預設 pin 8 是 Buzzer 喇叭
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == LOW){
      tone(8, 523, 100); // 0.1 秒
      delay(100); // 等一下(讓聲音夠長)2
    }
}
