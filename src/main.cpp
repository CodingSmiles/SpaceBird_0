/*
  SpeedBird 0 Thrust Control Code
  Written By Aadiraj Anil and Ayushman kalita
  Install TimerThree library before uploading
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

#define pumpPin 9           // Connect the transistor's base to pin 9
#define igniterPin 10       // Connect to igniter transistor's base pin
#define trigPin 11          // Fuel Level Sensor Trigger Pin
#define echoPin 13          // Fuel Level Sensor Echo Pin
#define solenoidPin 22      // This pin powers the solenoid

double duration, fuelLevel; // Fuel Level Values
bool pumpState = true;      // true will speed up the pumps, false will do the opposite
bool paraDeploy = false;

volatile unsigned long speedVal = 0;     // Variable to hold pump speed value
volatile unsigned long incrementVal = 1; // Variable to hold pump speed increment value
volatile unsigned long decrementVal = 1; // Variable to hold pump speed decrement value

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(igniterPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  Timer3.initialize(300000);
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
  else if (paraDeploy == true)
  {
    speedVal = 0;
  }
  else
  {
    speedVal - decrementVal;
  }
}

void getFuelLevel()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  fuelLevel = (duration / 2) * 0.0340;
}

void parachute()
{
  paraDeploy = true;
  pumpState = false;
  analogWrite(pumpPin, 0);
  digitalWrite(igniterPin, LOW);
  digitalWrite(solenoidPin, HIGH);
}

void loop()
{
  getFuelLevel();
  if (fuelLevel > 25.0)
  {
    parachute();
  }
  else if (fuelLevel > 15.0)
  {
    pumpState = false;
    decrementVal = 1;
    digitalWrite(igniterPin, HIGH);
    analogWrite(pumpPin, speedVal);
  }
  else
  {
    // Start Igniter
    digitalWrite(igniterPin, HIGH);
    // Write PWM to transistor
    analogWrite(pumpPin, speedVal);
  }
}
