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
uint8_t openingTemp = 30;
uint8_t closingTemp = 20;

// function declarations
void ctrlActuator(float);

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  sensors.setResolution(9);
  Serial.println(sensors.getResolution());
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{
  unsigned long lastMillis = millis();
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    int elapsedTime = millis()-lastMillis;
    Serial.println(elapsedTime);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
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
  else{
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, LOW);
  }
}