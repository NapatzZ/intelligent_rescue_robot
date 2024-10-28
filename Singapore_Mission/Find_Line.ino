void find_line() {
    int speedLeft = 40;
      int speedRight = 40;
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);
  delay(100);
  if (!huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING)) {
    Serial.println("Failed to switch to LINE_TRACKING!");
    return;
  }
  AO();
  servo(1, 85);
  servo(2, SERVO_ARR);
  sleep(300);
  while (true) {
    if (!huskylens.requestBlocks()) {
      Serial.println("Failed to request blocks from HuskyLens!");
      Motor(0, 0);
      continue;
    }
    int numBlocks = huskylens.countBlocks();
    if (numBlocks > 0) {
      HUSKYLENSResult line = huskylens.getBlock(0);
      int centerX = line.xCenter;
      if (centerX < 159) {
        Motor(speedLeft - 50, speedRight);
      } else if (centerX > 161) {
        Motor(speedLeft, speedRight - 50);
      }
    } else {
      Motor(speedLeft, speedRight);
    }
    if (sensor_front(0) == 0 || sensor_front(1) == 0 || sensor_front(2) == 0 || sensor_front(3) == 0 || sensor_front(4) == 0) {
      Motor(0, 0);
      break;
    }
    delay(100);
  }
  servo(1, SERVO_UP);
  servo(2, SERVO_KEEP);
  sleep(100);
  AO();
}