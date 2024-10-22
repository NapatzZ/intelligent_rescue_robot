void backward(int BaseSpeed, float Kp, float Ki, float Kd) {
  int8_t integral = 0;
  int output = 0;
  int last_error = 0;
  while (sensor_back(0) == 0 || sensor_back(2) == 0 || sensor_back(4) == 0 || sensor_back(6) == 0) {
    int error = Position_back() - setpoint_front;
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
}

void backward() {
  while (sensor_back(0) == 0 || sensor_back(2) == 0 || sensor_back(4) == 0 || sensor_back(6) == 0) {
    if(sensor_back(0) == 1 && sensor_back(1) == 0 && sensor_back(2) == 0 && sensor_back(3) == 0 && sensor_back(4) == 0 && sensor_back(5) == 0 && sensor_back(6) == 0 && sensor_back(7) == 0){
        Motor(leftmotor * 0.6, rightmotor);
    }
  }
}