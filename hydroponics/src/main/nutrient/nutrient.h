#ifndef NUTRIENT_H
#define NUTRIENT_H

#include <Arduino.h>

// Calculates the mass of nutrients in [g] needed to meet target.
double calculateRequiredNutrients(double currentTDS /*[ppm]*/); 

// Dispenses a certain amount of nutrients into the water tank.
bool dispenseNutrients(double amount /*[g]*/);

// Initializes the nutrient dispensing subsystem (start).
void initNutrient();

// Updates the nutrient dispensing subsystem (loop).
void updateNutrient();

// Stops the nutrient dispensing subsystem (emergency stop).
void stopNutrient();

// Checks if the nutrient dispensing subsystem is active.
bool isNutrientActive();

#endif
