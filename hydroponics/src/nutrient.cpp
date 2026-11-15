#include "nutrient.h"

#include "hardware.h"

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

// Make the variables and function inside the braces priavte to the file 
namespace { 

// constexpr means these settings are fixed while the sketch runs.
// Connect the servo signal wire to .
constexpr uint8_t servoPin = ;  
// Pocket lines up under the funnel.
constexpr int fillAngle = 0;   
 // Pocket lines up with the bottom discharge hole.
constexpr int dumpAngle = 180; 

// These timers start when we send the position command, so they include travel.
// 1000 milliseconds (ms) = 1 second.
// Give the rotor time to reach fill when the system starts.
constexpr unsigned long startupMs = 1000;
// Time to move to fill and collect powder.
constexpr unsigned long fillMs = 3000;  
// Time to turn and let the powder fall.
constexpr unsigned long dumpMs = 2000;  
// Time to turn back before reporting idle.
constexpr unsigned long returnMs = 1000; 


// Readings from 900 to 1150 ppm, including both endpoints, are in range.
constexpr double minTdsPpm = 900.0;
constexpr double maxTdsPpm = 1150.0;

// A zero dose mass blocks dispensing.
// Actual water volume in litres.
constexpr double tankVolumeL = 0.0;
// From measured TDS rise * litres / grams.
constexpr double tdsSlopePpmLPerGram = 0.0;
// Weigh the powder delivered by one cycle.
constexpr double gramsPerPocket = 0.0;

// Each name represents one step. Idle means ready and Stopped means locked out.
enum class Phase { Stopped, MovingToFill, Idle, Filling, Dumping, Returning };
// This object sends position commands to the physical servo.
Servo servo;
Phase phase = Phase::Stopped;
// Time on the Arduino clock when a step began.
unsigned long phaseStarted = 0;

void enterPhase(Phase next)
{
  // Remember which step we are now doing.
  phase = next;
  // Record the current clock reading for that step.
  phaseStarted = millis();
}
}

// Calculates the mass of nutrients in [g] needed to meet target.
double calculateRequiredNutrients(double currentTDS)
{
  // A return value of zero tells main to request no dose.
  // First check whether the sensor reading and calibration are usable.
  if (!isfinite(currentTDS) || currentTDS < 0.0 ||
      tankVolumeL <= 0.0 ||
      tdsSlopePpmLPerGram <= 0.0) {
    return 0.0;
  }

  // Above the target band, adding nutrients would raise TDS further.
  if (currentTDS > maxTdsPpm) {
    return 0.0;
  }

  // A reading within the target band needs no additional nutrients.
  if (currentTDS >= minTdsPpm) {
    return 0.0;
  }

  // Below the band, calculate the grams needed to reach its lower edge.
  // TDS gap (ppm) * water volume (L) / calibration slope (ppm L per g).
  return (minTdsPpm - currentTDS) * tankVolumeL / tdsSlopePpmLPerGram;
}

// Dispenses a certain amount of nutrients into the water tank.
bool dispenseNutrients(double amount)
{
    // Only start from Idle. A bool result is either true or false.
  // The rotor delivers one whole pocket per accepted request. If the
  // requested grams are smaller than a pocket, skip the dose.
  if (phase != Phase::Idle || !isfinite(amount) ||
      gramsPerPocket <= 0.0 || amount < gramsPerPocket) {
    return false;
  }

  // Hold at the fill position while the pocket collects powder.
  servo.write(fillAngle);
  enterPhase(Phase::Filling);
  // This means the cycle started. It takes time to finish.
  return true;
}

// Initializes the nutrient dispensing subsystem (start).
// main
void initNutrient()
{
  // Main calls this at startup or after intentionally resetting a stop.
  // Clear any previous cycle and set the first servo position.
  stopNutrient();
  servo.write(fillAngle);
  servo.attach(servoPin);

  // Start the timer once the servo can receive position commands.
  if (servo.attached()) {
    enterPhase(Phase::MovingToFill);
  }
}

// Updates the nutrient dispensing subsystem (loop).
void updateNutrient()
{
    // Call this every time main's loop() runs. millis() keeps counting
  // while main reads sensors, checks Stop, or updates the display.
  // Subtract the start time from the current time to see how long this
  // step has been running. Each call checks once and returns immediately.
  const unsigned long elapsed = millis() - phaseStarted;

  switch (phase) {
    case Phase::MovingToFill:
      // Accept dose requests once the rotor has had time to reach fill.
      if (elapsed >= startupMs) {
        enterPhase(Phase::Idle);
      }
      break;

      case Phase::Filling:
      // Leave the pocket under the funnel until its fill time has passed.
      if (elapsed >= fillMs) {
        servo.write(dumpAngle);
        enterPhase(Phase::Dumping);
      }
        break; 
    
       case Phase::Dumping:
      // Give the rotor time to turn and the powder time to drop.
      if (elapsed >= dumpMs) {
        servo.write(fillAngle);
        enterPhase(Phase::Returning);
      }
        break;

      case Phase::Returning:
      // When the return timer finishes, main can start mixing and rechecking TDS.
      if (elapsed >= returnMs) {
        enterPhase(Phase::Idle);
      }
        break;     
    case Phase::Idle:
    case Phase::Stopped:
       // There is no cycle to advance in either of these states.
      break;
  }
}

// Stops the nutrient dispensing subsystem (emergency stop).
void stopNutrient()
{
  if (servo.attached()) {
    servo.detach();
  }
  // New requests stay blocked until initNutrient().
  enterPhase(Phase::Stopped);
}

// Checks if the nutrient dispensing subsystem is active.
bool isNutrientActive()
{
  // Tell main the dispenser is busy during startup or any dosing step.
  if (phase == Phase::MovingToFill || phase == Phase::Filling ||phase == Phase::Dumping || phase == Phase::Returning) {
    return true;
  }

  // Idle and Stopped have no movement timer running.
  return false;
}
