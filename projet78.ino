// PorteGarage.ino
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneButton.h>
#include <HCSR04.h>
#include <LiquidCrystal.h>
#include <AccelStepper.h>
#include "PorteGarage.h"
#include "luminosite.h"
#include "alarme.h"
#include"PorteGarage.h"

#define bluePin 6
#define redPin 5
#define LCD_ADDR 0x27

const byte triggerPin = 12;
const byte echoPin = 13;

HCSR04 hc(triggerPin, echoPin);
int distance;
enum etape { afflcd, LUM_DIST, CALIBRATION };
etape currentState = LUM_DIST;
int lastValidDistance = 0;
int buzzerPin = 7;
int led_pin = 2;
int btn_pin = 3;
int photoResPin = A0;
bool calibrationMode = false;
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
OneButton button(btn_pin, true);
//unsigned long currentTime = 0;

unsigned long currentMillis = 0;

Luminosite luminosite(photoResPin,led_pin);
Alarme alarme(buzzerPin, redPin, bluePin);

const int buttonPin = 4;
const int stepperPin1 = 11;
const int stepperPin2 = 10;
const int stepperPin3 = 9;
const int stepperPin4 = 8;
const int  MotorInterfaceType = 4 ;

PorteGarage porte(4, 11, 9, 10, 8);

bool isCalibrated = false;

void setup() {
  Serial.begin(9600);
 // porte.setCallBack(eventMoteur);
  pinMode(led_pin, OUTPUT);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  button.attachClick(click);
  button.attachDoubleClick(doubleClick);

  pinMode(buzzerPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);

}

int distanceSon(int currentMillis) {
  distance = hc.dist();
  if (distance > 0) {              // Vérifier que la valeur est valide
    lastValidDistance = distance;  // Mettre à jour la dernière valeur valide
  }
  return lastValidDistance;

  // Utiliser lastValidDistance au lieu de distance
}
void click() {

  Serial.println(" Pressed!");
  if (currentState == CALIBRATION) {
    currentState = LUM_DIST;
  }

  else {
    currentState = CALIBRATION;
  }
}
void doubleClick() {
  currentState = CALIBRATION;
  calibrationMode = false;
  /*valeurMin = 1023;
  valeurMax = 0;*/
}
void affIchelcd(int distance, int lum, long currentMillis) {
  
  static unsigned long previousMillis = 0;
  const int rate = 50;
  //Serial.print("boss///***/*/*/-/*/");
  if (currentMillis - previousMillis >= rate) {
    previousMillis = currentMillis;
    //  Serial.print("basic ///***/*/*/-/*/");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F(" Lum : "));
    lcd.print(lum);
    lcd.print(F(" %"));
    lcd.setCursor(0, 1);
    lcd.print(F("Dist : "));
    lcd.print(lastValidDistance);
    lcd.print(F(" cm"));
  }
}


void loop() {
  currentMillis = millis();
  button.tick();
  
  //porte.update();
 
  switch (currentState) {
    case LUM_DIST:
      lastValidDistance = distanceSon(currentMillis);
      affIchelcd(lastValidDistance, luminosite.getLuminosite(), currentMillis);
      alarme.gererAlarme(lastValidDistance);
    
      break;

    case CALIBRATION:
luminosite.getValeurMax();
luminosite.getValeurMin();
      break;
  }

}


