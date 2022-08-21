
/*
 * Energia Robot Library for Texas Instruments' Robot System Learning Kit (RSLK)
 * Simplified Encoder Example
 *
 * Summary:
 * This example has the TI Robotic System Learning Kit (TI RSLK) driving forward
 * by a predefined distance utilizing wheel encoders.
 *
 * How to run:
 * 1) Push left button on Launchpad to start the demo
 * 2) Robot will drive forward by a predefined distance
 * 3) Once distance has been reached the robot will stop
 * 4) Push left button again to start demo again
 *
 * Learn more about the classes, variables and functions used in this library by going to:
 * https://fcooper.github.io/Robot-Library/
 *
 * Learn more about the TI RSLK by going to http://www.ti.com/rslk
 *
 * created by Franklin Cooper Jr.
 *
 * This example code is in the public domain.
 */
// current_cnt = current count
// cnt_per_rev = Count per revolution 



#include "SimpleRSLK.h"


#include <hcrs04.h>


/* Diameter of Romi wheels in inches */
float wheelDiameter = 2.7559055;

/* Number of encoder (rising) pulses every time the wheel turns completely */
int cntPerRevolution = 360;

/* How far in inches for the robot to travel */
int inchesToTravel = 6;

int setspeed= 50; //speed of the robot set by user 

int wheelSpeed = 0; // Default raw pwm speed for motor.

float Distance_mean=0;




#define PINTRIG 6
#define PINECHO 5

hcrs04 mySensor(PINTRIG, PINECHO);

void ultrasonic();
/* The distance the wheel turns per revolution is equal to the diameter * PI.
 * The distance the wheel turns per encoder pulse is equal to the above divided
 * by the number of pulses per revolution.
 */
float distanceTraveled(float wheel_diam, uint16_t cnt_per_rev, uint8_t current_cnt) {
  float temp = (wheel_diam * PI * current_cnt) / cnt_per_rev;
  return temp;
}


uint32_t countForDistance(float wheel_diam, uint16_t cnt_per_rev, uint32_t distance) {
  float temp = (wheel_diam * PI) / cnt_per_rev;
  temp = distance / temp;
  return int(temp);
}



void setup() {
  Serial.begin(115200);

  setupRSLK();
  /* Left button on Launchpad */
  setupWaitBtn(LP_LEFT_BTN);
  /* Red led in rgb led */
  setupLed(RED_LED);
  mySensor.begin();
}



void loop()
{
  float DISTANCE=0;
  float Distance_total=0;
  Distance_mean=0;
  for(int i=0;i<10;i++)
  {
    DISTANCE = mySensor.read();
    Distance_total =(DISTANCE + Distance_total);
  }
  Distance_mean= Distance_total/10;

  
  if(Distance_mean > setspeed)
  {
    wheelSpeed= setspeed;

    resetLeftEncoderCnt();
    resetRightEncoderCnt();

    /* Cause the robot to drive forward */
    setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

    /* "Turn on" the motor */
    enableMotor(BOTH_MOTORS);

    /* Set motor speed */
    setMotorSpeed(BOTH_MOTORS,wheelSpeed);

    Serial.print("Distance_mean : ");
    Serial.print(Distance_mean);
    Serial.println(" cm");
    delay(500);
 }
 
  if (Distance_mean > 15 && Distance_mean < setspeed)
  {
    wheelSpeed = Distance_mean-10;

    resetLeftEncoderCnt();
    resetRightEncoderCnt();

    /* Cause the robot to drive forward */
    setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

    /* "Turn on" the motor */
    enableMotor(BOTH_MOTORS);

    /* Set motor speed */
    setMotorSpeed(BOTH_MOTORS,wheelSpeed); 

    Serial.print("Distance_mean : ");
    Serial.print(Distance_mean);
    Serial.println(" cm");
    delay(500);
        
  }
  else if ( Distance_mean < 15)
  {
    disableMotor(BOTH_MOTORS);

    Serial.print("Distance_mean : ");
    Serial.print(Distance_mean);
    Serial.println(" cm");
    delay(500);
  }
  
    
}
  
