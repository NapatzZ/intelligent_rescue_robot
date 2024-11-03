void turn_left() {
  delay(100);
  while (sensor_front(0) == 1) {
    Motor(-turn_speed, turn_speed);
  }
  while (sensor_front(0) == 0) {
    Motor(-turn_speed, turn_speed);
  }
  while (sensor_front(0) == 1) {
    Motor(-turn_speed, turn_speed);
  }
  AO();
  sleep(100);
}

void turn_right() {
  delay(100);
  while (sensor_front(4) == 1) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(4) == 0) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(4) == 1) {
    Motor(turn_speed, -turn_speed);
  }

  AO();
  sleep(100);
}
void Uturn()
{
  while (sensor_front(4) == 1) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(4) == 0) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(4) == 1) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(4) == 0) {
    Motor(turn_speed, -turn_speed);
  }
  while (sensor_front(4) == 1) {
    Motor(turn_speed, -turn_speed);
  }
   AO();
  sleep(100);
}