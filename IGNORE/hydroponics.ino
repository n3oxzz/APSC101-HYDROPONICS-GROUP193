#include "hydroponics.h"

////////////////////////////////////////////////////////////////////////////////

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define OLED_I2C_ADDRESS 0x3C

#define PRESS_TIME 100

#define STOP_BUTTON_PIN A2
#define PAGE_BUTTON_PIN A3

namespace Interface {

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long timer = 0;

int page = 0;

bool stopToggle = HIGH;
bool pageToggle = HIGH;

void toggleStop();
void togglePage();

void init();
void update(double tds, double ph, bool ll);

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

}

////////////////////////////////////////////////////////////////////////////////

#define MIXING_MOTOR_PORT 1

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

}

////////////////////////////////////////////////////////////////////////////////

#define NUTRIENT_SERVO_PIN 0

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

}

////////////////////////////////////////////////////////////////////////////////

#define PH_PUMP_PORT 2

#define PH_FLOW_RATE 0

namespace Ph {

int startTime = 0;
int stopTime = 0;

double calculate(double tds);

void dispense(double amount);

bool isActive();

void init();
void update();

}

////////////////////////////////////////////////////////////////////////////////

#define PLANT_PUMP_PORT 3
#define WASTE_PUMP_PORT 4

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

}

////////////////////////////////////////////////////////////////////////////////

void setup () {

}

void loop () {

}

////////////////////////////////////////////////////////////////////////////////

void Interface::togglePage () {
  page =  (page + 1) % 2;
}

void Interface::toggleStop () {
  
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
  
  if (page == 0) {
    display.print(F("TDS: ")); display.println(tds);
    display.print(F("PH: ")); display.println(ph);
    display.print(F("LL: ")); display.println(ll);
  }
  
  if (page == 1) {
    display.println(F("HELLO WORLD!!!!!!!!!!"));
  }
  
  display.println(F("====================="));

  display.display();
}

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

////////////////////////////////////////////////////////////////////////////////

double Ph::calculate (double tds) {

}

void Ph::dispense (double amount) {

}

bool Ph::isActive () {

}

void Ph::init () {

}

void Ph::update () {

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

////////////////////////////////////////////////////////////////////////////////
