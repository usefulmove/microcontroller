#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "cor.h"
#include "moments.h"

// Adafruit Feather ESP32-S3 with integrated TFT display control pins
#define TFT_CS         7   // chip select
#define TFT_RST        40  // reset
#define TFT_DC         39  // data/command
#define TFT_BACKLIGHT  45  // backlight

#define BOOT_BUTTON     0  // GPIO0

// initialize the display
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  // configure boot button as input
  pinMode(BOOT_BUTTON, INPUT_PULLUP);

  // turn on backlight
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // initialize display
  display.init(135, 240);
  display.setRotation(3);
}

void display_image(const uint16_t* image) {
  display.fillScreen(cor_black);
  delay(1200);
  display.drawRGBBitmap(0, 0, image, 240, 135);
}

void hold_for_button_press() {
  while (digitalRead(BOOT_BUTTON) == HIGH) {}
}

void loop() {
  display_image(splash);
  delay(3800);
  display_image(no_parts);
  hold_for_button_press();

  display_image(stacy);
  hold_for_button_press();

  display_image(amada);
  hold_for_button_press();

  display_image(bobby);
  hold_for_button_press();

  display_image(remembering_xochi);
  hold_for_button_press();

  display_image(steve);
  hold_for_button_press();

  display_image(thavy);
  hold_for_button_press();

  display_image(ali);
  hold_for_button_press();

  display_image(plum);
  hold_for_button_press();

  display_image(thumb);
  hold_for_button_press();

  display_image(behind);
  hold_for_button_press();

  display_image(tub);
  hold_for_button_press();
}
