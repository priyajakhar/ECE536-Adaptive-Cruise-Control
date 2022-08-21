# Adaptive Cruise Control

Adaptive Cruise Control (ACC) is a real-time system that controls the set cruising speed of a vehicle and maintains a safe distance from vehicles ahead. The main purpose of the system is to reduce driver fatigue during long journeys.

* We used the TI Robotics Systems Learning Kit (TI-RSLK) to act as a vehicle.
* TI-RSLK uses Microcontroller MSP432 which was programmed using Energia IDE.
* Main peripherals are DC motors with in-built encoders and HC-SR04 ultrasonic sensor.
* We performed system identification, modeled the system and designed a PID controller for it.
* The mode of operation of the bot is decided by the proximity with the lead vehicle. Elegoo robot car kit was used for lead vehicle.
  - Constant speed logic utilizes PID control loop depending on feedback from the encoders and ultrasonic sensor. 
  - Safe distance logic governed by open loop control derived from data gathered during experiments.
