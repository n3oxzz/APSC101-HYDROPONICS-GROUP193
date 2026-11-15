 /*
 * APSC 101 Example Sketch
 * 
 * C. Milberry for APSC 101, 2023.08.9
 * Edited by M.Malik 12-Sep-2026
 * 
 * Simple example code for servo motor with Arduino. 
 * More info: https://www.instructables.com/Arduino-How-to-Control-Servo-Motor-With-Motor-Shie/
 * 
 */

#include <Servo.h>
Servo Servo1;

int servo_pos = 0;

void setup() {
  Servo1.attach(9); // Pin 9 corresponds to SERVO_2 and Pin 10 corresponds to SER1 connector on the shield

}

void loop() {

  Servo1.write(0);  //Use Servo1.write(angle) to move the servo. Angle can be any integer between 0-180. 
  delay(1000);
  Servo1.write(90);
  delay(1000);
  Servo1.write(180);
  delay(1000);

  /*
  * In essence, you only need to use Servo1.write(angle) to make the servo move
  * However, that is really fast movement
  * To havea more controlled gradual movement, you can define a for loop, and move the servo in 1degree increments
  * the delay() inside the for() loop controls the speed of the servo movement
  */
  for (servo_pos = 0; servo_pos <= 180; servo_pos += 1){
    Servo1.write(servo_pos);
    delay(20);
  }

  for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1){
    Servo1.write(servo_pos);
    delay(20);
  }
}
