// PorteGarage.cpp
#include "PorteGarage.h"

PorteGarage* PorteGarage::instance = nullptr;



void PorteGarage::buttonClick(PorteGarage *self) {
 
  switch (self->etat) {
    
    case CALIB:
      self-> ouvrirEnter();
    
      break;
    case OUVERT:
       
      self->fermerEnter();
      break;
    case FERME:
      self->fermeOuverture();
      
      break;
    case OUVERTURE:
    self->arret();
    break;
    case FERMETURE:
      self->arret();
      break;
       case ARRET:
     
    self->gererEtat() ;
      break;
    default:
      break;
  }

}


static void PorteGarage::handleLongPress(PorteGarage *self) 
{
  Serial.println("LONG PRESS");
  self->etat = CALIB;
  self->calibrer();
}


void PorteGarage:: gererEtat() 
{
  if (etat ==ARRET) 
  {
    
   
      // Determine the next state bas
    // Déterminer le prochain état en fonction de l'état précédent avant ARRET
      etat = (previouState == OUVERTURE) ? FERMETURE : OUVERTURE;
  } 
  else 
  {
     previouState = etat; // Stocker l'état précédent
    etat = ARRET;

  }
}


void PorteGarage::ouvrir() 
{
Serial.println("OUVERTURE");
stepper.moveTo(troisTours);
 stepper.run();
  if (stepper.distanceToGo() == 0) {
   
   
  sendEvent(false);
   etat = OUVERT;
  }
  

}


void PorteGarage::fermeture() 
{
Serial.println("FERMETURE");
  stepper.moveTo(-troisTours);
   stepper.run();
  if (stepper.distanceToGo() == 0) {
  
   sendEvent(false);
   Serial.println("FERMER");
   etat = FERME;
   
  }
 

}


void PorteGarage::fermeOuverture()
{
  etat=OUVERTURE;
}

void PorteGarage::ouvrirEnter() {
 //IL Y A PAS D ACTION ICI 
  
 //FAIRE LES INITIALISATIONS DES VARIABLES NECESSAIRE FAIRE LA PASSE A OUVERTURE
  etat = OUVERT;
 // stepper.moveTo(troisTours);// Déplacer le moteur pas à pas sur trois tours
  //sendEvent(true);

}


void PorteGarage::fermerEnter() 
{
  //IL Y A PAS D ACTION ICI 
  Serial.println("FERMER");
  etat = FERMETURE;
 //FAIRE LES INITIALISATIONS DES VARIABLES NECESSAIRE FAIRE LA PASSE A FERMETURE
  
  //stepper.moveTo(-troisTours); // Déplacer le moteur pas à pas sur trois tours en sens inverse
  sendEvent(true);
  
}

void PorteGarage::calibrer() 
{
  // Calibration code here
  sendEvent(false);
 // ACTION CALIBRER CODE 
 Serial.println("CALIBRER");
}


void PorteGarage::attente() 
{
  // Nothing to do here
}

void PorteGarage::arret() 
{
  Serial.println("ARRET");
  etat = ARRET;
 stepper.stop();
 sendEvent(false);
}

void PorteGarage::ouvert()
{
  Serial.println("OUVERT");
}
  void PorteGarage::debut()
{
 Serial.println("DEBUT");
}
 void PorteGarage::fermer()
{
 Serial.println("FERMER");
}
 void PorteGarage::sendEvent(bool moving) 
 {
  if (callback) {
    callback(moving, "Garage");
  }
}

void PorteGarage::update() 
{
  switch (etat) 
  {
    case OUVERT:
   ouvert();
   break;
    case FERME:
   // Serial.println("Fermer");
   fermer();
   break;
    case NOT_INIT:
      //attente();
     debut();
  
      break;
    case OUVERTURE:
      ouvrir();
      break;
    case FERMETURE:
      fermeture();
      break;
    case CALIB:
      calibrer();
      break;
    case ARRET:
      attente();
        break;
    default:
      break;
  }
  btn.tick();
}
