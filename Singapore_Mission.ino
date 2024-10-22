#include <POP32.h>
#include <ADS7828.h>
#include "HUSKYLENS.h"
//MODE
#define DEBUG_MODE 0
//PIN DEFINE
#define LEFT_ULTRASONIC_PIN 5
#define FRONT_ULTRASONIC_PIN 8
#define RIGHT_ULTRASONIC_PIN 7
//BALL COLLECTING AREA DEFINE
#define START_POSITION { 0, 3 }
#define EXIT_POSITION { 5, 3 }

#define PICKUP1 { 1, 1 }
#define PICKUP2 { 9, 2 }
#define PICKUP3 { 9, 1 }
#define PICKUP4 { 9, 0 }

#define RED_DROP_OFF { 2, 5 }
#define GREEN_DROP_OFF { 3, 5 }
#define BLUE_DROP_OFF { 4, 4 }
#define YELLOW_DROP_OFF { 1, 4}

#define SERVO_RED 55
#define SERVO_GREEN 55
#define SERVO_BLUE 50
#define SERVO_YELLOW 45

#define SERVO_KEEP 0
#define SERVO_ARR 170

#define SERVO_UP 10
#define SERVO_DOWN 110

#define WIDTH 7
#define HEIGHT 7
#define NUM_BALLS 4
#define QUEUE_SIZE (WIDTH * HEIGHT)

//SENSOR VARIABLE
const int numsensor_front = 5;
const int numsensor_back = 8;
const int setpoint_front = (numsensor_front - 1) * 100 / 2;
const int setpoint_back = (numsensor_back - 1) * 100 / 2;
const float setpoint_left = 3.8;
const float setpoint_right = 3.6;
int max_front_sensor_value[5] = { 3562, 3370, 3567, 3699, 3470 };
int min_front_sensor_value[5] = { 633, 528, 524, 634,666};
int max_back_sensor_value[8] = { 2721, 2786, 2360, 785, 2608, 2648, 2500, 2190 };
int min_back_sensor_value[8] = { 206, 311, 229, 61, 239, 236, 219, 234 };
int green[5] = {847,356,437,1385,690};
//ADJUSTMENT VARIABLE
int8_t base_speed_left = 40;
int8_t base_speed_right = 50;
int turn_time = 315;
//ASSINGED VARIABLE
float left_distance;
float front_distance;
float right_distance;
int last_position = 0;  // เก็บตำแหน่งเส้นล่าสุดที่หุ่นยนต์เคยอยู่
int error = 0;
int8_t leftmotor;
int8_t rightmotor;
int8_t turn_speed = 40;
int8_t close_wall_distance = 7;
int8_t color;
//ENUM
enum direction {
    up, down, right, left
} robot_direction;
//HUSKEYS VARIABLE
int ID[NUM_BALLS+1] = {0,1,2,3,4};
ADS7828 adc;
HUSKYLENS huskylens;


