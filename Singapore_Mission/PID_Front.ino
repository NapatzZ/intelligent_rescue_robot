void forward_ultra(int BaseSpeed, float Kp, float Ki, float Kd) {
  int8_t integral = 0;
  int output = 0;
  int last_error = 0;
  while (27.86 / ((analog(FRONT_INFARED_PIN) * (5.0 / 1023.0)) - 0.1) > 2.15) {
    int error = Position_front() - setpoint_front;
    integral += error;
    integral = constrain(integral, -100, 100);
    output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    leftmotor = constrain(leftmotor, -60, 60);
    rightmotor = constrain(rightmotor, -60, 60);
    Motor(leftmotor, rightmotor);
  }
  AO();
  sleep(50);
}

void forward_range(int BaseSpeed, float Kp, float Ki, float Kd) {
  int integral = 0;
  int output = 0;
  int last_error = 0;
  while (!(in_rangeR(0) && in_rangeR(1) && in_rangeR(2) && in_rangeR(3))) {
    int error = Position_front() - setpoint_front;
    output = (error * Kp) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    if (BaseSpeed >= 60) {
      cal_M = 70;
    } else {
      cal_M = BaseSpeed;
    }
    leftmotor = constrain(leftmotor, -cal_M, cal_M);
    rightmotor = constrain(rightmotor, -cal_M, cal_M);
    Motor(leftmotor, rightmotor);
  }
  Motor(40, 40);
  sleep(50);
  AO();
}
void forward(int BaseSpeed, float Kp, float Ki, float Kd) {
  int integral = 0;
  int output = 0;
  int last_error = 0;
  while (!(sensor_front(2)==1 && sensor_front(3)==1&& sensor_front(4)==1)) {
    int error = Position_front() - setpoint_front;
    output = (error * Kp) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    if (BaseSpeed >= 60) {
      cal_M = 70;
    } else {
      cal_M = BaseSpeed;
    }
    leftmotor = constrain(leftmotor, -cal_M, cal_M);
    rightmotor = constrain(rightmotor, -cal_M, cal_M);
    Motor(leftmotor, rightmotor);
  }
  Motor(40, 40);
  sleep(50);
  AO();
}
void forward_millis(int BaseSpeed, float Kp, float Ki, float Kd, float duration) {
  int integral = 0;
  int output = 0;
  int last_error = 0;
  long time = millis();
  while ((millis() - time) < duration) {
    int error = Position_front() - setpoint_front;
    output = (error * Kp) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    if (BaseSpeed >= 60) {
      cal_M = 70;
    } else {
      cal_M = BaseSpeed;
    }
    leftmotor = constrain(leftmotor, -cal_M, cal_M);
    rightmotor = constrain(rightmotor, -cal_M, cal_M);
    Motor(leftmotor, rightmotor);
  }
  sleep(100);
  AO();
}