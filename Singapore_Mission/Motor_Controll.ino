void Motor(int speed_left,int speed_right){
  #if DEBUG_MODE 
    oled.text(4,0, "left = %d   ", speed_left);
    oled.text(5,0, "right = %d   ", speed_right);
    oled.show();
  #else 
    motor(1,speed_left+4);
    motor(2,speed_right);
  #endif
}
