void read_color(uint8_t *color_choice) {
  unsigned long previous = millis();
  while (millis() - previous <= 300) {
    AO();  // Stop motors while waiting for color detection
  }

  if (huskylens.requestBlocks()) {  // Request all blocks from HuskyLens
    if (huskylens.countBlocks() > 0) {  // Check if there are any detected blocks
      HUSKYLENSResult result = huskylens.getBlock(0);  // Get the first detected block
      switch (result.ID) {
        case 1:
          *color_choice = 0;  // Red
          break;
        case 2:
          *color_choice = 1;  // Green
          break;
        case 3:
          *color_choice = 2;  // Blue
          break;
        case 4:
          *color_choice = 3;  // Yellow
          break;
        default:
          *color_choice = 99;  // Default if no valid ID is detected
          break;
      }
    } else {
      *color_choice = 99;  // No blocks detected
    }
  } else {
    color_choice = 99;  // Request failed
  }

  // Retry logic if no valid color was detected
  if (color_choice == 99) {
    unsigned long previous = millis();
    while (millis() - previous <= 300) {
      AO();  // Stop motors again while retrying color detection
    }

    if (huskylens.requestBlocks()) {
      if (huskylens.countBlocks() > 0) {
        HUSKYLENSResult result = huskylens.getBlock(0);  // Get the first detected block
        switch (result.ID) {
          case 1:
            *color_choice = 0;  // Red
            break;
          case 2:
            *color_choice = 1;  // Green
            break;
          case 3:
            *color_choice = 2;  // Blue
            break;
          case 4:
            *color_choice = 3;  // Yellow
            break;
          default:
            *color_choice = 99;  // Still no valid ID
            break;
        }
      } else {
        *color_choice = 99;  // No blocks detected
      }
    }
  }
}