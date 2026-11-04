#ifndef TRANSFER_H
#define TRANSFER_H

#include <Arduino.h>

// Starts transfering solution from the excess to the main tank.
bool startMainTransfer();

// Stops transfering solution from the excess to the main tank.
bool stopMainTransfer();

// Starts transfering solution from the main tank to the plant.
bool startPlantTransfer();

// Stops transfering solution from the main tank to the plant.
bool stopPlantTransfer();

// Initializes the fluid transfer subsystem (start).
void initTransfer();

// Updates the fluid transfer subsystem (loop).
void updateTransfer();

// Stops the fluid transfer subsystem (emergency stop).
void stopTransfer();

// Checks if the main fluid transfer subsystem is active.
bool isMainTransferActive();

// Checks if the plant fluid transfer subsystem is active.
bool isPlantTransferActive();

#endif
