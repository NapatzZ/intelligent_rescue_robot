void SimpleRight(float Kp, float Ki, float Kd) {
  unsigned long checkStartTime = 0;  // For time tracking
  bool belowThreshold = false;       // Status to track continuous values below 500
  int integral = 0;
  int output = 0;
  int last_error = 0;

  while (1) {
    right_distance = 27.86 / ((analog(RIGHT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
    left_distance = 27.86 / ((analog(LEFT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
    front_distance = (analog(8) / 41);

    // Check if all analog values are in range
    if (in_range(0) && in_range(1) && in_range(2) && in_range(3) && in_range(4)) {
      if (checkStartTime == 0) {
        checkStartTime = millis();  // Start timer when values are below threshold
      } else if (millis() - checkStartTime >= 20) {
        AO();
        break;  // Exit loop
      }
    } else {
      checkStartTime = 0;  // Reset timer if values return to normal
                           // Normal operation if no stop conditions
      if (front_distance <= 6) {
        AO();
        sleep(200);
        Motor(-turn_speed, -turn_speed);
        delay(200);
        AO();
        delay(200);
        Motor(-turn_speed, turn_speed);
        delay(240);
      } else if (right_distance > 6) {  // Close to the right wall
        Motor(base_speed_right, 10);    // Right motor will increase speed
        delay(30);
      } else {
        float error = ((int)(right_distance * 100 + 0.5) / 100.0) - setpoint_right;
        integral += error;
        integral = constrain(integral, -100, 100);
        output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
        last_error = error;
        leftmotor = base_speed_right + output;
        rightmotor = base_speed_right - output;
        leftmotor = constrain(leftmotor, -100, 100);
        rightmotor = constrain(rightmotor, -100, 100);
        Motor(leftmotor, rightmotor);
      }
    }
  }
}