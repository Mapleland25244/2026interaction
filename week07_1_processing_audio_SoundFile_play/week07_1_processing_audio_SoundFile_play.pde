// week07_1_processing_audio_SoundFile_play
// File- Preferences... 把字型調大
// 想要在電腦，用程式控制聲音/音樂的
// 方法1:Processing 的 Sound 外掛, 方法2:Minim 的 外掛
// Sketch - Library - Manage Libraries... 網路通的話，可下載
// 或者用 google: processing sound library download
// Moodle 的 「上課用軟體」也有一份 sound.zip
// 把「有3個資料夾」的 sound 放在「文件-Processing-Libraries」目錄裡
// 成功後，便可在File-Example-Libraries核心函式庫-Sound-Soundfile-JumbSoundfile
import processing.sound.*;
SoundFile sound;
void setup() {
  size(300, 300);
  sound = new SoundFile(this, "music.mp3");
  sound.play();
}
void draw(){

}
