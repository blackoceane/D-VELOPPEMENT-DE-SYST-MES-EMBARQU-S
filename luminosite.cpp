#include "luminosite.h"
#include <Arduino.h>

Luminosite::Luminosite(int photoResPin,int led_pin ) {
  _photoResPin = photoResPin;
  valeurMax = 0;
  valeurMin = 1023;
  
}

int Luminosite::getLuminosite() {
  int valeur = analogRead(_photoResPin);
  if (valeur > valeurMax) {
    valeurMax = valeur;
  }
  if (valeur < valeurMin) {
    valeurMin = valeur;
  }
 int lum= map(valeur, 0, 1023, 0, 100);
    if (lum >= 30) {

      digitalWrite(led_pin, LOW);
    } else {
      digitalWrite(led_pin, HIGH);
    }
  return lum;
}

int Luminosite::getValeurMax() {
  return valeurMax;
}
int Luminosite::getValeurMin() {
  return valeurMin;
}