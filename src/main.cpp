
#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 4, /* data=*/ 5);   // ESP32 Thing, HW I2C with pin remapping


void setup() {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_7x14B_tf);	// choose a suitable font

  u8g2.setCursor(0, 15);
  u8g2.println("Hello World!");
  u8g2.setCursor(0, 30);
  u8g2.println("second line");
  u8g2.setCursor(0, 45);
  u8g2.println("and so on ....");
  
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
}