#ifndef ALARME_H
#define ALARME_H

class Alarme {
public:
  Alarme(int buzzerPin, int redPin, int bluePin);
  void gererAlarme(int distance);
  void girophare();


private:
  int _buzzerPin;
  int _redPin;
  int _bluePin;
  unsigned long _alarmStartTime;
  bool _alarmActive;
  bool _lightActive;
  int currentLED;
};

#endif

