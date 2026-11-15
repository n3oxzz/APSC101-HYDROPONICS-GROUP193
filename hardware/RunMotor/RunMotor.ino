/* 
 * APSC 101 Example Sketch
 * 
 * M.Malik for APSC 101: 22-Sep-2023
 * 
 * Simple example code for testing a DC Motor. Original code from Adafruit.
 * 
 * To understand how to use the library methods, Read documentation on the AFMotor library at: https://learn.adafruit.com/afmotor-library-reference/af-dcmotor
 * 
 */


#include <AFMotor.h>

/* 
* You need to initialize an object of the AF_DCMotor class
* You need to use the port number that your motor/pump is connected to.
* Syntax: AF_DCMotor objname(motorport) 
* Example: AF_DCMotor motor(1) for Motor/Pump connected to M1
* Example: AF_DCMotor xpump(3) for Motor/Pump connected to M3
*/
AF_DCMotor motor(1); 

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps -- **Ensure Serial Monitor also has baud rate set to 9600**
  Serial.print("Starting motor.");
  motor.setSpeed(255);          // setSpeed() decides the speed at which the motor can run. This value can be between 0-255
  motor.run(FORWARD);           // run() decides the direction. This method also makes the motor move. So you need to call this fuction to get the motor started.
                                // run() can take values: FORWARD, BACKWARD or RELEASE(to stop the motor)

  /* A note on setSpeed(): 
  * As mentioned, it uses a 8-bit value (0-255). 
  * This is mapped linearly with voltage applied to the motor. 
  * Meaning, 0 is 0% power, 127 is 50% power, 255 is 100% power and so on.
  * You can slow down the motor/pump, but if you use a very small value,
  * the motor/pump will not have enough starting torque to run, especially if you have a gearbox connected.
  * Try out different values of setSpeed() to see how your motor reacts.
  */
}

void loop() {
  // In this example the code in setup() is enough to make the motor run. No need for loop()
}
