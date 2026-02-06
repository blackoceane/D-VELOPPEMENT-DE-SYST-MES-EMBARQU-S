// PorteGarage.h
#pragma once
#include <Arduino.h>
#include <AccelStepper.h>
#include <OneButton.h>

class PorteGarage {
 
  public:
 
    enum Etat {
      NOT_INIT, // Non initialise 
      CALIB, // État de calibration
      OUVERT,
      OUVERTURE,
      FERME,
      FERMETURE,
      ARRET
    };
    
   PorteGarage(int pinButton, uint8_t step_pin1, uint8_t step_pin2, uint8_t step_pin3, uint8_t step_pin4) :
                   btn(pinButton), 
                   stepper(AccelStepper::FULL4WIRE, step_pin1, step_pin2, step_pin3, step_pin4) {
  etat = NOT_INIT;
  //previouState=etat;
  instance = this;
  btn.attachClick(buttonClick, instance);
   btn.attachLongPressStart(handleLongPress, instance);
  callback = NULL;
  stepper.setMaxSpeed(1000);
  stepper.setCurrentPosition(0); // Définit la position actuelle à 0

};



    Etat getEtat(){return etat;};
    void update();
   // PorteGarage &setCallBack(void (*callback)(bool moving, String));

  private:
    Etat etat;
    Etat previouState;
    AccelStepper stepper;
    OneButton btn;
    const int troisTours = 3 * 2038;
    static PorteGarage *instance;
    void ouvrir();
    void fermeture();
    void calibrer();
    void attente();
    static void buttonClick(PorteGarage *self);
    static void handleLongPress(PorteGarage *self);
      void calibrerEnter();
    void ouvrirEnter();
    void fermerEnter();
    void (*callback)(bool, String);
    void sendEvent(bool);
    void arret();
    void ouvert();
    void debut();
    void fermeOuverture();
    void fermer();
    void gererEtat();
};