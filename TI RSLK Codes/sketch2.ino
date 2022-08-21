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
#include "clock.h"

int sensorPin = A0;    // select the input pin for the voltage from motor 

int sensorValue = 0;  // variable to store the value coming from the sensor

/* Diameter of Romi wheels in inches */
float wheelDiameter = 2.7559055;

/* Number of encoder (rising) pulses every time the wheel turns completely */
int cntPerRevolution = 360;

/* How far in inches for the robot to travel */
int inchesToTravel = 6;

int encoder_count=0;

int wheelSpeed = 61; // Default raw pwm speed for motor.

float voltage;

int firstencodervalue =0;

int previousencodervalue=0;

int  totalcount_persecond =0;

/* The distance the wheel turns per revolution is equal to the diameter * PI.
 * The distance the wheel turns per encoder pulse is equal to the above divided
 * by the number of pulses per revolution.
 */
float distanceTraveled(float wheel_diam, uint16_t cnt_per_rev, uint8_t current_cnt) {
   float temp = (2.7559 * PI * current_cnt) / 360;
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
 // setupWaitBtn(LP_LEFT_BTN);
  /* Red led in rgb led */
    setupLed(RED_LED);
}

void loop() {
  uint16_t totalCount = 0; // Total amount of encoder pulses received
    
  /* Amount of encoder pulses needed to achieve distance */
  uint16_t x = countForDistance(wheelDiameter, cntPerRevolution, inchesToTravel);

 // if(wheelSpeed > 0)
 // {
    
  /* Set the encoder pulses count back to zero */
 // resetLeftEncoderCnt();
 // resetRightEncoderCnt();

  /* Cause the robot to drive forward */
  //wheelSpeed = wheelSpeed - 1;
  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS,wheelSpeed);
  
  Serial.print("Wheelspeed : ");
  Serial.print(wheelSpeed);
  Serial.println(" PWM");
  delay(1000);
  Serial.print("Encoder : ");
  Serial.print(getEncoderLeftCnt());
  Serial.println(" ");
 // resetLeftEncoderCnt();
  
  }
  //else if ( wheelSpeed < 1)
//  {
  /* Halt motors */
//  disableMotor(BOTH_MOTORS);
//  }
