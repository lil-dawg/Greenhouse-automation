//Thermometer
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8 // Data wire is plugged into digital pin 2 on the Arduino
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire); // Pass oneWire reference to DallasTemperature library

//Display
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
#include "custom_char.h"

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

//Input & Button Logic
const int numOfInputs = 4;
const int inputPins[numOfInputs] = {2,3,4,5};
int inputState[numOfInputs];
int lastInputState[numOfInputs] = {LOW,LOW,LOW,LOW};
bool inputFlags[numOfInputs] = {LOW,LOW,LOW,LOW};
long lastDebounceTime[numOfInputs] = {0,0,0,0};
long debounceDelay = 5;

//LCD Menu Logic
const int numOfScreens = 3;
int currentScreen = 0;
String screens[numOfScreens][2] = {{"Läge", ""}, {"Öppnings temp", char(0)+"C"}, {"Temperatur, "}};
int parameterValues[numOfScreens];
int parameterLimits[numOfScreens][2] = {{0, 1}, {10, 30}, {0, 0}};
String mode[] = {"Automatisk", "Manuell"};

/*class Menu {
  public:

    void parameterChange(int key) {
    if (currentScreen == 0) {
      
    }
    if(key == 0) {
      parameterValues[currentScreen]++;
    }else if(key == 1) {
      parameterValues[currentScreen]--;
    }
}

  
}*/

void setup() {
  for(int i = 0; i < numOfInputs; i++) {
    pinMode(inputPins[i], INPUT);
    digitalWrite(inputPins[i], HIGH); // pull-up 20k
  }
	
  lcd.begin(16, 2);
  createChars(lcd);
  //lcd.setBacklight(HIGH);

  //Initial Display
  lcd.print(char(0));
  lcd.setCursor(15,0);
  lcd.print(char(1));
  lcd.setCursor(15,1);
  lcd.print(char(2));
  delay(3000); 

  sensors.begin(); // Start up the library
  //Serial.begin(9600);
}

void loop() {
  setInputFlags();
  resolveInputFlags();

  //sensors.requestTemperatures(); // Send the command to get temperatures

  //print the temperature in Celsius
  //Serial.print("Temperature: ");
  //Serial.println("Temperature: " + String(sensors.getTempCByIndex(0)) + (char)176 + "C");

	//lcd.print("Temp: " + String(sensors.getTempCByIndex(0)) + "C");
  
}

void setInputFlags() {
  for(int i = 0; i < numOfInputs; i++) {
    int reading = digitalRead(inputPins[i]);
    if (reading != lastInputState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != inputState[i]) {
        inputState[i] = reading;
        if (inputState[i] == HIGH) {
          inputFlags[i] = HIGH;
        }
      }
    }
    lastInputState[i] = reading;
  }
}

void resolveInputFlags() {
  for(int i = 0; i < numOfInputs; i++) {
    if(inputFlags[i] == HIGH) {
      inputAction(i);
      inputFlags[i] = LOW;
      printScreen();
    }
  }
}

void inputAction(int input) {
  if(input == 0) {
    if (currentScreen == 0) {
      currentScreen = numOfScreens-1; //loop around
    }else{
      currentScreen--;
    }
  }else if(input == 1) {
    if (currentScreen == numOfScreens-1) {
      currentScreen = 0; //loop around
    }else{
      currentScreen++;
    }
  }else if(input == 2) {
    parameterChange(0);
  }else if(input == 3) {
    parameterChange(1);
  }
}

void parameterChange(int key) {
  int currentValue = parameterValues[currentScreen];
  int lowerLimit = parameterLimits[currentScreen][0];
  int upperLimit = parameterLimits[currentScreen][1];
  //increment
  if(key == 0 && currentValue < upperLimit) {
    parameterValues[currentScreen]++;
  //decrement
  }else if(key == 1 && currentValue > lowerLimit) {
    parameterValues[currentScreen]--;
  }
}

void printScreen() {
  lcd.clear();
  lcd.print(screens[currentScreen][0]);
  lcd.setCursor(0,1);
  if (currentScreen == 0) {
    lcd.print(mode[parameterValues[currentScreen]]);
  }
  else {
    lcd.print(parameterValues[currentScreen]);
  }
  lcd.print(" ");
  lcd.print(screens[currentScreen][1]);
  //arrows
  lcd.setCursor(15,0);
  lcd.print(char(1));
  lcd.setCursor(15,1);
  lcd.print(char(2));
}