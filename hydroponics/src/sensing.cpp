#include "sensing.h"
#include "hardware.h"

#include <GravityTDS.h>
static GravityTDS tds;

// Returns the tds of the main water tank.
double getCurrentTDS () { return tds.getTdsValue(); }

// Returns the ph of the main water tank.
double getCurrentPH () {
  double reading = analogRead(PH_SENSOR_PIN);
  double voltage = reading * 5.0 / 1024.0;
  
  return 3.5 * voltage + PH_OFFSET;
}

// Checks if the main tank water level is low.
bool isMainWaterLow () { 
  return (getCurrentTDS() <= 0);
}

// Checks if the plant tank water level is low.
bool isPlantWaterLow () {
  return (digitalRead(LIQUID_SENSOR_PIN) == HIGH);
}

// Initializes the sensing subsystem (start).
void initSensing () {
  stopSensing();
  
  tds.setPin(TDS_SENSOR_PIN);
  
  tds.setAref(5.0);
  tds.setAdcRange(1024);
  
  tds.begin();
  
  pinMode(LIQUID_SENSOR_PIN, INPUT);
  pinMode(PH_SENSOR_PIN, INPUT);
}

// Updates the sensing subsystem (loop).
void updateSensing () { tds.update(); }

// Stops the sensing subsystem (emergency stop).
void stopSensing () { }
