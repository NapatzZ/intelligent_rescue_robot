uint8_t BASE_SPEED = 40;
float KP_F = 0.4, KI_F = 0.00001, KD_F = 90, KP_B = 0.4, KI_B = 0.00001, KD_B = 90;

typedef struct {
  uint8_t x;
  uint8_t y;
} Point;

typedef struct {
  Point dropoff_location;
  int servo_angle;
} DropoffZone;

typedef struct {
  uint8_t x_positions[QUEUE_SIZE];
  uint8_t y_positions[QUEUE_SIZE];
  int front;
  int rear;
} Queue;

// Function Prototypes
void enqueue(Queue *q, Point pos);
Point dequeue(Queue *q);
bool is_empty(Queue *q);
bool is_dropoff_zone(Point p);
bool is_pickup_point(Point p);
bool is_valid_move(Point p, Point destination);
void find_shortest_pickup(Point *pickup_points, Point current_position, Point *closest_pickup, int *visited_pickups, uint8_t *closest_pickup_index);
void add_possible_moves(Point current, Point destination, Queue *q);
void print_direction_change(Point previous, Point current);
void move(Point previous, Point current);
void path_calculation(Point start, Point destination, int servo_angle);
void set_visited(uint8_t x, uint8_t y);
bool is_visited(uint8_t x, uint8_t y);
void clear_visited();
void clear_parent();

// Global Variables
const DropoffZone dropoff_zones[NUM_BALLS] = {
  { RED_DROP_OFF, SERVO_RED },
  { GREEN_DROP_OFF, SERVO_GREEN },
  { BLUE_DROP_OFF, SERVO_BLUE },
  { YELLOW_DROP_OFF, SERVO_YELLOW }
};

const Point pickup_points[NUM_BALLS] = {
  PICKUP1, PICKUP2, PICKUP3, PICKUP4
};

Point return_step = { 0, 0 };
Point current_position = START_POSITION;  // Starting position
Point exit_point = EXIT_POSITION;
int visited_pickups[NUM_BALLS] = { 0 };  // Track visited pickup points

// Arrays moved to global scope
uint8_t visited[HEIGHT];  // Each uint8_t represents a row, bits represent columns
uint8_t parent[WIDTH * HEIGHT];
Point path[WIDTH * HEIGHT];

// Function Implementations

void enqueue(Queue *q, Point pos) {
  if ((q->rear + 1) % QUEUE_SIZE == q->front) {
    // Queue is full
    return;
  }
  q->x_positions[q->rear] = pos.x;
  q->y_positions[q->rear] = pos.y;
  q->rear = (q->rear + 1) % QUEUE_SIZE;
}

Point dequeue(Queue *q) {
  Point pos = { q->x_positions[q->front], q->y_positions[q->front] };
  q->front = (q->front + 1) % QUEUE_SIZE;
  return pos;
}

bool is_empty(Queue *q) {
  return q->front == q->rear;
}

bool is_dropoff_zone(Point p) {
  for (uint8_t i = 0; i < NUM_BALLS; i++) {
    if (p.x == dropoff_zones[i].dropoff_location.x && p.y == dropoff_zones[i].dropoff_location.y) {
      return true;
    }
  }
  return false;
}

bool is_pickup_point(Point p) {
  for (uint8_t i = 0; i < NUM_BALLS; i++) {
    if (p.x == pickup_points[i].x && p.y == pickup_points[i].y && !visited_pickups[i]) {
      return true;
    }
  }
  return false;
}

void set_visited(uint8_t x, uint8_t y) {
  visited[y] |= (1 << x);
}

bool is_visited(uint8_t x, uint8_t y) {
  return (visited[y] & (1 << x)) != 0;
}

void clear_visited() {
  for (uint8_t i = 0; i < HEIGHT; i++) {
    visited[i] = 0;
  }
}

void clear_parent() {
  for (uint8_t i = 0; i < WIDTH * HEIGHT; i++) {
    parent[i] = 255;  // Initialize to invalid point
  }
}

bool is_valid_move(Point p, Point destination) {
  if (p.x >= WIDTH || p.y >= HEIGHT || is_visited(p.x, p.y)) {
    return false;
  }

  for (uint8_t i = 0; i < NUM_BALLS; i++) {
    if (p.x == pickup_points[i].x && p.y == pickup_points[i].y && !(p.x == destination.x && p.y == destination.y)) {
      return false;
    }
  }

  if ((is_dropoff_zone(p) || is_pickup_point(p)) && !(p.x == destination.x && p.y == destination.y)) {
    return false;
  }

  return true;
}

void find_shortest_pickup(Point *pickup_points, Point current_position, Point *closest_pickup, int *visited_pickups, uint8_t *closest_pickup_index) {
  uint8_t min_distance = 255;
  for (uint8_t i = 0; i < NUM_BALLS; i++) {
    if (!visited_pickups[i]) {
      uint8_t distance_x = abs((int)current_position.x - (int)pickup_points[i].x);
      uint8_t distance_y = abs((int)current_position.y - (int)pickup_points[i].y);
      uint8_t distance = distance_x + distance_y;
      if (distance < min_distance) {
        min_distance = distance;
        *closest_pickup = pickup_points[i];
        *closest_pickup_index = i;
      }
    }
  }
}

void add_possible_moves(Point current, Point destination, Queue *q) {
  Point moves[4] = {
    { current.x + 1, current.y },  // move right
    { current.x - 1, current.y },  // move left
    { current.x, current.y + 1 },  // move down
    { current.x, current.y - 1 }   // move up
  };

  for (uint8_t i = 0; i < 4; i++) {
    Point new_pos = moves[i];
    if (is_valid_move(new_pos, destination)) {
      enqueue(q, new_pos);
      set_visited(new_pos.x, new_pos.y);
      parent[new_pos.y * WIDTH + new_pos.x] = current.y * WIDTH + current.x;
    }
  }
}

// Function to print direction changes
void print_direction_change(Point previous, Point current) {
#if DEBUG_MODE
  oled.clear();                  // Clear the screen before updating
  oled.text(0, 0, "Heading: ");  // Row 0, Column 0: Display Heading
  if (current.x > previous.x && robot_direction != right) {
    switch (robot_direction) {
      case up: oled.text(1, 0, "Direction: Right"); break;
      case down: oled.text(1, 0, "Direction: Left"); break;
      case left:
        oled.text(1, 0, "Direction: Left");
        oled.text(2, 0, "Direction: Left");
        break;
    }
    robot_direction = right;
  } else if (current.x < previous.x && robot_direction != left) {
    switch (robot_direction) {
      case up: oled.text(1, 0, "Direction: Left"); break;
      case down: oled.text(1, 0, "Direction: Right"); break;
      case right:
        oled.text(1, 0, "Direction: Left");
        oled.text(2, 0, "Direction: Left");
        break;
    }
    robot_direction = left;
  } else if (current.y > previous.y && robot_direction != down) {
    switch (robot_direction) {
      case right: oled.text(1, 0, "Direction: Right"); break;
      case left: oled.text(1, 0, "Direction: Left"); break;
      case up:
        oled.text(1, 0, "Direction: Left");
        oled.text(2, 0, "Direction: Left");
        break;
    }
    robot_direction = down;
  } else if (current.y < previous.y && robot_direction != up) {
    switch (robot_direction) {
      case right:
        oled.text(1, 0, "Direction: Left");
        ;
        break;
      case left: oled.text(1, 0, "Direction: Right"); break;
      case down:
        oled.text(1, 0, "Direction: Left");
        oled.text(2, 0, "Direction: Left");
        break;
    }
    robot_direction = up;
  }
  oled.show();  // Update the OLED screen with the new information
  delay(7000);
#else
  // Non-debug mode: actual movement happens here
  if (current.x > previous.x && robot_direction != right) {
    switch (robot_direction) {
      case up: turn_right(); break;
      case down: turn_left(); break;
      case left:
        turn_left();
        turn_left();
        break;
    }
    robot_direction = right;
  } else if (current.x < previous.x && robot_direction != left) {
    switch (robot_direction) {
      case up: turn_left(); break;
      case down: turn_right(); break;
      case right:
        turn_left();
        turn_left();
        break;
    }
    robot_direction = left;
  } else if (current.y > previous.y && robot_direction != down) {
    switch (robot_direction) {
      case right: turn_right(); break;
      case left: turn_left(); break;
      case up:
        turn_left();
        turn_left();
        break;
    }
    robot_direction = down;
  } else if (current.y < previous.y && robot_direction != up) {
    switch (robot_direction) {
      case right: turn_left(); break;
      case left: turn_right(); break;
      case down:
        turn_left();
        turn_left();
        break;
    }
    robot_direction = up;
  }
#endif
}

// Function to move robot and display actions
void move(Point previous, Point current) {
#if DEBUG_MODE
  oled.clear();  // Clear the OLED screen before updating
  oled.text(0, 0, "Moving from: ");
  char buf[16];
  snprintf(buf, sizeof(buf), "(%d,%d) to (%d,%d)", previous.x, previous.y, current.x, current.y);
  oled.text(1, 0, buf);  // Display the coordinates

  if (current.x > previous.x) {  // Moving right
    oled.text(2, 0, "Direction: Right");
    oled.text(3, 0, "Forward");
  } else if (current.x < previous.x) {  // Moving left
    oled.text(2, 0, "Direction: Left");
    oled.text(3, 0, "Forward");
  } else if (current.y > previous.y) {  // Moving down
    oled.text(2, 0, "Direction: Down");
    oled.text(3, 0, "Forward");
  } else if (current.y < previous.y) {  // Moving up
    oled.text(2, 0, "Direction: Up");
    oled.text(3, 0, "Forward");
  }

  oled.show();  // Update the OLED screen with the new information
  delay(1000);  // Delay for 20 seconds before the next step

#else
  // Non-debug mode: actual movement happens here
  if (current.x > previous.x) {  // Moving right
    if (robot_direction == right) {
      forward();
    } else {
      backward();
    }
  } else if (current.x < previous.x) {  // Moving left
    if (robot_direction == left) {
      forward();
    } else {
      backward();
    }
  } else if (current.y > previous.y) {  // Moving down
    if (robot_direction == down) {
      forward();
    } else {
      backward();
    }
  } else if (current.y < previous.y) {  // Moving up
    if (robot_direction == up) {
      forward(40, KP_F, KI_F, KD_F);
    } else {
      backward(BASE_SPEED, KP_B, KI_B, KD_B);
    }
  }
#endif
}
// Function to calculate path and display debug info
void path_calculation(Point start, Point destination, int servo_angle) {
  Queue q = { .front = 0, .rear = 0 };
  clear_visited();
  clear_parent();

  set_visited(start.x, start.y);
  enqueue(&q, start);

  bool found = false;

  while (!is_empty(&q)) {
    Point current_pos = dequeue(&q);

    if (current_pos.x == destination.x && current_pos.y == destination.y) {
      found = true;
      break;
    }

    add_possible_moves(current_pos, destination, &q);
  }

  if (found) {
    uint8_t path_length = 0;
    Point current = destination;
    while (!(current.x == start.x && current.y == start.y)) {
      path[path_length++] = current;
      uint8_t parent_index = parent[current.y * WIDTH + current.x];
      current.x = parent_index % WIDTH;
      current.y = parent_index / WIDTH;
    }
    path[path_length++] = start;

    // Reverse the path to get the correct order
    for (uint8_t i = 0; i < path_length / 2; i++) {
      Point temp = path[i];
      path[i] = path[path_length - i - 1];
      path[path_length - i - 1] = temp;
    }

    // Follow the calculated path
    for (uint8_t i = 0; i < path_length - 1; i++) {
      print_direction_change(path[i], path[i + 1]);
      if (i != path_length - 2) {
        move(path[i], path[i + 1]);
      }
    }
    // Handle servo movement and finalize
    if (servo_angle == -1) {
      servo(1, SERVO_UP);
      delay(200);
      servo(2, SERVO_ARR);
    } else {
      servo(1, SERVO_UP);
      delay(500);
      servo(2, SERVO_KEEP);
    }

    forward_millis(20,200);
    forward_ultra(20);

    if (servo_angle == -1) {
      //ขาหยิบ
    } else {
      //ขาวาง
    }

    AO();
    delay(200);

    if (path_length >= 2) {
      return_step = path[path_length - 2];
    } else {
      return_step = start;
    }

  } else {
    // No valid path found
  }
}

void return_to_before_position() {
  backward();
  AO();
  sleep(300);
  current_position = return_step;
}

void execute() {
  int8_t closest_pickup_index;
  Point closest_pickup;

  for (uint8_t i = 0; i < NUM_BALLS; i++) {
    find_shortest_pickup(pickup_points, current_position, &closest_pickup, visited_pickups, &closest_pickup_index);

    path_calculation(current_position, closest_pickup, -1);
    current_position = closest_pickup;
    visited_pickups[closest_pickup_index] = 1;
    AO();

    return_to_before_position();
    read_color(&color);

    oled.textSize(1);
    oled.text(0, 0, "%d   ", color);
    oled.show();

    path_calculation(current_position, dropoff_zones[color].dropoff_location, dropoff_zones[color].servo_angle);
    current_position = dropoff_zones[color].dropoff_location;

    return_to_before_position();
  }
  sound(3000, 500);
  path_calculation(current_position, exit_point, -1);

  AO();
  sleep(300);
}