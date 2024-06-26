// color macro
#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

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
