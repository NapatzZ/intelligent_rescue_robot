void backward(int BaseSpeed, float Kp, float Ki, float Kd) {
  int8_t integral = 0;
  int8_t output = 0;
  int last_error = 0;
  while (sensor_back(0) == 0 || sensor_back(2) == 0 || sensor_back(4) == 0 || sensor_back(6) == 0) {
    int error = Position_back() - setpoint_back;
    integral += error;
    integral = constrain(integral, -100, 100);
    output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
    last_error = error;
    leftmotor = -BaseSpeed + output;
    rightmotor = -BaseSpeed - output;
    leftmotor = constrain(leftmotor, -70, 70);
    rightmotor = constrain(rightmotor, -70, 70);
    Motor(leftmotor, rightmotor);
  }
  Motor(-40, -40);
  delay(30);
  calibate_back();
  delay(200);
}
void calibate_back() {
  if (sensor_back(1) == 1 || sensor_back(2) == 1) {
    while (sensor_back(3) == 0 && sensor_back(4) == 0) {
      Motor(-30, 30);
    }
    delay(50);
    AO();
  } if (sensor_back(5) == 1 || sensor_back(6) == 1) {
    while (sensor_back(3) == 0 && sensor_back(4) == 0) {
      Motor(30, -30);
    }
    delay(50);
    AO();
  }
}