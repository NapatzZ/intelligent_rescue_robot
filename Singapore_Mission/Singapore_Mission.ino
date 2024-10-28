#include <POP32.h>
#include <ADS7828.h>
#include "HUSKYLENS.h"
//MODE
#define DEBUG_MODE 0  
//PIN DEFINE
#define LEFT_ULTRASONIC_PIN 5
#define FRONT_ULTRASONIC_PIN 8
#define RIGHT_ULTRASONIC_PIN 7
#define FRONT_INFARED_PIN 6
//BALL COLLECTING AREA DEFINE
#define START_POSITION  { 0, 2 }
#define EXIT_POSITION { 4, 3 }
#define PICKUP1  { 1, 4 }
#define PICKUP2 { 1, 0 }
#define PICKUP3 { 2, 1 }
#define PICKUP4 { 4, 1 }
#define RED_DROP_OFF  { 3, 4 }
#define GREEN_DROP_OFF { 3, 0 }
#define BLUE_DROP_OFF { 2, 3 }
#define YELLOW_DROP_OFF { 4, 2 }

#define SERVO_RED 80
#define SERVO_GREEN 80
#define SERVO_BLUE 75
#define SERVO_YELLOW 70

#define SERVO_KEEP 5
#define SERVO_ARR 170

#define SERVO_UP 30
#define SERVO_DOWN 93

#define WIDTH 6
#define HEIGHT 6
#define NUM_BALLS 4
#define QUEUE_SIZE (WIDTH * HEIGHT)

//SENSOR VARIABLE
const int numsensor_front = 5;
const int numsensor_back = 8;
const int setpoint_front = (numsensor_front - 1) * 100 / 2;
const int setpoint_back = (numsensor_back - 1) * 100 / 2;
const float setpoint_left = 3.8;
const float setpoint_right = 4;
int max_front_sensor_value[5] = { 3802, 3334, 3893, 2561, 3810 };
int min_front_sensor_value[5] = { 673, 558, 678, 415, 565 };
int max_back_sensor_value[8] = { 2829, 3151, 2722, 935, 2694, 2925, 2438, 2469 };
int min_back_sensor_value[8] = { 313, 362, 329, 106, 308,343, 277, 285 };
int green[5] = { 765, 1196, 919, 923,777 };
int red[5] = { 1998, 512, 2084, 1164, 2103 };
//ADJUSTMENT VARIABLE
int8_t base_speed_left = 40;
int8_t base_speed_right = 40;
// VD
int8_t cal_M ;
int turn_time = 315;
//ASSINGED VARIABLE
float left_distance;
float front_distance;
float right_distance;
int last_position = 0;  // เก็บตำแหน่งเส้นล่าสุดที่หุ่นยนต์เคยอยู่
int error = 0;
int8_t leftmotor;
int8_t rightmotor;
int8_t turn_speed = 35;
int8_t close_wall_distance = 7;
int8_t color;
//ENUM
enum direction {
  up,
  down,
  right,
  left
} robot_direction;
//HUSKEYS VARIABLE
int ID[NUM_BALLS + 1] = { 0, 1, 2, 3, 4 };
ADS7828 adc;
HUSKYLENS huskylens;
