#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define UPDATE_RATE 2000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // don't proceed. loop forever.
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  delay(UPDATE_RATE);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("could not read sensor"));
    return;
  }

  Serial.print(F("temperature: "));
  Serial.print(temperature);
  Serial.println(F("°F"));
  Serial.print(F("humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));
  Serial.println();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(temperature);
  display.println(F("F"));
  display.print(humidity);
  display.println(F("%"));
  display.println();
  display.display();
}
