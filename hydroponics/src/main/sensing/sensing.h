#ifndef SENSING_H
#define SENSING_H

#include <Arduino.h>

// Measures the tds within the main tank.
bool measureTDS ();

// Measures the pd within the main tank.
bool measurePH ();

// Returns the last tds measurement of the main tank.
double getCurrentTDS ();

// Returns the last ph measurement of the main tank.
double getCurrentPH ();

// Checks if the main tank water level is low.
bool isMainWaterLow ();

// Checks if the plant tank water level is low.
bool isPlantWaterLow ();

#endif
