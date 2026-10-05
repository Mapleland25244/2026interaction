// week05_2_processing_do_re_mi_serial_keyPressed_keyRelased
// 修改自 week05_1_processing_do_re_mi_serial
// 按多久、叫多久，放開、就不叫了 不是永遠 0.1秒
import processing.serial.*; // 使用 USB Serial 外掛
Serial myPort; // 將用 myPort 來傳 USB Serial 資料
void setup(){
  size(300, 300); // 隨便的視窗
  myPort = new Serial(this, "COM3", 9600); // 中間序列埠自己查
}
void draw(){

}
int p1 = 0, p2 = 0, p3 = 0; // 下面有做修改
void keyPressed(){ // 按數字鍵時，會利用 USB Serial 傳資料到 電路板
  if (p1 == 0 && key == '1') myPort.write('1'); // 之前沒按，現在按下去了
  if (p2 == 0 && key == '2') myPort.write('2');
  if (p3 == 0 && key == '3') myPort.write('3');
  if (p1 == 0 && key == '1') p1 = 1; // 0 代表 「沒有按」 1 代表 「按下去」
  if (p2 == 0 && key == '2') p2 = 1; 
  if (p3 == 0 && key == '3') p3 = 1; 
}
void keyReleased() {
  if (key == '1') p1 = 0; // 放開 1 鍵
  if (key == '2') p2 = 0; // 放開 2 鍵
  if (key == '3') p3 = 0; // 放開 3 鍵
  myPort.write('0'); // 告訴 Arduino 你不要發出任何聲音 !!!!!
}
