#include "sensing.h"
#include "hardware.h"
#include "settings.h"

#include <GravityTDS.h>
static GravityTDS tds;

// Initializes the sensing subsystem (start).
void initSensing () {
  tds.setPin(TDS_SENSOR_PIN);
  
  tds.setAref(5.0);
  tds.setAdcRange(1024);
  
  tds.begin();

  pinMode(LIQUID_SENSOR_PIN, INPUT);
}

// Updates the sensing subsystem (loop).
void updateSensing () {
  tds.update();
}

// Returns the tds of the main water tank.
double getCurrentTDS () {
  return tds.getTdsValue();
}

// Returns the ph of the main water tank.
double getCurrentPH () {
  double value = analogRead(PH_SENSOR_PIN);
  double voltage = value * 5.0 / 1024.0;
  
  return 3.5 * voltage + PH_OFFSET;
}

// Checks if the main tank water level is low.
bool isMainWaterLow () {
  return tds.getTdsValue() <= 0;
}

// Checks if the plant tank water level is low.
bool isPlantWaterLow () {
  return digitalRead(LIQUID_SENSOR_PIN) == HIGH;
}
