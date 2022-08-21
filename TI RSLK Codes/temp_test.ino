#include "Energia.h"

#include "rtosGlobals.h"

#include "Clock.h"

#include "SimpleRSLK.h"

#include "OneMsTaskTimer.h"

#include <hcrs04.h>

int sensorPin = A0;          // pin 5.5 for ADC calculation 

int encoder_count=0;        // counts encoder value

float meter_per_degree = 0.000611;   //distance covered in meter per encoder value 

float speed=0;              // speed calculation variable in speed_calculation function 

float set_speed = 0.50 ;    // speed in m/s set by the user

float temp = set_speed ;    //temp variable 

//float speed = set_speed;  // variable for clock_ultrasonic function 

int wheel_pwm = 15 ;        // variable to control the pwm of the motor

float distance = 0;         // variable to save the value from ultrasonic sensor 

float voltage =0;           // motor voltage value 



void clock_encoder_reading()
{
   encoder_count = getEncoderLeftCnt();
   Serial.print("encoder: ");
   Serial.println(encoder_count); 
   Serial.print("  ");
   resetLeftEncoderCnt();
   
}


Clock encoder_value;

//initialization
void setup()
{
  Serial.begin(115200);  //starting the USRT for debugging 

 
  // put your setup code here, to run once:
  setupRSLK();

  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);  // setting the motor direction


 
  encoder_value.begin(clock_encoder_reading,1,1);          //encoder reading every 1000ms = 1S
  
             
  encoder_value.start();  
  
}

void loop() {
  // put your main code here, to run repeatedly: 

 //  double  count = millis();
  //  Serial.println(count);

   
  /* "Turn on" the motor */
    enableMotor(BOTH_MOTORS);
    //count = millis();
   
    setMotorSpeed(BOTH_MOTORS,wheel_pwm);


    
  
}
