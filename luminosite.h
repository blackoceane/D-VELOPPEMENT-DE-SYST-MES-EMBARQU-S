#ifndef LUMINOSITE_H
#define LUMINOSITE_H

class Luminosite {
public:
  Luminosite(int photoResPin,int led_pin);
  int getLuminosite();
  int getValeurMax();
  int getValeurMin();

private:
  int _photoResPin;
  int valeurMax;
  int valeurMin;
  int lum;
  int led_pin ;
};

#endif