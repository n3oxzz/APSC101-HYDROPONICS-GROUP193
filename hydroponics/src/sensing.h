#ifndef SENSING_H
#define SENSING_H

#include <Arduino.h>

// Returns the tds measurement of the main water tank.
double getCurrentTDS();

// Returns the ph measurement of the main water tank.
double getCurrentPH();

// Checks if the main tank water level is low.
bool isMainWaterLow();

// Checks if the plant tank water level is low.
bool isPlantWaterLow();

// Initializes the sensing subsystem (start).
void initSensing();

// Updates the sensing subsystem (loop).
void updateSensing();

#endif
