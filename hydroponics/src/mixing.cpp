#include "mixing.h"

#include "hardware.h"

#include <AFMotor.h>


static int currentSpeed = 0;
static int startTime = 0;
static int stopTime = 0;

static AF_DCMotor mixingMotor(MIXING_MOTOR_PORT); 

// Runs the mixer at a given speed for a set time.
bool runMixer(int speed, int time)
{
  startTime = millis();
  stopTime = millis() + time;

  currentSpeed = 0;
  
  return true;
}

// Initializes the mixing subsystem (start).
void initMixing()
{
  return;
}

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
  
  return;
}

// Stops the mixing subsystem (emergency stop).
void stopMixing()
{
  currentSpeed = 0;
  mixingMotor.setspeed(currentSpeed);
  mixingMotor.run(RELEASE);
  return;
}

// Checks if the mixing subsystem is active.
bool isMixingActive()
{
  return currentSpeed > 0;
}
