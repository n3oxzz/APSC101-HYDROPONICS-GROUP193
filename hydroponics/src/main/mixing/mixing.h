#ifndef MIXING_H
#define MIXING_H

#include <Arduino.h>

// Runs the mixer at a certain speed for a certain aount of time.
bool runMixer (double speed /*[rpm]*/, int time /*[ms]*/);

#endif
