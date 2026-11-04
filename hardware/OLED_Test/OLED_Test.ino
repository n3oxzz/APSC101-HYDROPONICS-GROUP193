/*
 * APSC 101 Example Sketch
 * 
 * M.Malik for APSC 101: 12-Sep-2026
 * 
 * Simple example code for testing the OLED Display.
 * Adapted from Adafruit SSD1306 Example code
 * 
 * Please carefully review the comments to properly understand how to display static and changing text on the display
 * You can also review videos on youtube that go into details about how to add more customization to your display etc.
 * But those are not needed for this test.
 * You can make your Display as useful as possible for your Prototpye
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//The OLEDs you have in your kit are 0.96" I2C 128x64 Monochrome OLEDs
// 0.96" is the screen size, I2C is the protocol it uses to talk to the Arduino
#define SCREEN_WIDTH 128 // OLED display width, in pixels. 
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define OLED_I2C_ADDRESS 0x3C // !!IMPORTANT!!: If OLED does not show any text, switch this value to 0x3D

int test_counter = 0; //Just a counter for this test. You won't need it in your prototype

void setup() {
  Serial.begin(9600);

  /* This section is used to initilize the OLED Display. If the display.begin() fails, it locks the setup into a loop.
  * You dont need to change anything. You can use this section of the code as is.
  * If you don't see anything on the screen, change the OLED_I2C_ADDRESS defined above to 0x3D 
  */
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever if the OLED did not initialize
  }
  
}

void loop() {

  /*
  * You can display things from loop() for from setup(). 
  * But remember: You need to call display.clear(); at the start of loop or to change the value
  * Or else, it will keep displaying the same thing multiple times.
  */

  //clearDisplay(); is called to clear the screen of any text. You can use this everytime you need to refresh the screen
  display.clearDisplay(); 

  display.setTextSize(1);             // Control the size of text. You can use a value of 1,2,3 etc. 
  display.setTextColor(SSD1306_WHITE); // Control the colour of the text. The display is Monochrome, so you can only use white.

  /* setCursor(x,y). This determines the position x,y coordinate where your text will be placed on the screen
  * The Display is a 128x64 display. Top left corner is (0,0), bottom right corner is (128,64) */
  display.setCursor(0,0);       

 /* !!IMPORTANT!!
 * If you notice carefully, the following function has string wrapped in the macro F()
 * This is used for static text. It saves the text directly into flash memory on Arduino
 * which is used for storing the program (Program Storage Space)
 * If you do not use F() for static text, it will be copied into SRAM which takes up too much space unnecessarily
 * 
 * NOTE: You must NOT use F() for variable text i.e value of pH, TDS, Turbidity etc. 
 */
  display.println(F("====== APSC 101 ====="));  // This is example of static text. Its a simple string and does not change


  display.setTextSize(2); // Display the next line in bigger size
  display.println(F("Counting.."));  // This is also static Text but specific to current state
  display.print(test_counter);  // This is a variable text. It will keep changing

  display.display(); // Actually draw everything on the screen.

  delay (1000);
  test_counter++; // Update the counter for next round

}
