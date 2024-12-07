#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 13


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// I/O declarations
const int outerLimSwitch = 2;
const int innerLimSwitch = 3;
const int relay_1 = 4;
const int relay_2 = 5;

// Constant declarations
uint8_t openingTemp = 22;
uint8_t closingTemp = 20;
uint8_t resolution = 9;

// Variable declarations
int delayInMillis;
int lastTempRequest;
float temperature;

// function declarations
float getTemperature(void);
void ctrlActuator(float);

void setup(void)
{
  // setup ports
  pinMode(outerLimSwitch, INPUT);
  pinMode(innerLimSwitch, INPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);

  // start serial port
  Serial.begin(9600);
  Serial.println("Temp test non blocking");

  // Start up the library
  sensors.begin();
  sensors.setResolution(9);
  sensors.setWaitForConversion(false);
  delayInMillis = 750 / (1 << (12 - resolution));
  sensors.requestTemperatures();
  lastTempRequest = millis();

}

void loop(void){

  temperature = getTemperature();
  
  ctrlActuator(temperature);
}

float getTemperature(void){
  float temp;
  if (millis() - lastTempRequest >= delayInMillis){ // waited long enough??
    Serial.println(millis() - lastTempRequest);
    
    temp = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
    lastTempRequest = millis(); 

    Serial.println(temp);
  }
  return temp;
}

// function definitions
void ctrlActuator(float temp) {
  if (digitalRead(outerLimSwitch) == LOW && temp > openingTemp){
    digitalWrite(relay_1, HIGH);
    digitalWrite(relay_2, LOW);
  }
  else if (digitalRead(innerLimSwitch) == LOW && temp < closingTemp){
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, HIGH);
  }
  else{
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, LOW);
  }
}