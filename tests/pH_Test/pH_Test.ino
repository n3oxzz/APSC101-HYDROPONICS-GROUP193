/*
 * APSC 101 Example Sketch
 * 
 * M.Malik for APSC 101: 10-Sep-2026
 * 
 * Simple example code for testing pH Sensor.
 * Adapted from sample code provided by manufacturer at: https://wiki.dfrobot.com/sen0161/docs/19898
 *
 * Please note the manufacturer's code has a lengthy algortihm to sample input from the Sensor Pin at a certain interval
 * Then arrange it, then drops some values, and calculates the average
 * Then the avg is converted into pH reading and voltage
 * This is not necessary for the test, so this code directly uses the calculation formula (instead of sampling & averaging)
 * You are free to review the code on the manufacturer's website and implement it
 * 
*/

#define phPin A3 //Must be Analog Pin. Remember to change this Pin if you plug in your sensor to another Analog Pin.

float voltage = 0;
float phValue = 0;

// We will provide you with Buffer solution later on to calibrate your pH Sensor and calculate this value
float calibrationOffset = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Both of these formulae are similar to TDS Sensor calculation
  voltage = analogRead(phPin) * 5.0 / 1024.0;
  // As for phValue, the formula is taken directly from the manufacturer's example code
  phValue = 3.5 * voltage + calibrationOffset;

  /* Output both Voltage and pH to Serial monitor
  * Serial.print(value, 2) 
  * The '2' in this line determines the digits after decimal (Since it is a float value, it will print upto 6 digits, but we only need 2) */
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);         
  Serial.print("V | pH Value: ");
  Serial.println(phValue, 2);

  delay(1000); 
}
