#include "hydroponics.h"

////////////////////////////////////////////////////////////////////////////////

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define OLED_I2C_ADDRESS 0x3C

#define PRESS_TIME 100

#define STOP_BUTTON_PIN 50
#define PAGE_BUTTON_PIN 51

namespace Interface {

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long timer = 0;

int PAGE = 0;
int STOP = 1;

bool stopToggle = HIGH;
bool pageToggle = HIGH;

void toggleStop();
void togglePage();

void init();
void update(double tds, double ph, bool ll);
void stop();

}

////////////////////////////////////////////////////////////////////////////////

#define TDS_SENSOR_PIN A4

#define TDS_TARGET 1000

#define TDS_NOTHING 0

#define PH_SENSOR_PIN A5

#define PH_TARGET 6

#define PH_SLOPE -5.82524272
#define PH_OFFSET 12.12621359

#define LL_SENSOR_PIN 30

#define LL_DETECTED LOW

namespace Sensors {

GravityTDS gravityTDS;

double getCurrentTDS();
double getCurrentPH();

bool isMainWaterLow();
bool isPlantWaterLow();

void init();
void update();
void stop();

}

////////////////////////////////////////////////////////////////////////////////

#define MIXING_MOTOR_PORT 4

#define MIXING_FAST 0
#define MIXING_SLOW 0

#define MIXING_IDLE 0

namespace Mixer {

AF_DCMotor motor(MIXING_MOTOR_PORT);

unsigned long startTime = 0;
unsigned long stopTime = 0;

int currentSpeed = 0;

void run(int speed, unsigned long time);

bool isActive();

void init();
void update();
void stop();

}

////////////////////////////////////////////////////////////////////////////////

#define NUTRIENT_SERVO_PIN 9

#define NUTRIENT_FILL_ANGLE 0
#define NUTRIENT_DROP_ANGLE 180

#define NUTRIENT_FILL_TIME 2000
#define NUTRIENT_DROP_TIME 4000
#define NUTRIENT_IDLE_TIME 6000

#define NUTRIENT_POCKET 0
#define NUTRIENT_SLOPE 0

namespace Nutrients {

bool flag = false;

Servo servo;

unsigned long startTime = 0;

int required = 0;

int calculate(double tds);

void dispense(int amount);

bool isActive();

void init();
void update();
void stop();

}

////////////////////////////////////////////////////////////////////////////////

#define PH_PUMP_PORT 3

#define PH_FLOW_RATE (70.0/60.0)

#define PH_SLOPE_5 0.0
#define PH_SLOPE_6 0.0

namespace Ph {

AF_DCMotor pump(PH_PUMP_PORT);

unsigned long startTime = 0;
unsigned long stopTime = 0;

double calculate(double ph);

void dispense(double amount);

bool isActive();

void init();
void update();
void stop();

}

////////////////////////////////////////////////////////////////////////////////

#define PLANT_PUMP_PORT 2
#define WASTE_PUMP_PORT 1

namespace Transfer {

AF_DCMotor plantPump(PLANT_PUMP_PORT);
AF_DCMotor wastePump(WASTE_PUMP_PORT);

bool plantActive = false;
bool wasteActive = false;

void runPlant();
void runWaste();

bool isPlantActive();
bool isWasteActive();

void init();
void update();
void stop();

}

////////////////////////////////////////////////////////////////////////////////

void initSubsystems () {
  Interface::init(); 
  Sensors::init(); 
  Mixer::init(); 
  Nutrients::init(); 
  Ph::init(); 
  Transfer::init();
}

void updateSubsystems () {
  Interface::update(
    Sensors::getCurrentTDS(),
    Sensors::getCurrentPH(),
    Sensors::isPlantWaterLow()
  );
  
  Sensors::update(); 
  
  if (!Interface::STOP) {
    Mixer::update(); 
    Nutrients::update(); 
    Ph::update(); 
    Transfer::update();
  }
}

void stopSubsystems () {
  Interface::stop();
  Sensors::stop(); 
  Mixer::stop(); 
  Nutrients::stop(); 
  Ph::stop(); 
  Transfer::stop();
}

bool isAnythingActive () {
  return Mixer::isActive() || Nutrients::isActive() || Ph::isActive() || Transfer::isPlantActive() || Transfer::isWasteActive();
}

////////////////////////////////////////////////////////////////////////////////

void setup () { initSubsystems(); }

void loop () {
  updateSubsystems(); 
  
  if (!Interface::STOP) {
    double tds = Sensors::getCurrentTDS();
    double ph = Sensors::getCurrentPH();
    
    if (Sensors::isMainWaterLow() && !isAnythingActive()) { Transfer::runWaste(); }
    
    if (tds < TDS_TARGET && !isAnythingActive()) {
      int amount = Nutrients::calculate(tds); 
      
      if (amount > 0) { 
        Nutrients::dispense(amount); 
        Mixer::run(MIXING_FAST, (unsigned long)(amount * NUTRIENT_IDLE_TIME + 1000));
      }
    }
    
    if (ph < PH_TARGET && !isAnythingActive()) {
      double amount = Ph::calculate(ph);
      
      if (amount > 0) { 
        Ph::dispense(amount); 
        Mixer::run(MIXING_FAST, (unsigned long)(1000 * amount / PH_FLOW_RATE + 1000));
      }
    }

    if (Sensors::isPlantWaterLow() && !isAnythingActive()) { Transfer::runPlant(); }
  }
}

////////////////////////////////////////////////////////////////////////////////

void Interface::togglePage () {
  PAGE =  (PAGE + 1) % 2;
}

void Interface::toggleStop () {
  if (STOP == 1) {
    //initSubsystems();
    STOP = 0;
  }
  else {
    stopSubsystems();
    STOP = 1;
  }
}

void Interface::init () {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS);
  
  pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PAGE_BUTTON_PIN, INPUT_PULLUP);
}

void Interface::update (double tds, double ph, bool ll) {
  if (digitalRead(STOP_BUTTON_PIN) == LOW && stopToggle == HIGH) {
    if (millis() > timer + PRESS_TIME) {
      toggleStop();
      timer = millis();
    }
  }
  
  if (digitalRead(PAGE_BUTTON_PIN) == LOW && pageToggle == HIGH) {
    if (millis() > timer + PRESS_TIME) {
      togglePage();
      timer = millis();
    }
  }
  
  stopToggle = digitalRead(STOP_BUTTON_PIN);
  pageToggle = digitalRead(PAGE_BUTTON_PIN);
  
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  display.println(F("====== APSC 101 ====="));
  
  if (PAGE == 0) {
    display.print(F("TDS: ")); display.println(tds);
    display.print(F("PH: ")); display.println(ph);
    display.print(F("LL: ")); display.println(ll);
  }
  
  if (PAGE == 1) {
    display.println(F("..."));
  }
  
  display.println(F("====================="));

  display.display();
}

void Interface::stop () {}

////////////////////////////////////////////////////////////////////////////////

double Sensors::getCurrentTDS () {
  return gravityTDS.getTdsValue();
}

double Sensors::getCurrentPH () {
  float voltage = analogRead(PH_SENSOR_PIN) * (5.0 / 1023.0);

  return PH_SLOPE * voltage + PH_OFFSET;
}

bool Sensors::isMainWaterLow () {
  return gravityTDS.getTdsValue() <= TDS_NOTHING;
}

bool Sensors::isPlantWaterLow () {
  return digitalRead(LL_SENSOR_PIN) != LL_DETECTED;
}

void Sensors::init () {
  gravityTDS.setPin(TDS_SENSOR_PIN);

  gravityTDS.setAref(5.0);
  gravityTDS.setAdcRange(1024);

  gravityTDS.begin();

  pinMode(PH_SENSOR_PIN, INPUT);
  pinMode(LL_SENSOR_PIN, INPUT);
}

void Sensors::update () { gravityTDS.update(); }

void Sensors::stop () {}

////////////////////////////////////////////////////////////////////////////////

void Mixer::run (int speed, unsigned long time) {
  startTime = millis();
  stopTime = startTime + time;

  currentSpeed = speed;
}

bool Mixer::isActive () {
  return millis() < stopTime; 
}

void Mixer::init () {
  
}

void Mixer::update () {
  if (millis() > stopTime) {
    motor.setSpeed(MIXING_IDLE);
    motor.run(FORWARD);
    return;
  }

  if (millis() < startTime + 125) {
    motor.setSpeed(currentSpeed / 4);
    motor.run(FORWARD);
    return;
  }
  if (millis() < startTime + 250) {
    motor.setSpeed(currentSpeed / 2);
    motor.run(FORWARD);
    return;
  }

  if (millis() < stopTime - 250) {
    motor.setSpeed(currentSpeed);
    motor.run(FORWARD);
    return;
  }

  if (millis() < stopTime - 125) {
    motor.setSpeed(currentSpeed / 2);
    motor.run(FORWARD);
    return;
  }
  if (millis() < stopTime - 000) {
    motor.setSpeed(currentSpeed / 4);
    motor.run(FORWARD);
  }
}

void Mixer::stop () {
  motor.setSpeed(0);
  motor.run(RELEASE);

  startTime = millis();
  stopTime = millis();  
}

////////////////////////////////////////////////////////////////////////////////

int Nutrients::calculate (double tds) {
  return (int)(NUTRIENT_SLOPE * (TDS_TARGET - tds) / NUTRIENT_POCKET);
}

void Nutrients::dispense (int amount) {
  required = amount;
  
  startTime = millis();
}

bool Nutrients::isActive () {
  return required > 0;
}

void Nutrients::init () {
  servo.attach(NUTRIENT_SERVO_PIN);
}

void Nutrients::update () {
  if (required <= 0) {
    return;
  }
  
  if (millis() > startTime + NUTRIENT_IDLE_TIME) {
    required -= 1;
    startTime = millis();
    flag = false;
    return;
  }
  
  if (millis() < startTime + NUTRIENT_FILL_TIME) {
    if (flag == false) {
      servo.write(NUTRIENT_FILL_ANGLE);
      flag = true;
    }
    return;
  }
  if (millis() < startTime + NUTRIENT_DROP_TIME) {
    if (flag == true) {
      servo.write(NUTRIENT_DROP_ANGLE);
      flag = false;
    }
    return;
  }
  if (millis() < startTime + NUTRIENT_IDLE_TIME) {
    if (flag == false) {
      servo.write(NUTRIENT_FILL_ANGLE);
      flag = true;
    }
  }
  
}

void Nutrients::stop () {
  required = 0;
}

////////////////////////////////////////////////////////////////////////////////

double Ph::calculate (double ph) {
  if (ph < 5.0) {
    return (PH_SLOPE_5 * (PH_TARGET - ph));
  }
  
  if (ph < 6.0) {
    return (PH_SLOPE_6 * (PH_TARGET - ph));
  }
  else {
    return 0.0;
  }
}

void Ph::dispense (double amount) {
  startTime = millis();
  
  stopTime = millis() + (unsigned long)(1000 * amount / PH_FLOW_RATE);

  pump.setSpeed(255);  
  pump.run(FORWARD);
}

bool Ph::isActive () {
  return millis() < stopTime;
}

void Ph::init () {

}

void Ph::update () {
  if (millis() >= stopTime) {
    pump.setSpeed(0);
    pump.run(RELEASE);
  }
}

void Ph::stop () {
  pump.setSpeed(0);
  pump.run(RELEASE);


  startTime = millis();
  stopTime = millis();  
}

////////////////////////////////////////////////////////////////////////////////

void Transfer::runPlant () {
  plantActive = true;

  plantPump.setSpeed(255);
  plantPump.run(FORWARD);  
}

void Transfer::runWaste () {
  wasteActive = true;

  wastePump.setSpeed(255);
  wastePump.run(FORWARD);
}

bool Transfer::isPlantActive () {
  return plantActive;
}

bool Transfer::isWasteActive () {
  return wasteActive;
}

void Transfer::init () {

}

void Transfer::update () {
  if (!Sensors::isPlantWaterLow()) {
    plantActive = false;

    plantPump.setSpeed(0);
    plantPump.run(RELEASE);
  }

  if (!Sensors::isMainWaterLow()) {
    wasteActive = false;

    wastePump.setSpeed(0);
    wastePump.run(RELEASE);
  }
}

void Transfer::stop () {  
    plantActive = false;

    plantPump.setSpeed(0);
    plantPump.run(RELEASE);


    wasteActive = false;

    wastePump.setSpeed(0);
    wastePump.run(RELEASE);
}

////////////////////////////////////////////////////////////////////////////////
