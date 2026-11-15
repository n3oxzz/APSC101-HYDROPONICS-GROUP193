/*
 * APSC 101 Example Sketch
 * 
 * B. Frank, adapted from R. Smyk for APSC 101, 2024.07.16
 * 
 * Simple example code for testing both Turbidity Sensors. 
 * Original code from DFRobot: https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189
 * 
 * !!! Must have the turbidity sensors connected on pin A0 and A1 as demonstrated in Arduino Instructions. !!!
 * !!! If you have turbidity sensors connected at different pins, you must replace those in code !!!
 * 
 */
unsigned long currentMillis=0; // Stores the the current time
unsigned long previousMillis = 0; // Stores the last time the serial monitor was updated
const unsigned long interval = 1000;
int seconds = 0; // Counter for seconds

void setup() {
  Serial.begin(9600);  // Opens serial port and sets rate to 9600 bits per sec. This has to match number on serial monitor!!
 const unsigned long interval = 1000;
  unsigned long previousMillis = 0; // Stores the last time the serial monitor was updated
  int seconds = 0; // Counter for seconds
  Serial.print("Time\tSensor 1\tSensor2\n");
  Serial.print("====\t========\t=======\n");  
}
void loop() {
   // Get the current time in milliseconds
  currentMillis = millis();
  
  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time you updated the serial monitor
    previousMillis = currentMillis;
    
    // Increment the seconds counter
    seconds++;
  
  int sensor1 = analogRead(A0);// read the input on analog pin 0
  float voltage1 = sensor1 * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  int sensor2 = analogRead(A1);
  float voltage2 = sensor2 * (5.0 / 1024.0); 
  Serial.print(seconds);
  Serial.print("\t");
  Serial.print(voltage1); 
  Serial.print("\t\t");
  Serial.println(voltage2); // println means next loop will print on new line
  }
}
