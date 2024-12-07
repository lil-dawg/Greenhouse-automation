#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NonBlockingDallas.h>

#define ONE_WIRE_BUS 8 // Data wire is plugged into digital pin 2 on the Arduino
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature dallasTemp(&oneWire);
NonBlockingDallas temperatureSensors(&dallasTemp);

// I/O declarations
const int innerLimSwitch = 3;
const int outerLimSwitch = 4;
const int relay_1 = 5;
const int relay_2 = 6;

// Constant declarations
uint8_t openingTemp = 25;
uint8_t closingTemp = 20;
bool manualMode = 0;

// function declarations
void ctrlActuator(float);

void setup() {
  pinMode(innerLimSwitch, INPUT);
  pinMode(outerLimSwitch, INPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);

  Serial.begin(9600);

  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  ctrlActuator(temp);
}

// function definitions
void ctrlActuator(float temp) {
  if (digitalRead(outerLimSwitch) == LOW && temp > openingTemp ){
    digitalWrite(relay_1, HIGH);
    digitalWrite(relay_2, LOW);
  }
  else if (digitalRead(outerLimSwitch) == LOW && temp < closingTemp){
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, HIGH);
  }
}