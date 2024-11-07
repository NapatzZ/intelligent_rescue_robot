int sensor_front(int8_t i) {
  int sensor_value = analog(i);                                                                            // อ่านค่า analog จากเซนเซอร์ที่ตำแหน่ง i
  int map_sensor_value = map(sensor_value, max_front_sensor_value[i], min_front_sensor_value[i], 0, 100);  // แปลงค่าให้อยู่ในช่วง 0-100
  return map_sensor_value >= 50 ? 1 : 0;                                                                   // ถ้าค่ามากกว่า 50 ถือว่าเซนเซอร์ตรวจพบเส้น(เจอสีดำ)
}


int sensor_back(int8_t i) {
  int sensor_value = adc.read(i);                                                                        // อ่านค่า analog จากเซนเซอร์ที่ตำแหน่ง i
  int map_sensor_value = map(sensor_value, max_back_sensor_value[i], min_back_sensor_value[i], 0, 100);  // แปลงค่าให้อยู่ในช่วง 0-100
  return map_sensor_value >= 50 ? 1 : 0;                                                                 // ถ้าค่ามากกว่า 50 ถือว่าเซนเซอร์ตรวจพบเส้น(เจอสีดำ)
}

int Position_front() {
  int sum = 0;
  int avg = 0;
  int8_t value;

  // Loop through the sensors to calculate weighted sum
  for (int8_t i = 0; i < numsensor_front; i++) {
    value = sensor_front(i);     // Read sensor value (0 or 1)
    avg += value * (i * 100);    // Apply weight (0, 100, 200, 300, 400)
    sum += value;                // Sum the active sensors
  }

  // Check if any sensor is on the line
  if (sum > 0) {
    last_position = avg / sum;   // Calculate weighted average
  } else {
    // Avoid division by zero, use last known position
    if (last_position >= setpoint_front) {
      last_position = 400;  // Assume far right if last position was on the right
    } else {
      last_position = 0;    // Assume far left if last position was on the left
    }
  }

  return last_position;
}


int Position_back() {
  int sum = 0;
  int avg = 0;
  int value;

  for (int8_t i = 0; i < numsensor_back; i++) {
    value = sensor_back(i);     // Read sensor value (0 or 1)
    avg += value * (i * 100);    // Apply weight (0, 100, 200, 300, 400)
    sum += value;                // Sum the active sensors
  }

  // Check if any sensor is on the line
  if (sum > 0) {
    last_position = avg / sum;   // Calculate weighted average
  } else {
    // Avoid division by zero, use last known position
    if (last_position >= setpoint_back) {
      last_position = 700;  // Assume far right if last position was on the right
    } else {
      last_position = 0;    // Assume far left if last position was on the left
    }
  }

  return last_position;
}

int in_range(int i) {
  if (analog(i) >= green[i] - 720 && analog(i) <= green[i] + 720){
    return 1;
  }
  else{
    return 0;
  }
}
int in_rangeR(int x) {
  if (analog(x) >= red[x] - 300 && analog(x) <= red[x] + 300){
    return 1;
  }
  else{
    return 0;
  }
}