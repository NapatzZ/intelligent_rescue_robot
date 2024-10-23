void find_line() {
  AO();
  servo(1, SERVO_DOWN);
  servo(2, SERVO_ARR);
  sleep(100);

  while (true) {
    if (huskylens.request()) {
      int numBlocks = huskylens.countBlocks();

      if (numBlocks > 0) {
        HUSKYLENSResult line = huskylens.getBlock(0);
        int centerX = line.xCenter;
        int speedLeft = 100;   //แก้เอง
        int speedRight = 100;  //แก้เอง

        if (centerX < 160) {
          speedLeft -= 50;  //แก้เอง
        } else if (centerX > 160) {
          speedRight -= 50;  //แก้เอง
        }

        Motor(speedLeft, speedRight);
      }
    }

    if (sensor_front(0) == 1 || sensor_front(1) == 1 || sensor_front(2) == 1 || sensor_front(3) == 1 || sensor_front(4) == 1) {
      Motor(0, 0);
      break;
    }

    AO();
    servo(1, SERVO_UP);
    servo(2, SERVO_KEEP);
    sleep(100);
  }
}