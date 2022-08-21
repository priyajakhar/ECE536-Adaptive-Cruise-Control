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

#include "SimpleRSLK.h"

#include "Timer.h"

#include "rtosGlobals.h"

#include "Clock.h"

/* Diameter of Romi wheels in meter */
float wheelDiameter = 0.069999;

/* Number of encoder (rising) pulses every time the wheel turns completely */
int cntPerRevolution = 360;

/* How far in inches for the robot to travel */
int inchesToTravel = 6;

int wheelSpeed = 15; // Default raw pwm speed for motor.

float meter_per_cnt = 0.00061046 ; //meter per revolution

int firstencodervalue =0;

int previousencodervalue=0;

int  totalCount =0;

float temp=0;

/* The distance the wheel turns per revolution is equal to the diameter * PI.
 * The distance the wheel turns per encoder pulse is equal to the above divided
 * by the number of pulses per revolution.
 */
float distanceTraveled(float wheel_diam, uint16_t cnt_per_rev, uint8_t current_cnt) {
  
//  return temp;
}


uint32_t countForDistance(float wheel_diam, uint16_t cnt_per_rev, uint32_t distance) {
  float temp = (wheel_diam * PI) / cnt_per_rev;
  temp = distance / temp;
  return int(temp);
}


  

Clock myClockR;

void clockFunctionR()
{
  totalCount = getEncoderLeftCnt();
  Serial.println(totalCount);
  temp = (2.7559 * PI * totalCount) / 360;
  resetLeftEncoderCnt();
  
}

void setup() {
  Serial.begin(115200);

   myClockR.begin(clockFunctionR, 1000, 100); // 1000 ms = 1 s
   myClockR.start();
   
  setupRSLK();
}

void loop() {

   Serial.println("Speed:");
   Serial.print(temp);
 
  //uint16_t totalCount = 0; // Total amount of encoder pulses received
 int x=1000;
 
 if (wheelSpeed < 100)
 {
  /* Cause the robot to drive forward */
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS,wheelSpeed);

   wheelSpeed = wheelSpeed+2;
  
 }
  /* Halt motors */
 // disableMotor(BOTH_MOTORS);
}
