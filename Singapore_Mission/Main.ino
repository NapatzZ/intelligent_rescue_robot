void setup() {
  Wire.begin();
  delay(10);
  Wire.setClock(1000000L);
  delay(10);
  adc.begin(0);
  delay(10);
  huskylens.begin(Wire);
  delay(10);
  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
  waitAnykey_bmp();
  servo(2,SERVO_ARR);
  delay(500);
  servo(1, -1);
  servo(2, -1);
  delay(500);
  oled.mode(0);
  robot_direction = right;
  execute();
  //SimpleLeft(0.36,0,9.6);
 // SimpleRight(0.34,0,15.4);
 //forward_ultra(40, 0.5, 0.00001, 70);
// backward(40, 0.43, 0, 90);
 //forward(45, 0.5, 0.00001, 70);
 //forward_millis(40 , 0.5, 0.00001, 70, 460);
}

void loop() {
  // oled.text(0,0,"%d   ",knob(180));
  // servo(1,knob(180));
  // oled.show();
  // AO();
  oled.text(0, 0, "%f   ", 27.86 / (analog(LEFT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
  oled.text(1, 0, "%f   ", 27.86 / (analog(RIGHT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
  oled.text(2, 0, "%f   ", 27.86 / (analog(6) * (5.0 / 1023.0)) - 0.1);
  oled.text(3, 0, "%d   ", analog(8) / 41);
  oled.show();
  //Motor(base_speed_left,base_speed_left);
  //for(int i = 0; i< 5 ; i++ )

  // oled.text(0,0,"%d   ",  !(sensor_front(0) && sensor_front(2) && sensor_front(4) ) );
  // oled.show();
  // forward(60, 0.5, 0, 2.2);
  // backward(60,0.5,0,2.2);*/
  // for (int i = 0; i < 5; i++) {
  //   oled.text(i, 0, "%d  | %d        ", sensor_front(i),analog(i));
  //   oled.show();
  // }
  // for (int i = 0; i < 8; i++) {
  //   oled.text(i, 0, "%d  | %d        ", adc.read(i));
  //   oled.show();
  // }
}