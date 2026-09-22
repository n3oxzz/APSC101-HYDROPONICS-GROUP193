/* 
 * APSC 101 Example Sketch
 * 
 * R.Smyk for APSC 101, 08-Aug-2024
 * Apapted from M.Malik for APSC 101, 10-Sep-2023
 * Edited M.Malik 12-Sep-2026
 * 
 * Example Sketch to run the Peristaltic Pump
 *  
 */


#include <AFMotor.h>

AF_DCMotor ppump(4); // Connected to M4

void setup() {
  Serial.begin(9600);
}


void loop() {
  /*
  * Peristaltic pumps are reversible. 
  * So they can be used to send liquid FORWARD, and after the cycle is complete, 
  * the liquid can be drawn back into the same cotainer using BACKWARD
  */
  ppump.setSpeed(255);  // Set the speed of pump. Uses an 8 bit value, 255 = 100% speed.
  ppump.run(FORWARD);  // Change between FORWARD or BACKWARD (all upper case,  Case sensitive) depending on what direction the liquid flows in the pump.
  Serial.println("Pumping Forward!");
  delay(5000);

  ppump.setSpeed(200);  // Set the speed of pump. Uses an 8 bit value, 255 = 100% speed.
  ppump.run(BACKWARD);  // Change between FORWARD or BACKWARD (all upper case,  Case sensitive) depending on what direction the liquid flows in the pump.
  Serial.println("Pumping BACKWARD!");
  delay(5000);

  ppump.run(RELEASE); //Stop the pump
  delay(1000);

}
