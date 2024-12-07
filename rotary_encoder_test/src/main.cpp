#include <Arduino.h>
 
#define outputA 12
#define outputB 13

int counter = 0;
int aState;
int aLastState;
char readEncoder();
int b();
unsigned long prevTime;
char encoder;

void setup() { 
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);

  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
  prevTime = millis();
} 

void loop() {
  encoder = readEncoder();
  if (encoder != 0){
    Serial.println(encoder);
  }
}

char readEncoder(){
  char foo = 0;
  if (millis() >= (prevTime + 1)){
    aState = digitalRead(outputA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState > aLastState){
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(outputB) != aState && counter < 100) { 
        foo = 1;
      } else if (counter > 0) {
        foo = 2;
      }
    aLastState = aState; // Updates the previous state of the outputA with the current state}
    }
  }
  prevTime = millis();
  return foo;
}