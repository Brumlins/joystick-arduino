#include <Arduino.h>

// *Interfacing RGB LED with Arduino 
// * Author: Osama Ahmed 

//Defining  variable and the GPIO pin on Arduino
int redPin= 9;
int greenPin = 10;
int  bluePin = 11;

#define pinX A0
#define pinY A1
#define pinKey 2

int nulaX=0, nulaY=0;

void setup() {
  //Defining the pins as OUTPUT
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(pinKey, INPUT_PULLUP);
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  // načtení a uložení hodnot pro x a y osy
  nulaX = analogRead(pinX);
  nulaY = analogRead(pinY);
}

void setColor(int redValue, int greenValue, int blueValue) {
  if (greenValue<=0){
    greenValue=0;
  }
  if (blueValue<=0){
    blueValue=0;
  }
  if (redValue<=0){
    redValue=0;
  }
  analogWrite(redPin, redValue);
  analogWrite(greenPin,  greenValue);
  analogWrite(bluePin, blueValue);
}


void  loop() {
  int aktX, aktY, stavTlac;
  // načtení analogových hodnot osy x a y
  aktX = analogRead(pinX) - nulaX;
  aktY = analogRead(pinY) - nulaY;
  int aktB;
  stavTlac = digitalRead(pinKey);
  if (aktX > 0) {
    aktX = map(aktX, 0, 1023-nulaX, 0, 255);
  }
  else {
    aktX = map(aktX, 0, -nulaX, 0, -255);
  }
  if (aktY > 0) {
    aktY = map(aktY, 0, 1023-nulaY, 0, 255);
  }
  else {
    aktY = map(aktY, 0, -nulaY, 0, -255);
  }
  aktB=-aktY;
  // vytištění informací o souřadnicích
  // po sériové lince
  Serial.print("Souradnice X,Y = ");
  Serial.print(aktX);
  Serial.print(", ");
  Serial.print(aktY);
  setColor(aktX, aktY, aktB);
  // kontrola stavu tlačítka, v případě stisku
  // vytiskneme informaci po sériové lince
  if(stavTlac == LOW) {
    Serial.print(" | Tlacitko stisknuto.");
  }
  Serial.println();
  // volitelná pauza pro přehledný tisk
}

