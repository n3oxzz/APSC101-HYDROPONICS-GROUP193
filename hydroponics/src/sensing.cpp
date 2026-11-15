#include "sensing.h"
#include "../../../hardware.h"
#include "../../../../libraries/GravityTDS.h"

static GravityTDS tds;

// Returns the tds of the main water tank.
double getCurrentTDS()
{
  return 0.0;
}

// Returns the ph of the main water tank.
double getCurrentPH()
{
  return 0.0;
}

// Checks if the main tank water level is low.
bool isMainWaterLow()
{
  if (tds.getTdsValue() <= 0) {
    return true;
  }
  else {
    return false;
  }
}

// Checks if the plant tank water level is low.
bool isPlantWaterLow()
{
  if (digitalRead(SENSING_LEVEL_PORT) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

// Initializes the sensing subsystem (start).
void initSensing()
{
  pinMode(SENSING_LEVEL_PORT, INPUT);

  tds.setPin(SENSING_TDS_PORT);
  tds.setAref(5.0);
  tds.setAdcRange(1024);
  tds.begin();

  return;
}

// Updates the sensing subsystem (loop).
void updateSensing()
{
  tds.update();

  return;
}
