#include "alarme.h"
#include <Arduino.h>

Alarme::Alarme(int buzzerPin, int redPin, int bluePin) {
  _buzzerPin = buzzerPin;
  _redPin = redPin;
  _bluePin = bluePin;
  _alarmStartTime = 0;
  _alarmActive = false;
  _lightActive = false;
  currentLED = 1;
}

void Alarme::gererAlarme(int distance) {
  if (distance <= 10) {
  // tone(_buzzerPin, 100, 500);
    Serial.println("buzzzeeeeeeeeeeeeeeeeeeerrrrrrrrr");
    girophare();
   
    _alarmStartTime = millis();
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - _alarmStartTime >= 3000) 
    {
      noTone(_buzzerPin);
      analogWrite(_redPin, 0);
  analogWrite(_bluePin, 0);
       }
  }
}

void Alarme::girophare() {
  if (currentLED == 1) {
    analogWrite(_redPin, 0);
    analogWrite(_bluePin, 255);
    currentLED = 2;
  } else {
    analogWrite(_redPin, 255);
    analogWrite(_bluePin, 0);
    currentLED = 1;
  }
}

