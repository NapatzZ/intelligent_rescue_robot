void cam_line() {
  servo(2, SERVO_ARR);
  delay(100);
  servo(1, 80);
  delay(500);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);
  delay(200); 
  while (1) {
    huskylens.available();
    huskylens.request(1);
    HUSKYLENSResult result = huskylens.read();
    int X = result.xTarget;
    if (X < 150) {
      Motor(-15, 15);
    } else if (X > 170) {
      Motor(15, -15);
    } else {
      AO();
      break;
    }
  }
  while (sensor_front(0) == 1 && sensor_front(1) == 1 && sensor_front(2) == 1 && sensor_front(3) == 1 && sensor_front(4) == 1) {
    Motor(30, 30);
  }
  AO();
  delay(100);
  servo(1, SERVO_UP);
  delay(200);
  servo(1, -1);
  servo(2, -1);
}
