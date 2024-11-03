void setup() {
  Wire.begin();
  delay(10);
  Wire.setClock(1000000L);
  delay(10);
  adc.begin(0);
  delay(10);
  huskylens.begin(Wire);
  delay(10);
  waitAnykey_bmp();
  servo(2,SERVO_ARR);
  delay(500);
  servo(1, -1);
  servo(2, -1);
  delay(500);
  oled.mode(0);
  robot_direction = right;
  SimpleLeft(0.35,0,10);
  Cam_line(40);
   forward(40,0.35,0,1.2);
   forward(40,0.35,0,1.2);
   forward(40,0.35,0,1.2);
   turn_left();
   forward(40,0.4,0,1.2);
   turn_right();
   execute();
   forward(40,0.4,0,1.2);
 // SimpleRight(0.28,0,20); 
//forward(50, 0.7, 0, 0.8);
}

void loop() {
  AO();
    Serial.println(Position_front());
  // oled.text(0,0,"%d   ",knob(180));
  // servo(1,knob(180));
  // oled.show();
  // AO();
  // oled.text(0, 0, "%f   ", 27.86 / (analog(LEFT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
  // oled.text(1, 0, "%f   ", 27.86 / (analog(RIGHT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
  // oled.text(2, 0, "%f   ", 27.86 / (analog(6) * (5.0 / 1023.0)) - 0.1);
  // oled.text(3, 0, "%d   ", analog(8) / 41);
  // oled.show();
  //Motor(base_speed_left,base_speed_left);
  //for(int i = 0; i< 5 ; i++ )

  // oled.text(0,0,"%d   ",  !(sensor_front(0) && sensor_front(2) && sensor_front(4) ) );
  // oled.show();
  // forward(60, 0.5, 0, 2.2);
  // backward(60,0.5,0,2.2);*/
   for (int i = 0; i < 5; i++) {
    oled.text(i, 0, "%d  | %d        ", sensor_front(i),analog(i));
    oled.show();
  }
  // for (int i = 0; i < 8; i++) {
  //   oled.text(i, 0, "%d  | %d        ", adc.read(i));
  //   oled.show();
  // }
}