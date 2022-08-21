# Adaptive Cruise Control

Adaptive Cruise Control (ACC) is a real-time system that controls the set cruising speed of a vehicle and maintains a safe distance from vehicles ahead. The main purpose of the system is to reduce driver fatigue during long journeys.

* In our project, we used the TI Robotics Systems Learning Kit (TI-RSLK) to act as a vehicle.
We performed system identification, modeled the system and designed a PID controller for it. The PID controller works around the encoder readings of the wheel motors to try to maintain constant speed. The distance from the lead vehicle detected using ultrasonic sensor HC-SR04 decides the mode the vehicle operates under.
