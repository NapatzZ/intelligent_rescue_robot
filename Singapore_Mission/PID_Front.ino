void forward_ultra(int BaseSpeed) {
  while ((27.86 / ((analog(FRONT_INFARED_PIN) * (5.0 / 1023.0)) - 0.1)) > 2.13) {
    if (sensor_front(0) == 1 && sensor_front(1) == 0 && sensor_front(2) == 0 && sensor_front(3) == 0 && sensor_front(4) == 0) {
      Motor(leftmotor * 0.6, rightmotor);
    } else if (sensor_front(0) == 1 && sensor_front(1) == 1 && sensor_front(2) == 0 && sensor_front(3) == 0 && sensor_front(4) == 0) {
      Motor(leftmotor * 0.55, rightmotor);
    } else if (sensor_front(0) == 0 && sensor_front(1) == 1 && sensor_front(2) == 0 && sensor_front(3) == 0 && sensor_front(4) == 0) {
      Motor(leftmotor * 0.50, rightmotor);
    }
  }
}

void forward(int BaseSpeed, float Kp, float Ki, float Kd) {
  int8_t integral = 0;
  int output = 0;
  int last_error = 0;
  while (!(sensor_front(0) == 1 && sensor_front(1) == 1 && sensor_front(2) == 1 && sensor_front(3) == 1 && sensor_front(4) == 1)) {
    int error = Position_front() - setpoint_front;
    integral += error;
    integral = constrain(integral, -100, 100);
    output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = BaseSpeed + output;
    rightmotor = BaseSpeed - output;
    leftmotor = constrain(leftmotor, -70, 70);
    rightmotor = constrain(rightmotor, -70, 70);
    Motor(leftmotor, rightmotor);
  }
}

void forward() {
  while (!(sensor_front(0) == 1 && sensor_front(1) == 1 && sensor_front(2) == 1 && sensor_front(3) == 1 && sensor_front(4) == 1)) {
    if (sensor_front(0) == 1 && sensor_front(1) == 0 && sensor_front(2) == 0 && sensor_front(3) == 0 && sensor_front(4) == 0) {
      Motor(leftmotor * 0.6, rightmotor);
    } else if (sensor_front(0) == 1 && sensor_front(1) == 1 && sensor_front(2) == 0 && sensor_front(3) == 0 && sensor_front(4) == 0) {
      Motor(leftmotor * 0.55, rightmotor);
    } else if (sensor_front(0) == 0 && sensor_front(1) == 1 && sensor_front(2) == 0 && sensor_front(3) == 0 && sensor_front(4) == 0) {
      Motor(leftmotor * 0.50, rightmotor);
    }
  }
}

void forward_millis(int BaseSpeed, int duration) {
  unsigned long time = millis();
  while ((millis() - time) < duration) {
    forward();
  }
}
