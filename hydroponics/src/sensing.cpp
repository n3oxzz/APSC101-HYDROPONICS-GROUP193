#include "sensing.h"
#include "hardware.h"

#include <GravityTDS.h>
static GravityTDS tds;

// Returns the tds of the main water tank.
double getCurrentTDS()
{
  return tds.getTdsValue();
}

// Returns the ph of the main water tank.
double getCurrentPH()
{
  return 0.0;
}

// Checks if the main tank water level is low.
bool isMainWaterLow()
{
  return (tds.getTdsValue() <= 0);
}

// Checks if the plant tank water level is low.
bool isPlantWaterLow()
{
  return (digitalRead(SENSING_LEVEL_PORT) == HIGH);
}

// Initializes the sensing subsystem (start).
void initSensing()
{
  tds.setPin(SENSING_TDS_PORT);
  
  tds.setAref(5.0);
  tds.setAdcRange(1024);
  
  tds.begin();

  pinMode(SENSING_LEVEL_PORT, INPUT);

  return;
}

// Updates the sensing subsystem (loop).
void updateSensing()
{
  tds.update();

  return;
}
