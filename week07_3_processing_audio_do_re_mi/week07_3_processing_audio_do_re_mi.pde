// week07_3_processing_audio_do_re_mi
import processing.sound.*;
SoundFile Do, Re, Mi;
void setup(){
  size(300, 200);
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
  }else if(mouseX < 200){
    Re.play();
  }else{
    Mi.play(); 
  }
}
