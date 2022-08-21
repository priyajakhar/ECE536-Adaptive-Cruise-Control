#include <hcrs04.h>
#include "timer.h"

#define PINTRIG 6
#define PINECHO 5

hcrs04 mySensor(PINTRIG, PINECHO);

float DISTANCE;

Timer myTimer;

 void timerFunction()
 {
  DISTANCE = mySensor.read();
  
  }
void setup()
{
  Serial.begin(9600);
  mySensor.begin();

  myTimer.begin(timerFunction, 10, 1000);
   myTimer.start();
  
}

void loop()
{
  Serial.print("Distance : ");
  Serial.print(DISTANCE);
  Serial.println(" cm");
 //delay(500);
 
}
