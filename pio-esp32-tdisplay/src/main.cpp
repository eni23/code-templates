#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Wire.h>
#include <Button2.h>

#include "config.h"


TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT); 

void setup_tft(){
  tft.init();
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); 
  tft.setSwapBytes(true);
  tft.setRotation(TFT_ROTATION);
  tft.fillScreen(TFT_BLACK);
}

void setup(){

}


void loop(){

}
