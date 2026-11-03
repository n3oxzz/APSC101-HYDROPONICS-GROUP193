#ifndef PH_H
#define PH_H

#include <Arduino.h>

// Calculates the volume of ph solution in [ml] needed to meet target.
double calculateRequiredPH (double currentPH); 

// Dispenses a certain amount of ph solution into the water tank.
bool dispensePH (double amount /*[ml]*/);

#endif
