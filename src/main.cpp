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
#include <TimerThree.h>

#define outPin 9            // Connect the transistor's base to pin 9
#define igniterPin 10       // Connect to igniter transistor's base pin
#define trigPin 10          // Fuel Level Sensor Trigger Pin
#define echoPin 13          // Fuel Level Sensor Echo Pin
double duration, fuelLevel; // Fuel Level Values
bool pumpState = true;      // true will speed up the pumps, false will do the opposite

volatile unsigned long speedVal = 0;     // Variable to hold pump speed value
volatile unsigned long incrementVal = 1; // Variable to hold pump speed increment value
volatile unsigned long decrementVal = 1; // Variable to hold pump speed decrement value

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outPin, OUTPUT);
  pinMode(igniterPin, OUTPUT);
  Timer3.initialize(150000);
  Timer3.attachInterrupt(increment);
}

void increment()
{
  if (pumpState == true)
  {
    if (speedVal < 255)
    {
      speedVal + incrementVal; // Each increment will increase the fuel flow by approx 7.8ml per minute
    }
    else
    {
    }
  }
  else
  {
    speedVal - decrementVal;
  }
}

double getFuelLevel()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  fuelLevel = (duration / 2) * 0.0343;
  return fuelLevel;
}

void parachute()
{
  pumpState = false;

  analogWrite(outPin, 0);
  digitalWrite(igniterPin, LOW);
}

void loop()
{
  getFuelLevel();
  if (fuelLevel < 15.0)
  {
    pumpState = false;
    decrementVal = 1;
    digitalWrite(igniterPin, HIGH);
    analogWrite(outPin, speedVal);
  }
  // Start Igniter
  digitalWrite(igniterPin, HIGH);
  // Write PWM to transistor
  analogWrite(outPin, speedVal);
}
