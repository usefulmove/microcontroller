#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define DISPLAY_LINES 7
#define SCROLL_DELAY 90
#define READ_DELAY 6500

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* poem[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  " We are the light",
  "",
  " we are robbed of",
  "",
  " each time one of us",
  "",
  " is lost",
  "",
  "",
  "",
  "  Toni Cade Bambara  ",
  "",
  "",
  "",
};

void display_poem(int start) {
  display.clearDisplay();
  display.setCursor(0, 0);
  for (int i = start; i < (start + DISPLAY_LINES); i++) {
    display.println(poem[i]);
  }
  display.display();
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // don't proceed. loop forever.
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  for (int i = 0; i <= 7; i++) {
    display_poem(i);
    delay(SCROLL_DELAY);
  }
  display_poem(7);
  delay(READ_DELAY);
  for (int i = 7; i <= 14; i++) {
    display_poem(i);
    delay(SCROLL_DELAY);
  }
  delay(4500);
  display.clearDisplay();
  display.display();
  delay(4500);
}
