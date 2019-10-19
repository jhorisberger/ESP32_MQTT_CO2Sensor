
#include <Arduino.h>
#include <U8g2lib.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 4, /* data=*/ 5);   // ESP32 Thing, HW I2C with pin remapping

const int swSeria_rx_pin = 13; //Serial rx pin no
const int swSeria_tx_pin = 15; //Serial tx pin no
const bool swSerialInvert = false;
const int swSeria_baud = 9600;
SoftwareSerial co2Serial;

MHZ19 mhz19;                                        // Constructor for MH-Z19 class
int CO2;                                            // Buffer for CO2
int8_t Temp;                                        // Buffer for temperature

unsigned long getDataTimer = 0;                     // Variable to store timer interval


void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_7x14B_tf);	// choose a suitable font

  Serial.begin(9600);
  delay(100);

  co2Serial.begin(swSeria_baud, swSeria_rx_pin, swSeria_tx_pin, SWSERIAL_8N1, swSerialInvert);
  delay(100);

  mhz19.begin(co2Serial);          // *Important, Pass your Stream reference 
  mhz19.autoCalibration();         // Turn auto calibration ON (disable with autoCalibration(false))
  mhz19.setFilter(true, false);
  

  delay(1000);
}

void loop(void) {

   if (millis() - getDataTimer >= 10000)                    // Check if interval has elapsed (non-blocking delay() equivilant)
   {

    CO2 = mhz19.getCO2();                         // Request CO2 (as ppm)
    Temp = mhz19.getTemperature();                     // Request Temperature (as Celsius)


    u8g2.clearBuffer();					// clear the internal memory

    u8g2.setCursor(0, 15);
    u8g2.print("CO2 (ppm): ");
    u8g2.print(CO2);
    
    u8g2.setCursor(0, 30);
    u8g2.print("Temp (C): ");                  
    u8g2.println(Temp);  

    u8g2.sendBuffer();					// transfer internal memory to the display                          

    getDataTimer = millis();         // Update interval
  }
}