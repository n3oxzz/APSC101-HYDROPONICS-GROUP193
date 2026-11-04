#ifndef MIXING_H
#define MIXING_H

#include <Arduino.h>

// Runs the mixer at a given speed for a set time.
bool runMixer(double speed /*[rpm]*/, int time /*[ms]*/);

// Initializes the mixing subsystem (start).
void initMixing();

// Updates the mixing subsystem (loop).
void updateMixing();

// Stops the mixing subsystem (emergency stop).
void stopMixing();

// Checks if the mixing subsystem is active.
bool isMixingActive();

#endif
