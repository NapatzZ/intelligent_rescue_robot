void forward_ultra(int BaseSpeed, float Kp, float Ki, float Kd) {
  int8_t integral = 0;
  int output = 0;
  int last_error = 0;
  while (27.86 / ((analog(6) * (5.0 / 1023.0)) - 0.1) > 4) { 
    int error = Position_front() - setpoint_front;
    integral += error;
    integral = constrain(integral, -100, 100);
    output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    leftmotor = constrain(leftmotor, -100, 100);
    rightmotor = constrain(rightmotor, -100, 100);
    Motor(leftmotor, rightmotor);
  }
  sleep(50);
  AO();
  sleep(100);
}

void forward(int BaseSpeed, float Kp, float Ki, float Kd) {
  int integral = 0;
  int output = 0;
  int last_error = 0;
  while (sensor_front(0) == 0 || sensor_front(2) == 0 || sensor_front(4) == 0) { 
    int error = Position_front() - setpoint_front;
    integral += error;
    integral = constrain(integral, -100, 100);
    output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    leftmotor = constrain(leftmotor, -100, 100);
    rightmotor = constrain(rightmotor, -100, 100);
    Motor(leftmotor, rightmotor);
  }
  sleep(50);
  AO();
  sleep(100);
}
