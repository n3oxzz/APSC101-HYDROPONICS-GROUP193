/*
 * APSC 101 Example Sketch
 * 
 * M.Malik for APSC 101: 10-Sep-2026
 * 
 * Simple example code for testing TDS Sensor.
 * Adapted from sample code provided by manufacturer at: https://wiki.dfrobot.com/sen0244/docs/20305
 *
 * Please note the original code from manufacturer contains a routine to sample 30+ values, and calculate the median of it
 * This helps provide a more accurate value, howeverm makes the code increasingly difficult to integrate with other systems
 * You are encouraged to review it and implement it, however, it is not needed for this test.
 * The method implemented in this test code will also suffice for your prototype
 */

#include "GravityTDS.h" // Custom Library provided by manufacturer

#define tdsPin A2   // Define the pin the TDS sensor is connected to. Important: You MUST use an Analog Pin (A0-A9)
GravityTDS tds;     // Create object of GravityTDS class, same as you do for the motor/pumps

float tdsVal = 0;

void setup()
{
    Serial.begin(9600);
    tds.setPin(tdsPin);
    tds.setAref(5.0);       // The sensor needs to have the reference voltage for TDS calculation. For Arduino Mega, it is 5V

    // This defines the range of the Analog-to-Dgitial Converter (ADC) which reads the value using analogRead()
    // For Arduino Mega, its a 10-bit ADC, so 1024 values
    tds.setAdcRange(1024);  
    tds.begin();
}

void loop()
{
    tds.update();
    tdsVal = tds.getTdsValue(); 
    Serial.print(tdsVal,0);
    Serial.println(" ppm");
    delay(1000);
}














