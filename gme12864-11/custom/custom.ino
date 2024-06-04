#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // don't proceed. loop forever.
  }

  // clear the buffer
  display.clearDisplay();
  display.display();

  showQuote();
}

void loop() {
}

void showQuote(void) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);     // start at top-left corner
  display.cp437(true);         // use full 256 char 'Code Page 437' font

  display.setTextSize(2);
  display.println(F(" a moment"));
  display.println(F(" a love"));
  display.println(F(" a dream"));
  display.println(F(" aloud."));
  display.display();

  //display.setTextSize(2);
  //display.println(F("   Do me"));
  //display.println(F("   like"));
  //display.println(F("   Jesus"));
  //display.display();

  //display.setTextSize(2);
  //display.println(F("  Gorilla"));
  //display.println(F("    My"));
  //display.println(F("   Love"));
  //display.display();

  //display.setTextSize(1);
  //display.println(F("  There is no chance"));
  //display.println(F("  that we will fall"));
  //display.println(F("  apart"));
  //display.println(F("  There is no chance"));
  //display.println(F("  There are no parts."));
  //display.println();
  //display.println(F("  June Jordan"));
  //display.println(F("  Poem Number Two"));
  //display.display();

  //display.setTextSize(3);
  //display.println();
  //display.println(F(" xochi "));
  //display.display();
}
