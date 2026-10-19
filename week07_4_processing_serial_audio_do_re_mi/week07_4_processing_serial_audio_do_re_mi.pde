// week07_4_processing_serial_audio_do_re_mi
// 修改自 week05_3_processing_do_re_mi_serial_draw
// 修改自 week07_3_processing_audio_do_re_mi
import processing.serial.*; // 加這行!!!!
Serial myPort; // 加這行!!!!
import processing.sound.*;
SoundFile Do, Re, Mi;
void setup(){
  size(300, 200);
  myPort = new Serial(this, "COM3", 9600);
  Do = new SoundFile(this, "do.wav");
  Re = new SoundFile(this, "re.wav");
  Mi = new SoundFile(this, "mi.wav");
}
void draw(){
  rect(0, 0, 100, 200);
  rect(100, 0, 100, 200);
  rect(200, 0, 100, 200);
}
void mousePressed(){
  if(mouseX < 100){
    Do.play();
    myPort.write('1'); // 加這行!!!!
  }else if(mouseX < 200){
    Re.play();
    myPort.write('2'); // 加這行!!!!
  }else{
    Mi.play();
    myPort.write('3'); // 加這行!!!!
  }
}
void mouseReleased(){ // 加這行!!!!
  myPort.write('0'); // 加這行!!!!
}
