void SimpleLeft(float Kp, float Ki, float Kd) {
  unsigned long checkStartTime = 0;  // ใช้สำหรับการจับเวลา
  bool belowThreshold = false;       // สถานะการจับว่าค่าต่ำกว่า 500 ต่อเนื่องหรือไม่
  int integral = 0;
  int output = 0;
  int last_error = 0;
  while (1) {
    right_distance = 27.86 / ((analog(RIGHT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
    left_distance = 27.86 / ((analog(LEFT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);
    front_distance = (analog(FRONT_ULTRASONIC_PIN) / 41);

    if (in_range(0) && in_range(1) && in_range(2)) {
      if (checkStartTime == 0) {
        checkStartTime = millis();  // เริ่มจับเวลาเมื่อค่าต่ำกว่า
      } else if (millis() - checkStartTime >= 20) {
        AO();
        break;  // ออกจากลูป
      }
    } else {
      checkStartTime = 0;  // รีเซ็ตตัวจับเวลาเมื่อค่ากลับมาเกิน
                           // ทำงานปกติถ้าไม่มีเงื่อนไขที่หยุด
      if (front_distance <= 8) {
        AO();
        sleep(200);
        Motor(-turn_speed, -turn_speed);
        delay(160);
        AO();
        delay(200);
        Motor(turn_speed+5, -turn_speed+5);
        delay(210);
        AO();
      } else if (left_distance > 6) {   // ใกล้กับผนังด้านซ้ายมาก
        Motor(11, base_speed_left);  // มอเตอร์ซ้ายจะเพิ่มความเร็ว
        delay(30);
      } else {
        float error = ((int)(left_distance * 100 + 0.5) / 100.0) - setpoint_left;
        integral += error;
        integral = constrain(integral, -100, 100);
        output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
        last_error = error;
        leftmotor = base_speed_left - output;
        rightmotor = base_speed_left + output;
        leftmotor = constrain(leftmotor, -100, 100);
        rightmotor = constrain(rightmotor, -100, 100);
        Motor(leftmotor, rightmotor);
      }
    }
  }
  AO();
  delay(100);
  Motor(leftmotor, rightmotor);
  delay(250);
  AO();
}