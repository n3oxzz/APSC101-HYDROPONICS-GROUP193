#ifndef HARDWARE_H
#define HARDWARE_H 

#include <Arduino.h>

// Defines hardware constants for the interface subsystem
#define INTERFACE_SCREEN_PORT 0x3C
#define INTERFACE_STOP_PORT A4
#define INTERFACE_START_PORT A5

// Defines hardware constants for the sensing subsystem
#define SENSING_TDS_PORT A2
#define SENSING_PH_PORT A3
#define SENSING_LEVEL_PORT 30

// Defines hardware constants for the ph subsystem
#define PH_PUMP_PORT 3

// Defines hardware constants for the nutrient subsystem
#define NUTRIENT_SERVO_PORT 9

// Defines hardware constants for the mixing subsystem
#define MIXING_MOTOR_PORT 4

// Defines hardware constants for the transfer subsystem
#define TRANSFER_PLANT_PUMP_PORT 1
#define TRANSFER_WASTE_PUMP_PORT 2

#endif
