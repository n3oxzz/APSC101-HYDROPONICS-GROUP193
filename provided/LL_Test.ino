/*
 * APSC 101 Example Sketch
 * 
 * M.Malik for APSC 101: 10-Sep-2026
 * 
 * Simple example code for testing Liquid Level Sensor.
 * Adapted from sample code provided by manufacturer at: https://wiki.dfrobot.com/sen0368/docs/19134
 * 
*/

int LLpin = 30;
bool pumpingDone = false;

void setup()
{
  Serial.begin(9600);
  pinMode(LLpin, INPUT);
}

void loop()
{
  /* Notice the use of '!' operator. This is the NOT operator.
  * Using '!' before a condition calculates inverse. 
  * So if pumpingDone = false, then !pumpingDone = true. This is equivalent of saying if (NOT pumpingDone)...  */
  if (!pumpingDone)
  {
    // Liquid Level sensor is Active LOW. Meaning when there is no water, it is HIGH.
    // If water is detected, it turns LOW.
    while(digitalRead(LLpin)==HIGH)   // while(No water detected)
  {
    Serial.println("Pumping...");
    // Run the pump
    // ... You can do more things while pumping, 
    // i.e. checking other sensors, reading pH/Turbidity/TDS value, display on OLED etc.
  }
  Serial.println("Water Level Reached! Pump Stopped.");
 }

/* Change the variable so you dont keep pumping and move on to next stage
* If you dont use a state variable to control the decision making, your pump will run again 
* after mixing is done and water is taken out, because the liquid level sensor will turn HIGH again */ 
 pumpingDone = true;  
 delay(10);
}
