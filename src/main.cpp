#include <Arduino.h>
/*
This sketch only works with the Arduino UNO because the timer numbers would
vary with the other boards
*/
// In this commit, the code is unfinished and needs to be finished

int outPin = 9; /* Output pin to transistor base, get your transistor's datasheet and
   find where the base is
*/

// Variable to hold speed value
int speedVal;

void setup()
{
    // Setup transistor pin as output
    pinMode(outPin, OUTPUT);
}

void loop()
{
    // Write PWM to transistor
    analogWrite(outPin, speedVal);

    delay(20);
}
