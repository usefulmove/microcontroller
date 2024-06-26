#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "moments.h"

// Adafruit Feather ESP32-S3 with integrated TFT display control pins
#define TFT_CS         7   // chip select
#define TFT_RST        40  // reset
#define TFT_DC         39  // data/command
#define TFT_BACKLIGHT  45  // backlight

#define BOOT_BUTTON     0  // GPIO0

// color macro
#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

// initialize the display
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// color definitions
uint16_t cor_black = color565(0, 0, 0);
uint16_t cor_charcoal = color565(102, 102, 102);
uint16_t cor_white = color565(255, 255, 255);
uint16_t cor_cream = color565(250, 246, 228);
uint16_t cor_red = color565(241, 95, 73);
uint16_t cor_orange_sherbet = color565(239, 157, 110);
uint16_t cor_yellow_canary = color565(255, 252, 103);
uint16_t cor_green_eggs = color565(135, 255, 175);
uint16_t cor_blue_smurf = color565(0, 128, 255);
uint16_t cor_blue_coffee = color565(0, 192, 255);

void display_splash() {
  display.fillScreen(cor_black);
  delay(1200);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.setTextColor(cor_cream);
  display.println("");
  display.println("");
  display.println("");
  display.println("    Poem No. 3");
  display.setTextColor(cor_charcoal);
  display.println("   Sonia Sanchez");
  delay(5200);
  display.fillScreen(cor_black);
  delay(1200);
}

void display_poem_no_3() {
  display.fillScreen(cor_black);
  display.setCursor(0, 0);
  display.setTextColor(cor_cream);
  display.setTextSize(2);
  display.println("  i gather up");
  display.print("  each ");
  display.setTextColor(cor_blue_smurf);
  display.println("sound");
  display.setTextColor(cor_cream);
  display.println("  you left behind");
  display.print("  and ");
  display.setTextColor(cor_orange_sherbet);
  display.print("stretch ");
  display.setTextColor(cor_cream);
  display.println("them");
  display.println("  on our bed.");
  display.println("         each nite");
  display.print("  i ");
  display.setTextColor(cor_blue_coffee);
  display.print("breathe ");
  display.setTextColor(cor_cream);
  display.println(" you");
  display.print("  and become ");
  display.setTextColor(cor_yellow_canary);
  display.print("high");
  display.setTextColor(cor_cream);
  display.println(".");
}

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

void loop() {
  display.fillScreen(cor_black);
  delay(1200);
  display.drawRGBBitmap(0, 0, stacy, 240, 135);

  while (digitalRead(BOOT_BUTTON) == HIGH) {}

  display_splash();
  display_poem_no_3();

  while (digitalRead(BOOT_BUTTON) == HIGH) {}
}
