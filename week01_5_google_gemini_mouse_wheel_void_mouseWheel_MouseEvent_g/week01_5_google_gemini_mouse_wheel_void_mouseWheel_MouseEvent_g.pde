// week01_5_google_gemini_mouse_wheel_void_mouseWheel_MouseEvent_getCount
// google gemini: Processing 怎麼用 mouse wheel
// 把 AI 摘要的程式碼 copy 過來用
float circleSize = 100; //宣告全域變數控制大小

void setup(){
  size(400, 400);
}

void draw() {
  background(240);
  // 繪製一個會隨著滾輪縮放的圓形
  fill(50, 150, 250);
  noStroke();
  ellipse(width/2, height/2, circleSize, circleSize);
}

// Processing 4 標準的滾輪事件函式
void mouseWheel(MouseEvent event) {
  // event.getCount() 會回傳滾輪的滾動方向與量
  float e = event.getCount();
  
  // 調整圓形大小 (將滾輪數值乘以 5 加快縮放速度)
  circleSize += e * 5;
  
  // 限制圓形大小的最小值與最大值，防止縮小到變負數
  circleSize = constrain(circleSize, 10, 400);
}
