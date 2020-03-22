#include <Arduino.h>
#include <hcsr04.h>
#include "EEPROM.h"

#define TRIGGER_PIN 3 //HCR04 Trigger set to pin 3
#define ECHO_PIN 5 // HCR04 Echo set to Pin 5
#define LO_LEVEL 0
#define HI_LEVEL 1
#define SWITCH 4

HCSR04 hcsr04(TRIGGER_PIN, ECHO_PIN, 20, 4000);
int distanceL, distanceH;

void setup()
{
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(LO_LEVEL, OUTPUT);
  pinMode(HI_LEVEL, OUTPUT);
  EEPROM.get( 0, distanceL);
  EEPROM.get( sizeof(int), distanceH);
}

void loop()
{
  int distance = hcsr04.distanceInMillimeters()/10;
  if (digitalRead(SWITCH) == 0)
  {
    pinMode(LO_LEVEL, INPUT_PULLUP);
    pinMode(HI_LEVEL, INPUT_PULLUP);
    if ((digitalRead(LO_LEVEL) == 0) && (distanceL != distance))
    {
      distanceL = distance;
      EEPROM.put(0, distanceL);
    };
    if ((digitalRead(HI_LEVEL) == 0) && (distanceH != distance))
    {
      distanceH = distance;
      EEPROM.put(sizeof(int), distanceH);
    };
  } 
  else
  {
    pinMode(LO_LEVEL, OUTPUT);
    pinMode(HI_LEVEL, OUTPUT);
    (distanceL > distance)?digitalWrite(LO_LEVEL, 1):digitalWrite(LO_LEVEL, 0);
    (distanceH > distance)?digitalWrite(HI_LEVEL, 1):digitalWrite(HI_LEVEL, 0);
  }
  delay(100);
}