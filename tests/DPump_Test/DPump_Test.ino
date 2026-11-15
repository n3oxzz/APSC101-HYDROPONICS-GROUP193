/* 
 * APSC 101 Example Sketch
 * 
 * S.Skripchenko for APSC 101, 29-Sep-2025
 * Edited by M.Malik 12-Sep-2026
 * 
 * Example Sketch to run the Diaphragm Water dPump
 * Works in the same way as motor from DCMotor Test run. It uses the Adafruit AFMotor library
 *  
 */
#include <AFMotor.h>

AF_DCMotor dpump(3);   // Connect to M3 port. You can use Any of M1-M4 port, but ensure correct port is used here.

void setup() 
{
  // No setup code needed since we are only testing the dpump
}

void loop() {
  dpump.setSpeed(255); // Set the speed to maximum for test. For your prorotype, you can slow it down of needed
  dpump.run(FORWARD);
  delay(5000);

  dpump.run(RELEASE);  // run(RELEASE) is important to stop the dpump. Or else it will keep running in infinite loop.
  delay(2000);

  /* Now example to slow down the speed
  * Do not slow down too much, or the motor on the dpump will not have enoguh starting torque to run properly.
  */
  dpump.setSpeed(170); 
  dpump.run(FORWARD);
  delay(5000);

  dpump.run(RELEASE);  // run(RELEASE) is important to stop the dpump. Or else it will keep running in infinite loop.
  delay(2000);
}
