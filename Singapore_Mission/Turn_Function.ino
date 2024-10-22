void turn_left() {
  while (sensor_front(0) == 0) {
    Motor(-turn_speed, turn_speed);
  }
  while (sensor_front(2) == 0) {
    Motor(-turn_speed, turn_speed);
  }
    AO();
    sleep(200);
}

void turn_right() {
  while (sensor_front(4) == 0) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(2) == 0) {
    Motor(turn_speed, -turn_speed);
  }

    AO();
    sleep(200);
}