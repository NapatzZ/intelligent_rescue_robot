void setup() {
  
  Wire.begin();delay(10);
  Wire.setClock(1000000L);delay(10);
  adc.begin(0);delay(10);
  huskylens.begin(Wire);delay(10);
  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
  servo(1,SERVO_UP);
  waitAnykey_bmp();
  oled.mode(0);
  robot_direction = right;
  //execute();
  SimpleLeft(0.7,0,5);
}

void loop() {
  AO();
  oled.text(0,0,"%f   ",  27.86 / (analog(LEFT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
 oled.text(1,0,"%f   ",  27.86 / (analog(RIGHT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
 oled.text(2,0,"%d   ",  analog(8) / 41);
 oled.show();
  //Motor(base_speed_left,base_speed_left);
 //for(int i = 0; i< 5 ; i++ )

  //oled.text(0,0,"%d   ",  !(sensor_front(0) && sensor_front(2) && sensor_front(4) ) );
  //oled.show();
  // forward(60, 0.5, 0, 2.2);
  // backward(60,0.5,0,2.2);*/
  // for (int i = 0; i < 5; i++) {
  //   oled.text(i, 0, "%d  | %d        ", sensor_front(i),analog(i));
  //   oled.show();
  // }
}