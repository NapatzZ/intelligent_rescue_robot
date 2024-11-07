int PICKUP1_ARRAY[2] { 1, 1 };
int PICKUP2_ARRAY[2] { 2, 1 };
int PICKUP3_ARRAY[2] { 3, 1 };
int PICKUP4_ARRAY[2] { 4, 1 };

void read_color(int x,int y, uint8_t *color_choice) {

  if(x == PICKUP1_ARRAY[0] && y == PICKUP1_ARRAY[1])   *color_choice = 0;  
  else if(x == PICKUP2_ARRAY[0] && y == PICKUP2_ARRAY[1])   *color_choice = 1;  
  else if(x == PICKUP3_ARRAY[0] && y == PICKUP3_ARRAY[1])   *color_choice = 2;  
  else if(x == PICKUP4_ARRAY[0] && y == PICKUP4_ARRAY[1])   *color_choice = 3;  
}