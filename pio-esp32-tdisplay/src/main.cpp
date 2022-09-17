#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Wire.h>
#include <Button2.h>
#include <Adafruit_MAX31865.h>

#include "config.h"


// init display
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); 

// init thermometer
Adafruit_MAX31865 thermo = Adafruit_MAX31865(
  PIN_THERMO_CS, 
  PIN_THERMO_DI, 
  PIN_THERMO_DO, 
  PIN_THERMO_CLK
);


void setup_tft(){
  tft.init();
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); 
  tft.setSwapBytes(true);
  tft.setRotation(TFT_ROTATION);
  tft.fillScreen(TFT_BLACK);
}

void setup(){
  Serial.begin(SERIAL_BAUD);

  setup_tft();
  tft.setTextSize(4);
  tft.setCursor(0, 0);
  tft.print("init");


  thermo.begin(MAX31865_2WIRE);
}



void loop(){

  uint16_t rtd = thermo.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("RTD = "); Serial.println(rtd);
  Serial.print("Ratio = "); Serial.println(ratio,8);
  Serial.print("Resistance = "); Serial.println(THERMO_RREF*ratio,8);
  Serial.print("Temperature = "); Serial.println(thermo.temperature(THERNMO_RNOMINAL, THERMO_RREF));

  // Check and print any faults
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    thermo.clearFault();
  }
  Serial.println();


  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.print(thermo.temperature(THERNMO_RNOMINAL, THERMO_RREF));


  delay(100);

}
