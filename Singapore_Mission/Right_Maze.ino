void SimpleRight(float Kp, float Ki, float Kd) {
  unsigned long checkStartTime = 0;  // ใช้สำหรับการจับเวลา
  bool belowThreshold = false;       // สถานะการจับว่าค่าต่ำกว่า 500 ต่อเนื่องหรือไม่
  int integral = 0;
  int output = 0;
  int last_error = 0;
  while (1) {
    right_distance = 27.86 / ((analog(RIGHT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);  //convert to .5 float
    left_distance = 27.86 / ((analog(LEFT_ULTRASONIC_PIN) * (5.0 / 1023.0)) - 0.1);    //convert to .5 float
    front_distance = (analog(8) / 41);

    if (in_range(0) && in_range(1) && in_range(2) && in_range(3) && in_range(4)) {
      if (checkStartTime == 0) {
        checkStartTime = millis();  // เริ่มจับเวลาเมื่อค่าต่ำกว่า
      } else if (millis() - checkStartTime >= 20) {
        AO();
        break;  // ออกจากลูป
      }
    } else {
      checkStartTime = 0;  // รีเซ็ตตัวจับเวลาเมื่อค่ากลับมาเกิน
                           // ทำงานปกติถ้าไม่มีเงื่อนไขที่หยุด
      if (front_distance <= 6) {
        AO();
        sleep(200);
        Motor(-turn_speed, -turn_speed);
        delay(220);
        AO();
        delay(200);
        Motor(-turn_speed, turn_speed);
        delay(260);
        AO();
      } else if (right_distance > 6) {  // ใกล้กับผนังด้านซ้ายมาก
        Motor(base_speed_right,11);    // มอเตอร์ซ้ายจะเพิ่มความเร็ว
        delay(30);
      } else {
        float error = ((int)(right_distance * 100 + 0.5) / 100.0) - setpoint_right;
        integral += error;
        integral = constrain(integral, -100, 100);
        output = (error * Kp) + (integral * Ki) + ((error - last_error) * Kd);
        last_error = error;
        leftmotor = base_speed_right + output;
        rightmotor = base_speed_right - output;
        leftmotor = constrain(leftmotor, -70, 60);
        rightmotor = constrain(rightmotor, -70, 60);
        Motor(leftmotor, rightmotor);
      }
    }
  }
}