#ifndef NUTRIENT_H
#define NUTRIENT_H

#include <Arduino.h>
#include <gravityTDS.h>

// Calculates the mass of Nutrients in [g] needed to meet target.
double calculateRequiredNutrients (double currentTDS /*[ppm]*/); 

// Dispenses a certain amount of nutrients into the water tank.
bool dispenseNutrients (double amount /*[g]*/);

#endif
