#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

#define matrix_I2C_address 0x70

// analog input pins
#define x_input_pin A0
#define y_input_pin A1

#define x_offset 502
#define y_offset 512

int x;
int y;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  matrix.begin(matrix_I2C_address);

  // set initial position
  x = 3;
  y = 3;
}

void loop() {
  matrix.clear();
  matrix.drawPixel(x, y, LED_ON);  
  matrix.drawPixel(x, y + 1, LED_ON);  
  matrix.drawPixel(x + 1, y, LED_ON);  
  matrix.drawPixel(x + 1, y + 1, LED_ON);  
  matrix.writeDisplay();

  int x_input = analogRead(x_input_pin) - x_offset;
  int y_input = analogRead(y_input_pin) - y_offset;

  x -= x_input / 300;
  y -= y_input / 300;

  x = constrain(x, 0, 6);
  y = constrain(y, 0, 6);

  delay(350);
}
