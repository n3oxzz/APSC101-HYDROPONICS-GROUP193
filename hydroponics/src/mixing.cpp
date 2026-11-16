#include "mixing.h"
#include "hardware.h"

#include <Arduino.h>
#include <AFMotor.h>

static int currentSpeed = 0;
static int startTime = 0;
static int stopTime = 0;

static AF_DCMotor mixingMotor(MIXING_MOTOR_PIN); 

// Runs the mixer at a given speed for a set time.
bool runMixer(int speed, int time)
{
  startTime = millis();
  stopTime = millis() + time;

  currentSpeed = speed;
  
  return true;
}

// Initializes the mixing subsystem (start).
void initMixing() { }

// Updates the mixing subsystem (loop).
void updateMixing()
{
  // ramp up speed over 300 milliseconds to not lose magnet coupling

  if(millis() < startTime + 150){
    mixingMotor.setspeed(currentSpeed/4);
    mixingMotor.run(FORWARD); 

  } else if(millis() >= startTime + 150 && millis() < startTime + 200) {
    mixingMotor.setspeed(currentSpeed/2);
    mixingMotor.run(FORWARD);  

  } else if (millis() >= startTime + 200 && millis() < startTime + 300 ) {
    mixingMotor.setspeed(3 * currentSpeed/4);
    mixingMotor.run(FORWARD);

  } else if (millis() >= startTime + 300) {
    mixingMotor.setspeed(currentSpeed);
    mixingMotor.run(FORWARD);  
  } 

  if (millis() >= stopTime) {
    currentSpeed = 0;
    mixingMotor.setspeed(currentSpeed);
    mixingMotor.run(RELEASE);
  }
}

void startIdleSpeed(int speed) {
  currentSpeed = speed;
  stopTime = millis() + 10 * 1000 * 60 // idle run for 10 min or until a new time is set
}

// Stops the mixing subsystem (emergency stop).
void stopMixing()
{
  currentSpeed = 0;
  stopTime = millis();
  mixingMotor.setspeed(currentSpeed);
  mixingMotor.run(RELEASE);
}

// Checks if the mixing subsystem is active.
bool isMixingActive()
{
  return currentSpeed > 0;
}
