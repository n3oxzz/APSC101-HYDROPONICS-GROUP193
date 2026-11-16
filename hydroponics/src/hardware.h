#ifndef HARDWARE_H
#define HARDWARE_H 

#include <Arduino.h>

// Defines hardware constants for the interface subsystem
#define SCREEN_PIN 0x3C
#define STOP_BUTTON_PIN A4
#define START_BUTTON_PIN A5

// Defines hardware constants for the sensing subsystem
#define TDS_SENSOR_PIN A2
#define PH_SENSOR_PIN A3
#define LIQUID_SENSOR_PIN 30

// Defines hardware constants for the ph subsystem
#define PH_PUMP_PIN 3

// Defines hardware constants for the nutrient subsystem
#define NUTRIENT_SERVO_PIN 9

// Defines hardware constants for the mixing subsystem
#define MIXING_MOTOR_PIN 4

// Defines hardware constants for the transfer subsystem
#define MAIN_PUMP_PIN 2
#define PLANT_PUMP_PIN 1

#endif
