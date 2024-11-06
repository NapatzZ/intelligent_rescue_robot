void Cam_line(int Spw) {
  AO();
  delay(100);
  Motor(30, -30);
  delay(120);
  AO();
  Motor(40, 40);
  delay(150);
  AO();
  delay(50);
  servo(2, SERVO_ARR);
  delay(100);
  servo(1, 80);
  delay(500);
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);
  delay(500);  //Switch the algorithm to line tracking.
  while (1) {
    huskylens.available();
    huskylens.isLearned();
    huskylens.request(1);
    HUSKYLENSResult result = huskylens.read();
    int X = result.xTarget;
    if (X < 130) {
      Motor(-18, 18);
    } else if (X > 140) {
      Motor(18, -18);
    } else {
      AO();
      delay(300);
      break;
    }
    // Serial.print(L1);
    // Serial.print('\t');
    // Serial.println(L2);
    // Serial.println((int32_t)result.xTarget);
    // }
  }
  while (!(sensor_front(1) == 1 && sensor_front(2) == 1 && sensor_front(3) == 1 && sensor_front(4) == 1)) {
    Motor(40, 40);
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
