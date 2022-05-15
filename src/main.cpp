/*
  SpeedBird 0 Thrust Control Code
  Written By Aadiraj Anil
  Install TimerOne library before uploading
  Connect the transistor base to pin 9
  With 120 litres per hour (2 litres per minute), each increment will increase
  fuel flow by 7.8ml per minute.
  100% Fuel Flow - speedVal = 255
  50% Fuel Flow - speedVal = 127.5
  25% Fuel Flow - speedVal = 63.75
  10% Fuel Flow - speedVal = 25.5
  5% Fuel Flow - speedVal = 12.75
  1% Fuel Flow - speedVal = 2.55
*/

#include <Arduino.h>
#include <TimerOne.h>

int outPin = 9; // Connect the transistor's base to pin 9

// Variable to hold pump speed value
volatile unsigned long speedVal = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(outPin, OUTPUT);
  Timer1.initialize(150000);
  Timer1.attachInterrupt(increment);
}

void increment()
{
  while (speedVal < 255)
  {
    speedVal++; // Each increment will increase the fuel flow by approx 7.8ml per minute
  }
}

void loop()
{
  // Write PWM to transistor
  analogWrite(outPin, speedVal);
}
