/* 
 * Queen's University - Smith Engeering APSC 101 Sketch
 * 
 * Author: M.Malik for APSC 101
 * 02-Sep-2025 
 * 
 * To understand how to use the library methods, Read documentation on the AFMotor library at: https://learn.adafruit.com/afmotor-library-reference/af-dcmotor
 * 
 * Code for running tests to determine Torque-Speed Curve
 */

 /* ==========SUMMARY OF THE CODE===========
  *  This code helps you run the motor until the string is pulled up and measures the time it tools to roll the 1meter string (in milliseconds)
  *  The motor will run for as long as the button is pressed (Press and Hold). 
  *  
  *  millis() function is used to measure time at the moment when button is pressed and The final time is measured when released. Total time is (Final - Initial)
  *  More about millis() here: https://docs.arduino.cc/language-reference/en/functions/time/millis/#:~:text=06/05/2025-,Description,-Returns%20the%20number
  * 
  *  while() loop keeps teh motor running for as long as the button is pressed, without letting the program flow break
  *  
  *  Since the button is mapped as INPUT_PULLUP, it will be connected to 5V ("HIGH") under normal state, and when pressed, it is connected to Ground ("LOW")
  *  This is called Active-Low logic level (Button is Active when LOW) https://learn.sparkfun.com/tutorials/logic-levels/active-low-and-active-high
  */
  


#include <AFMotor.h>

float start;
float finish;

AF_DCMotor motor(1);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps -- **Ensure Serial Monitor also has baud rate set to 9600**
  pinMode(A0, INPUT_PULLUP);    // Define pin A0 for the button: note the use of INPUT_PULLUP. More information here: https://docs.arduino.cc/tutorials/generic/digital-input-pullup/
  
  motor.setSpeed(190);          // Set the motor speed here. The motor speed is a 8 bit number 0-255. Where 0 = 0% speed and 255 = 100% speed.
                                // If you want a specific speed, for eg. 75% speed, then: (0.75 * 255) = 190. 
  motor.run(RELEASE);           // Release (stop) the motor when the program starts to prevent accidentally running it
}

void loop() {

  if(digitalRead(A5) == LOW)            // Check if the button is pressed Pin used is A5. You can use any Pin. 
  {
    start = millis();                   // Measure time at the moment button is pressed
    Serial.println("==========");
    Serial.println("Start");
    
    while(digitalRead(A5) == LOW)       // Keep the motor running for as long as the button is pressed
    {
     motor.run(FORWARD);
    }
    
    Serial.println("End");
    finish=millis();                    // Measure time at the moment button is released
    Serial.print("Total Run Time:");
    Serial.println(finish - start);     //Total Runtime in milliseconds
    Serial.println("==========");
    }

 motor.run(RELEASE);                    //Important to stop the motor, r it will keep running even after button is released
}
