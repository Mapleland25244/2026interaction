// week01_6_mouseWheel_strokeWeight_circleSize_ellipse
// 整合 week01_4 week01_5 讓大小可以通過 mouseWheel 改變

float circleSize = 5; // 小一點點

void setup(){
  size(500, 500);
  background(255); // 白色背景
}
void draw(){
  strokeWeight(circleSize); // 筆畫的重量粗細
  if (mousePressed){ // mouse按下去，有兩種可能
    if (mouseButton == LEFT) stroke(0); // 畫黑線
    if (mouseButton == RIGHT) stroke(255); // 用白色清掉
    line(mouseX, mouseY, pmouseX, pmouseY);
  }
  noStroke(); // 不要畫外框
  rect(0, 0, 100, 100);
  stroke(0); // 黑色的線
  strokeWeight(1); // 左上角小圈圈的外框
  ellipse(50, 50, circleSize, circleSize); // 畫出圖
}
void mouseWheel(MouseEvent e){
  float a = e.getCount(); // a 會等於 1 or -1 往下滾動等於1 往上滾動等於-1
  circleSize -= a * 5;
  circleSize = constrain(circleSize, 10, 99); // 限制 circleSize 數值介於10-99
}
