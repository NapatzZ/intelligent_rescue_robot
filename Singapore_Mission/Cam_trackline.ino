void Cam_line() {
  Motor(30,30);
  delay(100);
  AO();
  delay(50);
  Motor(20,-20);
  delay(100);
  AO();
  servo(2, SERVO_ARR);
  delay(100);
  servo(1, 85);
  delay(500);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);
  delay(500);  //Switch the algorithm to line tracking.
  while (1) {
    huskylens.available();
    huskylens.isLearned();
    huskylens.request(1);
    HUSKYLENSResult result = huskylens.read();
    int X = result.xTarget;
    if (X < 138) {
      Motor(-15, 15);
    } else if (X > 150) {
      Motor(15, -15);
    } else {
      AO();
      delay(300);
      break;
    }
  }
  while ( sensor_front(1) == 1 && sensor_front(2) == 1 && sensor_front(3) == 1 ) {
    Motor(30, 30);
  }
  Motor(30, 30);
  delay(200);
  AO();
  delay(100);
  servo(1, SERVO_UP);
  delay(200);
  servo(1, -1);
  servo(2, -1);
  delay(100);
}
