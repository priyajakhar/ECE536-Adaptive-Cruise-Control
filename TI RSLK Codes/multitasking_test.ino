#include "Energia.h"

#include "rtosGlobals.h"

#include "Clock.h"

#include "SimpleRSLK.h"

#include "OneMsTaskTimer.h"

#include <hcrs04.h>

#define PINTRIG 6
#define PINECHO 5

hcrs04 mySensor(PINTRIG, PINECHO);




// variables intialization

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

// Functions 

void clock_ultrasonic()   //Calculates distance from the object in front
{
  distance = mySensor.read();
  //Serial.println(distance);
  if(distance < 100  && distance > 80)
  {
   set_speed = temp - 0.10;  
  // Serial.println(set_speed);
   }
   else if(distance < 80  && distance > 50) 
   {
    set_speed = temp - 0.20;
 //   Serial.println(set_speed);
    }
   else if(distance < 50  && distance > 20) 
   {
    set_speed = temp - 0.30;
 //   Serial.println(set_speed);
   } 
   else if(distance < 20)
   {
    set_speed =0;
  //  wheel_pwm=0;
 //   Serial.println(set_speed);
   }
   else if (distance > 100)
   {
    set_speed = temp;
 //   Serial.println(set_speed);
    }   
}

void clock_encoder_reading()
{
  encoder_count = getEncoderLeftCnt();
  Serial.print("encoder: ");
  Serial.print(encoder_count); 
  Serial.print("  ");
  resetLeftEncoderCnt();
}


void clock_speed_calculation()
{
  speed = encoder_count* meter_per_degree ;
  if(speed < set_speed && distance > 100)
  {
    
    wheel_pwm= wheel_pwm+2;
   //    Serial.println(wheel_pwm);
  }

  else if (speed > set_speed && wheel_pwm < 100)
  {
    wheel_pwm--;
  //  Serial.println(wheel_pwm);
   }
  
}


void voltage_calculation()
{
//  voltage = analogRead(sensorPin);
//  Serial.println(voltage);
  
 }

//define variables and constants

Clock ultrasound;
Clock encoder_value;
Clock speed_calculation;


//initialization
void setup()
{
  Serial.begin(115200);  //starting the USRT for debugging 

  mySensor.begin();      // starting the sensor
  // put your setup code here, to run once:
  setupRSLK();

  setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);  // setting the motor direction


  ultrasound.begin(clock_ultrasonic,10,10);                    //numbers in ms
  encoder_value.begin(clock_encoder_reading,10,1000);          //encoder reading every 1000ms = 1S
  speed_calculation.begin(clock_speed_calculation,10,1000);    //speed calculation every 1000ms= 1S;
  
  ultrasound.start();                  
  encoder_value.start();  
  speed_calculation.start();
  

}


void loop() {
  // put your main code here, to run repeatedly: 

    
    voltage_calculation();
   
  /* "Turn on" the motor */
    enableMotor(BOTH_MOTORS);
    //count = millis();
   
    setMotorSpeed(BOTH_MOTORS,wheel_pwm);


    
  
}
