#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RST_PIN -1

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

#define FRAME_DELAY (21)
#define FRAME_WIDTH (48)
#define FRAME_HEIGHT (48)
#define FRAME_COUNT (sizeof(walk_frames) / sizeof(walk_frames[0]))

#define EEPROM_SIZE 1

const unsigned char hello [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x3b, 0x80, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x38, 0x00, 0x00, 0x00, 0x71, 0x81, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0e, 0x38, 0x00, 0x00, 0x00, 0x61, 0x81, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x00, 0xe1, 0x81, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x00, 0xc1, 0x83, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1c, 0x30, 0x00, 0x00, 0x00, 0xc1, 0x83, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1c, 0x70, 0x00, 0x00, 0x01, 0xc1, 0x83, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x70, 0x00, 0x00, 0x01, 0x83, 0x87, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x01, 0x83, 0x07, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0xe0, 0x00, 0x00, 0x01, 0x83, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0xc0, 0x00, 0x00, 0x03, 0x87, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x00, 0x03, 0x86, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x39, 0xe0, 0x00, 0x30, 0x03, 0x86, 0x06, 0x18, 0x00, 0xfc, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x33, 0xf8, 0x00, 0xfc, 0x03, 0x0e, 0x06, 0x18, 0x03, 0xfe, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3f, 0xfc, 0x01, 0xfe, 0x03, 0x0c, 0x0e, 0x38, 0x07, 0x8f, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3f, 0x0c, 0x03, 0x86, 0x03, 0x1c, 0x0e, 0x30, 0x0f, 0x07, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3c, 0x0e, 0x03, 0x87, 0x03, 0x18, 0x0e, 0x70, 0x0e, 0x03, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7c, 0x0e, 0x03, 0x07, 0x03, 0x18, 0x0e, 0x60, 0x1c, 0x01, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x78, 0x0c, 0x07, 0x06, 0x03, 0x30, 0x0e, 0xe0, 0x18, 0x01, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xf8, 0x0c, 0x07, 0x06, 0x03, 0x70, 0x0e, 0xc0, 0x18, 0x01, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xf0, 0x0c, 0x07, 0x0e, 0x03, 0xe0, 0x0f, 0xc0, 0x38, 0x01, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0xf0, 0x0c, 0x07, 0x0c, 0x03, 0xe0, 0x07, 0x80, 0x38, 0x01, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x0f, 0xf0, 0x0c, 0x07, 0x1c, 0x03, 0xc0, 0x07, 0x00, 0x78, 0x03, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x3c, 0x60, 0x0c, 0x07, 0x18, 0x03, 0x80, 0x07, 0x00, 0x78, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xf8, 0x60, 0x0c, 0x03, 0x38, 0x03, 0x80, 0x0f, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xe0, 0x60, 0x0c, 0x03, 0xf0, 0x0f, 0xc0, 0x1f, 0x01, 0xf8, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0xe0, 0x0e, 0x03, 0xe0, 0x1e, 0xe0, 0x3f, 0x83, 0xdc, 0x0e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xe0, 0x0f, 0x07, 0xf0, 0xf8, 0xf9, 0xf1, 0xef, 0x8f, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xe0, 0x07, 0xff, 0xff, 0xf0, 0x7f, 0xc0, 0xfe, 0x07, 0xf8, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xc0, 0x03, 0xf8, 0x3f, 0x80, 0x1f, 0x00, 0x78, 0x03, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const byte PROGMEM walk_frames[][288] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,31,224,0,0,0,0,63,240,0,0,0,0,112,56,0,0,0,1,224,28,0,0,0,3,128,28,0,0,0,7,8,62,0,0,0,14,56,55,0,0,0,12,120,51,192,0,0,12,248,49,248,0,0,25,208,120,60,0,0,25,176,124,12,0,0,49,176,111,204,0,0,51,48,99,252,0,0,51,96,192,56,0,0,54,96,192,0,0,0,62,96,224,0,0,0,24,112,96,0,0,0,0,120,48,0,0,0,0,124,56,0,0,0,0,206,28,0,0,0,0,199,12,0,0,0,0,199,134,0,0,0,1,204,198,0,0,0,1,140,198,0,0,0,3,12,102,0,0,0,6,24,99,0,0,0,14,56,99,0,0,0,28,112,99,0,0,0,24,96,51,0,0,0,24,192,49,128,0,0,25,128,51,128,0,0,31,128,31,0,0,0,15,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,31,224,0,0,0,0,56,112,0,0,0,0,112,56,0,0,0,0,224,24,0,0,0,3,128,28,0,0,0,7,8,62,0,0,0,6,56,54,0,0,0,12,120,51,128,0,0,12,248,51,240,0,0,12,208,120,120,0,0,25,176,124,12,0,0,25,176,111,140,0,0,51,48,99,252,0,0,51,96,192,120,0,0,55,96,192,0,0,0,62,96,224,0,0,0,28,112,96,0,0,0,0,120,48,0,0,0,0,124,56,0,0,0,0,206,24,0,0,0,0,199,12,0,0,0,0,199,140,0,0,0,1,205,198,0,0,0,1,140,198,0,0,0,3,12,198,0,0,0,7,24,99,0,0,0,14,56,99,0,0,0,12,48,99,0,0,0,24,96,99,0,0,0,24,192,49,128,0,0,25,192,51,128,0,0,31,128,31,0,0,0,15,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,31,224,0,0,0,0,56,112,0,0,0,0,112,56,0,0,0,0,224,24,0,0,0,1,192,28,0,0,0,3,8,60,0,0,0,6,24,54,0,0,0,6,56,55,0,0,0,12,248,51,224,0,0,12,240,112,240,0,0,12,240,120,24,0,0,25,176,127,24,0,0,25,176,103,248,0,0,25,224,192,248,0,0,27,96,192,0,0,0,31,96,224,0,0,0,14,112,96,0,0,0,0,120,48,0,0,0,0,124,48,0,0,0,0,110,24,0,0,0,0,70,12,0,0,0,0,199,12,0,0,0,0,199,140,0,0,0,1,134,198,0,0,0,3,140,198,0,0,0,7,28,198,0,0,0,14,24,99,0,0,0,12,48,99,0,0,0,24,96,99,0,0,0,24,224,49,128,0,0,29,192,51,0,0,0,15,128,31,0,0,0,6,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,31,224,0,0,0,0,56,112,0,0,0,0,112,24,0,0,0,0,224,24,0,0,0,1,192,28,0,0,0,3,136,60,0,0,0,3,24,62,0,0,0,6,56,54,0,0,0,6,120,55,128,0,0,6,112,113,224,0,0,12,240,112,112,0,0,12,240,124,48,0,0,12,240,79,176,0,0,13,224,195,240,0,0,25,224,192,224,0,0,15,224,192,0,0,0,15,112,96,0,0,0,0,120,112,0,0,0,0,120,48,0,0,0,0,108,24,0,0,0,0,102,24,0,0,0,0,103,12,0,0,0,0,231,140,0,0,0,1,199,142,0,0,0,3,135,198,0,0,0,7,12,198,0,0,0,6,28,227,0,0,0,12,56,99,0,0,0,12,112,99,0,0,0,12,224,49,128,0,0,15,192,51,0,0,0,7,128,31,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,3,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,15,192,0,0,0,0,31,224,0,0,0,0,56,48,0,0,0,0,112,24,0,0,0,0,224,24,0,0,0,1,192,24,0,0,0,3,140,60,0,0,0,3,24,60,0,0,0,3,56,60,0,0,0,3,120,55,0,0,0,6,112,115,192,0,0,6,112,113,224,0,0,6,112,120,112,0,0,6,240,126,48,0,0,6,224,207,224,0,0,12,224,193,224,0,0,15,224,224,0,0,0,7,240,96,0,0,0,0,120,96,0,0,0,0,120,48,0,0,0,0,108,48,0,0,0,0,110,24,0,0,0,0,102,24,0,0,0,0,103,12,0,0,0,0,199,12,0,0,0,1,135,134,0,0,0,3,14,198,0,0,0,6,28,195,0,0,0,12,56,99,0,0,0,12,112,99,128,0,0,14,224,49,128,0,0,7,192,59,0,0,0,3,128,31,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,248,0,0,0,0,3,252,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,3,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,31,240,0,0,0,0,56,48,0,0,0,0,112,24,0,0,0,0,96,24,0,0,0,0,192,24,0,0,0,1,140,56,0,0,0,1,156,56,0,0,0,3,56,60,0,0,0,3,56,62,0,0,0,3,48,103,0,0,0,3,112,99,128,0,0,3,112,121,128,0,0,3,112,253,128,0,0,2,96,207,128,0,0,6,96,195,0,0,0,3,224,192,0,0,0,3,240,96,0,0,0,0,120,96,0,0,0,0,56,96,0,0,0,0,60,48,0,0,0,0,60,48,0,0,0,0,54,48,0,0,0,0,230,24,0,0,0,1,199,24,0,0,0,3,135,12,0,0,0,6,15,140,0,0,0,12,57,140,0,0,0,12,112,198,0,0,0,15,224,198,0,0,0,7,192,230,0,0,0,0,0,110,0,0,0,0,0,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,248,0,0,0,0,3,252,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,4,0,0,0,0,3,12,0,0,0,0,3,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,96,24,0,0,0,0,228,24,0,0,0,0,204,48,0,0,0,1,156,48,0,0,0,1,152,48,0,0,0,1,184,56,0,0,0,1,176,124,0,0,0,1,176,110,0,0,0,1,176,118,0,0,0,1,176,254,0,0,0,1,48,222,0,0,0,1,176,192,0,0,0,1,240,192,0,0,0,0,240,192,0,0,0,0,48,96,0,0,0,0,56,96,0,0,0,0,56,96,0,0,0,0,60,96,0,0,0,0,124,32,0,0,0,1,230,48,0,0,0,3,134,48,0,0,0,7,14,48,0,0,0,12,63,24,0,0,0,12,115,24,0,0,0,15,227,24,0,0,0,7,129,136,0,0,0,0,1,136,0,0,0,0,1,248,0,0,0,0,0,248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,156,0,0,0,0,6,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,4,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,112,24,0,0,0,0,100,16,0,0,0,0,206,48,0,0,0,0,204,48,0,0,0,1,152,48,0,0,0,1,152,112,0,0,0,1,152,112,0,0,0,1,152,120,0,0,0,0,152,120,0,0,0,0,152,248,0,0,0,0,216,240,0,0,0,0,216,192,0,0,0,0,240,192,0,0,0,0,112,192,0,0,0,0,48,192,0,0,0,0,56,64,0,0,0,0,24,96,0,0,0,0,56,96,0,0,0,1,252,96,0,0,0,3,204,96,0,0,0,6,12,96,0,0,0,12,30,96,0,0,0,12,126,48,0,0,0,7,230,48,0,0,0,7,134,48,0,0,0,0,6,48,0,0,0,0,3,48,0,0,0,0,3,240,0,0,0,0,1,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,96,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,48,24,0,0,0,0,102,16,0,0,0,0,102,48,0,0,0,0,204,48,0,0,0,0,204,48,0,0,0,0,216,96,0,0,0,0,216,96,0,0,0,0,204,96,0,0,0,0,204,96,0,0,0,0,204,192,0,0,0,0,108,192,0,0,0,0,108,192,0,0,0,0,120,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,56,192,0,0,0,1,248,192,0,0,0,7,248,192,0,0,0,15,8,192,0,0,0,12,12,192,0,0,0,12,124,192,0,0,0,15,252,64,0,0,0,7,140,96,0,0,0,0,12,96,0,0,0,0,12,96,0,0,0,0,12,96,0,0,0,0,15,192,0,0,0,0,7,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,96,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,48,24,0,0,0,0,50,16,0,0,0,0,102,48,0,0,0,0,102,48,0,0,0,0,204,48,0,0,0,0,204,96,0,0,0,0,108,96,0,0,0,0,108,96,0,0,0,0,102,96,0,0,0,0,102,192,0,0,0,0,118,192,0,0,0,0,118,192,0,0,0,0,124,192,0,0,0,0,56,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,248,192,0,0,0,1,248,192,0,0,0,3,24,192,0,0,0,3,56,192,0,0,0,3,248,192,0,0,0,1,248,192,0,0,0,0,24,192,0,0,0,0,24,192,0,0,0,0,25,128,0,0,0,0,31,128,0,0,0,0,15,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,96,0,0,0,0,0,0,0,0,0,0,7,224,0,0,0,0,15,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,48,24,0,0,0,0,50,16,0,0,0,0,54,48,0,0,0,0,102,48,0,0,0,0,102,48,0,0,0,0,110,48,0,0,0,0,102,96,0,0,0,0,102,96,0,0,0,0,55,96,0,0,0,0,51,192,0,0,0,0,51,192,0,0,0,0,123,192,0,0,0,0,127,192,0,0,0,0,46,192,0,0,0,0,32,128,0,0,0,0,49,128,0,0,0,0,49,128,0,0,0,0,49,128,0,0,0,0,49,128,0,0,0,0,113,128,0,0,0,0,113,128,0,0,0,0,241,128,0,0,0,0,241,128,0,0,0,0,113,0,0,0,0,0,51,0,0,0,0,0,51,0,0,0,0,0,51,0,0,0,0,0,63,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,156,0,0,0,0,6,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,240,0,0,0,0,24,48,0,0,0,0,24,24,0,0,0,0,48,24,0,0,0,0,51,24,0,0,0,0,115,48,0,0,0,0,115,48,0,0,0,0,102,48,0,0,0,0,102,48,0,0,0,0,102,96,0,0,0,0,115,96,0,0,0,0,115,224,0,0,0,0,121,192,0,0,0,0,121,192,0,0,0,0,109,192,0,0,0,0,111,192,0,0,0,0,103,128,0,0,0,0,97,128,0,0,0,0,97,128,0,0,0,0,97,128,0,0,0,0,99,192,0,0,0,0,99,192,0,0,0,0,99,192,0,0,0,0,99,128,0,0,0,0,99,128,0,0,0,0,99,0,0,0,0,0,98,0,0,0,0,0,102,0,0,0,0,0,70,0,0,0,0,0,70,0,0,0,0,0,110,0,0,0,0,0,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,248,0,0,0,0,3,156,0,0,0,0,6,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,4,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,224,0,0,0,0,24,48,0,0,0,0,24,24,0,0,0,0,48,24,0,0,0,0,115,24,0,0,0,0,243,48,0,0,0,0,243,48,0,0,0,0,243,48,0,0,0,1,179,48,0,0,0,1,179,96,0,0,0,1,179,224,0,0,0,1,185,224,0,0,0,1,248,192,0,0,0,0,108,192,0,0,0,0,110,96,0,0,0,0,103,192,0,0,0,0,99,192,0,0,0,0,97,128,0,0,0,0,97,192,0,0,0,0,99,224,0,0,0,0,99,96,0,0,0,0,199,96,0,0,0,0,198,96,0,0,0,0,198,224,0,0,0,0,198,192,0,0,0,0,198,192,0,0,0,0,207,128,0,0,0,0,143,128,0,0,0,1,140,0,0,0,0,1,140,0,0,0,0,1,220,0,0,0,0,0,248,0,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,248,0,0,0,0,3,252,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,3,12,0,0,0,0,3,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,224,0,0,0,0,28,112,0,0,0,0,56,24,0,0,0,0,120,24,0,0,0,0,241,24,0,0,0,1,179,48,0,0,0,1,179,48,0,0,0,3,179,48,0,0,0,3,51,48,0,0,0,3,51,224,0,0,0,3,121,224,0,0,0,3,124,224,0,0,0,3,252,96,0,0,0,1,230,48,0,0,0,0,99,48,0,0,0,0,99,224,0,0,0,0,97,224,0,0,0,0,97,192,0,0,0,0,97,224,0,0,0,0,99,96,0,0,0,0,99,48,0,0,0,0,67,48,0,0,0,0,199,48,0,0,0,0,199,48,0,0,0,0,199,48,0,0,0,1,143,96,0,0,0,1,143,96,0,0,0,1,143,224,0,0,0,3,155,192,0,0,0,3,24,0,0,0,0,3,56,0,0,0,0,1,240,0,0,0,0,0,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,3,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,224,0,0,0,0,28,112,0,0,0,0,120,56,0,0,0,0,248,24,0,0,0,1,217,24,0,0,0,3,155,48,0,0,0,3,59,48,0,0,0,3,59,48,0,0,0,6,123,48,0,0,0,6,121,224,0,0,0,6,120,224,0,0,0,6,252,112,0,0,0,7,246,56,0,0,0,3,227,24,0,0,0,0,97,152,0,0,0,0,96,240,0,0,0,0,97,224,0,0,0,0,97,224,0,0,0,0,97,224,0,0,0,0,99,48,0,0,0,0,99,48,0,0,0,0,99,24,0,0,0,0,199,24,0,0,0,0,199,152,0,0,0,1,207,152,0,0,0,1,141,152,0,0,0,3,141,152,0,0,0,3,25,152,0,0,0,3,25,248,0,0,0,6,48,240,0,0,0,6,48,96,0,0,0,3,224,0,0,0,0,1,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,15,224,0,0,0,0,28,112,0,0,0,0,120,56,0,0,0,0,248,24,0,0,0,1,217,24,0,0,0,3,25,48,0,0,0,3,57,176,0,0,0,6,57,176,0,0,0,6,121,176,0,0,0,6,121,224,0,0,0,12,248,240,0,0,0,12,254,56,0,0,0,7,247,24,0,0,0,3,227,140,0,0,0,0,96,252,0,0,0,0,96,248,0,0,0,0,97,240,0,0,0,0,97,224,0,0,0,0,97,176,0,0,0,0,99,56,0,0,0,0,99,24,0,0,0,0,99,152,0,0,0,0,199,140,0,0,0,0,199,140,0,0,0,1,199,140,0,0,0,1,140,204,0,0,0,3,28,198,0,0,0,7,24,198,0,0,0,6,48,198,0,0,0,4,48,124,0,0,0,6,96,124,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,15,224,0,0,0,0,29,240,0,0,0,0,56,56,0,0,0,0,248,24,0,0,0,1,217,24,0,0,0,1,153,48,0,0,0,3,25,176,0,0,0,3,57,176,0,0,0,6,121,176,0,0,0,6,121,224,0,0,0,12,124,112,0,0,0,12,254,56,0,0,0,7,247,28,0,0,0,7,227,204,0,0,0,0,96,252,0,0,0,0,96,252,0,0,0,0,97,240,0,0,0,0,97,224,0,0,0,0,97,176,0,0,0,0,99,24,0,0,0,0,99,24,0,0,0,0,99,140,0,0,0,0,199,140,0,0,0,0,199,140,0,0,0,1,134,198,0,0,0,3,140,198,0,0,0,3,28,198,0,0,0,6,24,99,0,0,0,6,48,99,0,0,0,12,112,102,0,0,0,12,96,62,0,0,0,15,192,28,0,0,0,7,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,15,224,0,0,0,0,28,112,0,0,0,0,56,56,0,0,0,0,120,24,0,0,0,0,249,24,0,0,0,1,219,48,0,0,0,1,153,176,0,0,0,3,57,176,0,0,0,7,57,176,0,0,0,6,121,224,0,0,0,14,124,112,0,0,0,12,254,56,0,0,0,7,247,24,0,0,0,3,225,204,0,0,0,0,96,252,0,0,0,0,96,248,0,0,0,0,97,224,0,0,0,0,97,224,0,0,0,0,97,176,0,0,0,0,99,56,0,0,0,0,99,24,0,0,0,0,99,24,0,0,0,0,99,140,0,0,0,0,199,140,0,0,0,1,135,140,0,0,0,1,140,198,0,0,0,3,28,198,0,0,0,6,24,198,0,0,0,14,48,98,0,0,0,12,112,102,0,0,0,14,96,62,0,0,0,7,192,28,0,0,0,3,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,224,0,0,0,0,28,112,0,0,0,0,24,56,0,0,0,0,24,24,0,0,0,0,25,24,0,0,0,0,59,48,0,0,0,0,59,48,0,0,0,0,123,48,0,0,0,0,121,176,0,0,0,0,249,224,0,0,0,0,252,224,0,0,0,1,190,112,0,0,0,1,247,48,0,0,0,0,227,152,0,0,0,0,97,240,0,0,0,0,96,224,0,0,0,0,96,192,0,0,0,0,97,224,0,0,0,0,97,240,0,0,0,0,97,176,0,0,0,0,99,24,0,0,0,0,99,24,0,0,0,0,99,24,0,0,0,0,195,140,0,0,0,1,199,140,0,0,0,3,143,140,0,0,0,3,29,198,0,0,0,6,24,198,0,0,0,6,48,198,0,0,0,6,112,102,0,0,0,7,224,126,0,0,0,3,192,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,2,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,224,0,0,0,0,24,48,0,0,0,0,24,24,0,0,0,0,24,24,0,0,0,0,19,24,0,0,0,0,19,48,0,0,0,0,51,48,0,0,0,0,51,48,0,0,0,0,51,176,0,0,0,0,57,224,0,0,0,0,60,224,0,0,0,0,60,96,0,0,0,0,54,96,0,0,0,0,103,96,0,0,0,0,99,224,0,0,0,0,97,192,0,0,0,0,96,192,0,0,0,0,97,224,0,0,0,0,97,224,0,0,0,0,97,240,0,0,0,0,97,176,0,0,0,0,33,176,0,0,0,0,99,24,0,0,0,0,227,24,0,0,0,1,199,24,0,0,0,3,143,140,0,0,0,3,29,140,0,0,0,6,25,140,0,0,0,6,48,198,0,0,0,7,224,198,0,0,0,3,192,252,0,0,0,0,0,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,3,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,24,24,0,0,0,0,48,24,0,0,0,0,51,24,0,0,0,0,51,48,0,0,0,0,51,48,0,0,0,0,51,48,0,0,0,0,51,48,0,0,0,0,51,96,0,0,0,0,57,224,0,0,0,0,57,224,0,0,0,0,60,224,0,0,0,0,108,192,0,0,0,0,103,192,0,0,0,0,99,192,0,0,0,0,96,192,0,0,0,0,96,192,0,0,0,0,48,224,0,0,0,0,49,224,0,0,0,0,49,224,0,0,0,0,49,176,0,0,0,0,113,176,0,0,0,0,227,176,0,0,0,1,199,24,0,0,0,3,143,24,0,0,0,3,31,24,0,0,0,3,57,140,0,0,0,3,241,140,0,0,0,1,225,140,0,0,0,0,0,220,0,0,0,0,0,120,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,248,0,0,0,0,3,252,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,4,0,0,0,0,3,12,0,0,0,0,3,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,15,240,0,0,0,0,24,48,0,0,0,0,24,24,0,0,0,0,48,24,0,0,0,0,51,24,0,0,0,0,51,56,0,0,0,0,102,56,0,0,0,0,102,56,0,0,0,0,102,56,0,0,0,0,119,120,0,0,0,0,51,120,0,0,0,0,51,120,0,0,0,0,57,216,0,0,0,0,121,216,0,0,0,0,127,248,0,0,0,0,111,248,0,0,0,0,96,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,24,192,0,0,0,0,24,224,0,0,0,0,57,224,0,0,0,0,49,224,0,0,0,0,99,96,0,0,0,0,231,96,0,0,0,0,198,48,0,0,0,0,206,48,0,0,0,0,254,48,0,0,0,0,123,48,0,0,0,0,3,240,0,0,0,0,1,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,156,0,0,0,0,6,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,48,24,0,0,0,0,51,24,0,0,0,0,102,56,0,0,0,0,102,56,0,0,0,0,102,56,0,0,0,0,108,120,0,0,0,0,102,120,0,0,0,0,102,108,0,0,0,0,102,108,0,0,0,0,114,236,0,0,0,0,51,244,0,0,0,0,62,252,0,0,0,0,60,216,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,48,192,0,0,0,0,24,96,0,0,0,0,24,96,0,0,0,0,28,96,0,0,0,0,28,192,0,0,0,0,24,192,0,0,0,0,25,128,0,0,0,0,25,128,0,0,0,0,51,128,0,0,0,0,51,128,0,0,0,0,55,128,0,0,0,0,30,128,0,0,0,0,15,128,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,96,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,48,24,0,0,0,0,98,24,0,0,0,0,102,56,0,0,0,0,198,56,0,0,0,0,204,56,0,0,0,0,204,124,0,0,0,0,204,108,0,0,0,0,204,110,0,0,0,0,204,119,0,0,0,0,204,251,0,0,0,0,100,223,0,0,0,0,124,206,0,0,0,0,124,192,0,0,0,0,48,96,0,0,0,0,48,96,0,0,0,0,56,96,0,0,0,0,60,96,0,0,0,0,60,48,0,0,0,0,30,48,0,0,0,0,30,96,0,0,0,0,62,96,0,0,0,0,62,96,0,0,0,0,60,96,0,0,0,0,60,192,0,0,0,0,60,192,0,0,0,0,44,192,0,0,0,0,63,128,0,0,0,0,63,0,0,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,12,0,0,0,0,6,4,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,96,0,0,0,0,0,0,0,0,0,0,15,224,0,0,0,0,31,240,0,0,0,0,24,48,0,0,0,0,48,24,0,0,0,0,112,24,0,0,0,0,102,24,0,0,0,0,198,56,0,0,0,1,204,60,0,0,0,1,156,60,0,0,0,1,152,60,0,0,0,1,152,103,0,0,0,1,152,115,128,0,0,1,152,113,192,0,0,1,152,252,192,0,0,1,152,207,192,0,0,1,240,195,128,0,0,0,240,192,0,0,0,0,112,96,0,0,0,0,56,96,0,0,0,0,56,48,0,0,0,0,60,48,0,0,0,0,54,48,0,0,0,0,55,16,0,0,0,0,51,48,0,0,0,0,99,48,0,0,0,0,103,48,0,0,0,0,103,48,0,0,0,0,199,48,0,0,0,0,207,48,0,0,0,0,207,48,0,0,0,0,143,224,0,0,0,0,249,224,0,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,240,0,0,0,0,1,248,0,0,0,0,3,156,0,0,0,0,6,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,12,0,0,0,0,3,12,0,0,0,0,1,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,31,240,0,0,0,0,56,48,0,0,0,0,112,24,0,0,0,0,96,24,0,0,0,0,192,24,0,0,0,1,140,60,0,0,0,3,156,60,0,0,0,3,56,52,0,0,0,3,56,55,0,0,0,3,48,115,192,0,0,3,112,112,224,0,0,6,112,120,112,0,0,6,112,222,48,0,0,6,96,199,224,0,0,7,224,193,192,0,0,3,224,224,0,0,0,0,112,96,0,0,0,0,120,112,0,0,0,0,124,48,0,0,0,0,110,24,0,0,0,0,102,24,0,0,0,0,103,24,0,0,0,0,103,152,0,0,0,0,199,152,0,0,0,0,207,152,0,0,0,1,141,152,0,0,0,1,141,136,0,0,0,3,25,136,0,0,0,3,25,136,0,0,0,3,48,216,0,0,0,3,240,248,0,0,0,1,224,112,0,0,0,0,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,248,0,0,0,0,3,252,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,4,0,0,0,0,3,12,0,0,0,0,3,248,0,0,0,0,0,240,0,0,0,0,0,0,0,0,0,0,7,192,0,0,0,0,31,224,0,0,0,0,56,112,0,0,0,0,112,24,0,0,0,0,224,24,0,0,0,1,192,28,0,0,0,3,140,60,0,0,0,3,24,54,0,0,0,6,56,54,0,0,0,6,120,51,192,0,0,6,112,113,240,0,0,12,240,120,56,0,0,12,240,126,24,0,0,12,240,79,248,0,0,25,224,193,240,0,0,13,224,192,0,0,0,15,96,224,0,0,0,0,112,96,0,0,0,0,120,48,0,0,0,0,124,48,0,0,0,0,110,24,0,0,0,0,103,28,0,0,0,0,71,140,0,0,0,0,199,140,0,0,0,1,196,204,0,0,0,1,140,204,0,0,0,3,28,198,0,0,0,7,24,198,0,0,0,6,48,198,0,0,0,12,48,70,0,0,0,12,96,102,0,0,0,14,224,126,0,0,0,7,192,60,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,240,0,0,0,0,3,248,0,0,0,0,3,12,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,6,6,0,0,0,0,3,12,0,0,0,0,3,252,0,0,0,0,1,248,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,31,224,0,0,0,0,56,112,0,0,0,0,112,56,0,0,0,0,224,24,0,0,0,3,128,28,0,0,0,7,8,62,0,0,0,6,56,54,0,0,0,14,120,51,128,0,0,12,248,51,240,0,0,12,240,120,120,0,0,25,176,124,12,0,0,25,176,111,140,0,0,25,176,99,252,0,0,51,96,192,120,0,0,51,96,192,0,0,0,30,96,224,0,0,0,12,112,96,0,0,0,0,120,48,0,0,0,0,124,56,0,0,0,0,206,28,0,0,0,0,199,12,0,0,0,0,199,140,0,0,0,1,205,198,0,0,0,1,140,198,0,0,0,3,12,198,0,0,0,7,24,102,0,0,0,6,56,99,0,0,0,12,48,99,0,0,0,24,96,99,0,0,0,24,192,99,0,0,0,25,192,51,0,0,0,31,128,63,0,0,0,15,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const unsigned char xochi [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x49, 0x24, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x22, 0x24, 0x90, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x80, 0x00, 0x00, 0x00, 0x08, 0x80, 0x04, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x70, 0x00, 0x00, 0x00, 0x00, 0x12, 0x41, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xdd, 0x00, 0x01, 0x9c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x12, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x93, 0x40, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x24, 0x88, 
	0x00, 0x00, 0x00, 0x00, 0x09, 0x25, 0x32, 0xd0, 0x02, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 
	0x00, 0x00, 0x00, 0x00, 0x49, 0x19, 0x4c, 0xb6, 0x00, 0x19, 0x80, 0x00, 0x00, 0x00, 0x09, 0x31, 
	0x00, 0x00, 0x00, 0x02, 0x24, 0xc9, 0x37, 0x2d, 0x81, 0x1a, 0xe0, 0x00, 0x00, 0x00, 0x01, 0x0c, 
	0x00, 0x00, 0x00, 0x08, 0x92, 0x64, 0xd3, 0x69, 0x78, 0x26, 0x78, 0x00, 0x00, 0x00, 0x14, 0xce, 
	0x00, 0x00, 0x00, 0x24, 0x93, 0x33, 0x5c, 0xdb, 0x4e, 0x0d, 0x4c, 0x00, 0x00, 0x00, 0x04, 0xb3, 
	0x00, 0x00, 0x00, 0x93, 0x25, 0x83, 0x6e, 0x96, 0xe7, 0xc1, 0x64, 0x00, 0x00, 0x00, 0x03, 0x35, 
	0x00, 0x00, 0x01, 0x18, 0x99, 0x84, 0x93, 0x66, 0xb9, 0x72, 0x5c, 0x00, 0x00, 0x00, 0x02, 0x4c, 
	0x00, 0x00, 0x05, 0x66, 0xce, 0x0d, 0xb0, 0x4b, 0x6e, 0x5a, 0x4c, 0x00, 0x00, 0x00, 0x01, 0xdb, 
	0x00, 0x00, 0x04, 0xa4, 0x66, 0x89, 0x20, 0x99, 0x9b, 0xcd, 0x84, 0x00, 0x00, 0x00, 0x08, 0x33, 
	0x00, 0x00, 0x0a, 0x99, 0x99, 0x0c, 0xc0, 0x16, 0xd9, 0xb5, 0x30, 0x00, 0x00, 0x00, 0x20, 0xac, 
	0x00, 0x00, 0x1a, 0xdb, 0x6d, 0x13, 0x00, 0x16, 0xe6, 0xb6, 0xc8, 0x00, 0x00, 0x04, 0x84, 0xcd, 
	0x00, 0x00, 0x13, 0x36, 0x66, 0x14, 0x00, 0x65, 0xbe, 0xdb, 0xbb, 0x00, 0x00, 0x00, 0x12, 0x73, 
	0x00, 0x00, 0x2d, 0xb6, 0xda, 0x14, 0x00, 0x4d, 0x93, 0x5b, 0x66, 0xc0, 0x00, 0x00, 0x0b, 0x2c, 
	0x00, 0x00, 0x26, 0xdb, 0x9c, 0x13, 0x07, 0x33, 0xf5, 0xcd, 0xdc, 0xd0, 0x00, 0x00, 0x6d, 0xad, 
	0x00, 0x00, 0x76, 0x6d, 0x64, 0x28, 0x0e, 0x4e, 0x6d, 0x76, 0xd3, 0x30, 0x00, 0x03, 0x24, 0xd3, 
	0x00, 0x00, 0x19, 0xb7, 0x7c, 0x24, 0x06, 0x4b, 0xef, 0x76, 0xff, 0xdc, 0x00, 0xc8, 0x9b, 0x52, 
	0x00, 0x00, 0xcf, 0xb6, 0xcc, 0x10, 0x03, 0x33, 0xbb, 0x9b, 0x2c, 0xdf, 0x00, 0x12, 0xdb, 0x6d, 
	0x00, 0x00, 0x69, 0xee, 0xf2, 0x48, 0x12, 0x8d, 0xee, 0xed, 0xf7, 0x33, 0x00, 0x44, 0x4c, 0xa7, 
	0x00, 0x00, 0x5b, 0x6b, 0xb8, 0x20, 0x02, 0x8d, 0xfd, 0xed, 0x9b, 0xed, 0x80, 0x25, 0xa6, 0xda, 
	0x00, 0x00, 0x9b, 0x7b, 0x6c, 0x90, 0x02, 0x67, 0x77, 0x6e, 0xee, 0xdd, 0xc9, 0x01, 0x33, 0x5b, 
	0x00, 0x00, 0xb6, 0xdd, 0xec, 0x94, 0x02, 0x13, 0xdf, 0xd3, 0x7b, 0x76, 0x62, 0x10, 0x5b, 0x6f, 
	0x00, 0x00, 0x66, 0xd6, 0xb2, 0x44, 0x0c, 0x9b, 0xfd, 0xdd, 0x5b, 0x6f, 0xa0, 0x84, 0xcc, 0xb6, 
	0x00, 0x00, 0x6d, 0x76, 0xde, 0x50, 0x08, 0x4f, 0x7f, 0x77, 0xad, 0xb9, 0xe4, 0x20, 0x24, 0xdf, 
	0x00, 0x01, 0x33, 0x6d, 0xe9, 0x92, 0x03, 0x27, 0xfb, 0xb6, 0xb6, 0xde, 0xd1, 0x09, 0x27, 0x79, 
	0x00, 0x00, 0x9c, 0xdb, 0x3a, 0x64, 0x94, 0xbe, 0xee, 0xec, 0xdb, 0x67, 0xb0, 0x42, 0x19, 0xef, 
	0x00, 0x00, 0xc7, 0xb6, 0xf6, 0xc8, 0x14, 0xfb, 0xff, 0xbb, 0x69, 0xbd, 0xa0, 0x10, 0x87, 0xbf, 
	0x00, 0x01, 0x69, 0x6d, 0xd5, 0x99, 0x2f, 0x6f, 0xb3, 0x6b, 0x66, 0xdb, 0x71, 0x04, 0x2d, 0xf6, 
	0x00, 0x01, 0x1b, 0x6d, 0x9d, 0x64, 0x89, 0xdc, 0xdd, 0x6c, 0x9a, 0x6e, 0xd0, 0x01, 0x3b, 0x7f, 
	0x00, 0x02, 0x5a, 0xd3, 0xeb, 0x66, 0x7b, 0xb7, 0x4d, 0xb7, 0xa9, 0xa6, 0xe4, 0x10, 0x9f, 0xdb, 
	0x00, 0x02, 0x66, 0xde, 0x6a, 0x99, 0x5e, 0xe9, 0x26, 0xf6, 0x6c, 0x9b, 0x60, 0x02, 0x6d, 0xff, 
	0x00, 0x01, 0x99, 0xad, 0xb6, 0xb7, 0x96, 0xdf, 0xf3, 0xdb, 0x42, 0x69, 0x98, 0x00, 0xff, 0xbd, 
	0x00, 0x00, 0x9b, 0x6f, 0x9d, 0x26, 0xfb, 0x76, 0xd9, 0x6d, 0x43, 0x6e, 0xc0, 0x01, 0xb6, 0xf7, 
	0x00, 0x02, 0x66, 0xda, 0x65, 0xcd, 0xed, 0xb3, 0x61, 0xb6, 0x45, 0x93, 0x70, 0x01, 0xbf, 0xff, 
	0x00, 0x02, 0x35, 0x9b, 0xec, 0x5b, 0x7d, 0xaf, 0x40, 0xdb, 0x84, 0xdd, 0x24, 0x03, 0xef, 0xdb, 
	0x00, 0x00, 0x93, 0x66, 0x9b, 0x26, 0xde, 0xfd, 0xc0, 0xd9, 0x8b, 0x25, 0xa8, 0x06, 0xfd, 0xff, 
	0x00, 0x01, 0x9a, 0x6c, 0xd1, 0x21, 0xb3, 0xdf, 0x01, 0xb6, 0x19, 0xac, 0xd0, 0x07, 0xbf, 0xbd, 
	0x00, 0x00, 0x23, 0x9b, 0x4c, 0x40, 0x6f, 0x7e, 0xc5, 0x66, 0x14, 0xcb, 0x50, 0x0d, 0xfb, 0xf7, 
	0x00, 0x02, 0x24, 0xd3, 0x20, 0x02, 0x4d, 0xee, 0xc3, 0x58, 0x36, 0x53, 0x68, 0x0f, 0x7f, 0x7e, 
	0x00, 0x00, 0x96, 0x54, 0x82, 0x00, 0x92, 0xbf, 0x23, 0x98, 0x39, 0x35, 0xa8, 0x1b, 0xf7, 0xef, 
	0x00, 0x00, 0x13, 0x36, 0x08, 0x01, 0x32, 0xfd, 0x84, 0xe2, 0x69, 0x8c, 0xc8, 0x1e, 0xff, 0xbb, 
	0x00, 0x00, 0x41, 0x28, 0x00, 0x01, 0x2d, 0x36, 0x51, 0x70, 0x76, 0x03, 0x70, 0x37, 0xee, 0xfd, 
	0x00, 0x00, 0x0c, 0x48, 0x00, 0x00, 0x95, 0x6c, 0x43, 0x30, 0x74, 0x5b, 0x50, 0x3d, 0xff, 0xed, 
	0x00, 0x00, 0x00, 0xd0, 0x00, 0x06, 0xd6, 0xd9, 0x02, 0xc4, 0xe8, 0x05, 0xd8, 0x4f, 0xdd, 0xfb, 
	0x00, 0x00, 0x02, 0x20, 0x00, 0x1e, 0x6a, 0x30, 0x04, 0xf0, 0xea, 0x0d, 0x20, 0x7f, 0xff, 0x77, 
	0x00, 0x00, 0x00, 0xa0, 0x10, 0x1c, 0x39, 0x64, 0x05, 0x82, 0xd8, 0x1b, 0x64, 0x76, 0xf7, 0xdd, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x39, 0xb7, 0x30, 0x06, 0xc1, 0xd0, 0x12, 0xc0, 0xff, 0xbe, 0xef, 
	0x00, 0x00, 0x01, 0x40, 0x40, 0x66, 0x6e, 0x90, 0x08, 0x83, 0xe0, 0x3e, 0x99, 0xbb, 0xef, 0xbb, 
	0x00, 0x00, 0x00, 0x41, 0x10, 0x04, 0x6e, 0xc0, 0x1b, 0x07, 0x3d, 0xef, 0xf7, 0x6f, 0xfb, 0xf6, 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x09, 0x37, 0xec, 0x44, 0xff, 0xff, 0xf9, 0x0d, 0xfe, 0xde, 0x77, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x1b, 0xdd, 0xbf, 0xff, 0xfe, 0xff, 0x37, 0xc9, 0xbf, 0xf7, 0xdd, 
	0x00, 0x00, 0x00, 0x02, 0xff, 0xfe, 0xff, 0x7b, 0xff, 0xdb, 0xdb, 0xdc, 0xf3, 0xed, 0xbd, 0xf7, 
	0x00, 0x00, 0x00, 0x7f, 0xf7, 0x67, 0xb3, 0xdf, 0xed, 0xff, 0x76, 0xdb, 0x36, 0xff, 0xef, 0x7d, 
	0x00, 0x40, 0x07, 0xdb, 0x59, 0xdd, 0xee, 0xf7, 0x7e, 0x66, 0xdd, 0x66, 0x4f, 0xb6, 0xfb, 0xcd, 
	0x6f, 0x5f, 0xfd, 0xb7, 0x6f, 0xdd, 0xbf, 0xbd, 0xdb, 0xdd, 0xb5, 0xb4, 0xcd, 0xff, 0xbe, 0xff, 
	0x24, 0xb2, 0xdb, 0x3d, 0xbe, 0x76, 0xdb, 0xde, 0xf7, 0x77, 0x6d, 0x99, 0x9f, 0x6d, 0xe7, 0xb3
};

long demo_mode;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
  display.clearDisplay();
  display.display();

  EEPROM.get(0, demo_mode);
  demo_mode = (demo_mode + 1) % 4;
  EEPROM.put(0, demo_mode);
}

int frame = 0;
void loop() {
  switch (demo_mode) {
    case 0:
      // hello
      display.clearDisplay();
      display.drawBitmap(0, 0, hello, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
      break;
  case 1:
    // quote
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.cp437(true); // use 256-character 'code page 437' font

    display.clearDisplay();
    display.setTextSize(2);
    display.println(F(" a moment"));
    display.println(F(" a love"));
    display.println(F(" a dream"));
    display.println(F(" aloud."));
    break;
  case 2:
    // walk animation
    display.clearDisplay();
    display.drawBitmap(40, 8, walk_frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
    frame = (frame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
    break;
  default:
    // xochi
    display.clearDisplay();
    display.drawBitmap(0, 0, xochi, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    break;
  }
  display.display();
}
