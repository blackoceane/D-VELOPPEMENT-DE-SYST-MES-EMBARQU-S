# DEVELOPPEMENT-DE-SYSTEMES-EMBARQUES
 ## Maison intelligente complète : Alarme HC-SR04 + Porte garage motorisée + Manette IR 
 Ce projet est divisé en 3 parties 
 ##  Premiére Partie- Système d'Alarme (BASE)
 ### Fonctionnalités
| Composant | Comportement |
|-----------|--------------|
| **Buzzer** | Son continu si distance ≤ 10cm |
| **LED RGB** | Bleu - Rouge (gyrophare police) |
| **HC-SR04** | Déclenchement précis 10cm |
| **Timer** | Arrêt auto après 3s silence |

##  Deuxiéme Partie - Ouverture Porte Garage
 ### Fonctionnalités
| Composant | Comportement |
|-----------|--------------|
| **Bouton poussoir** | Calibration (3s+), Ouverture/Fermeture, Arrêt d'urgence, Inversion sens |
| **Moteur pas-à-pas** | Monte jusqu'à position MAX (calibration), descend à 0, stop immédiat |
| **AccelStepper** | Contrôle précis vitesse/accélération, positions mémorisées |
| **DEL intégrée** | Clignote rapide 100ms UNIQUEMENT pendant mouvement |
| **Sécurité** | Bloqué si jamais calibré - aucun mouvement possible |
| **États** | 	7 états : NON_CALIBRE -> CALIBRATION -> OUVERTE/FERMÉE/ARRET |

##  Troisiéme Partie - Porte Garage + Manette IR
 ### Fonctionnalités
| Composant             | Comportement                                                                   |
| --------------------- | ------------------------------------------------------------------------------ |
| **Refactorisation**       | Classe PorteGarage étendue - Intégration manette IR dans constructeur existant |
| **Manette IR - Power**    |  Verrouille/Déverrouille porte (bloque TOUS les inputs bouton/IR)            |
| **Manette IR - Bouton 1** |  Ouvrir porte (uniquement si déverrouillée)                                  |
| **Manette IR - Bouton 2** |  Fermer porte (uniquement si déverrouillée)                                  |
| **DEL intégrée**          | ALLUMÉE EN PERMANENCE = Porte VERROUILLÉE                                      |
| **Sécurité verrou**       | AUCUNE action possible (bouton + IR) quand verrouillé                          |

##  Problématiques techniques globales

 | Problématique               | Description                                              | Solution appliquée                                        |
| --------------------------- | -------------------------------------------------------- | --------------------------------------------------------- |
| Dépendance séquentielle     | Impossible d'avancer sans compléter étape précédente     | Planification rigoureuse des étapes                       |
| Intégration incrémentielle  | Ajouter nouveaux modules SANS casser l'existant          | Architecture modulaire - Chaque labo = nouvelle classe    |
| Code initial unique fichier | Embrouillement rapide + maintenance impossible           | Refactorisation POO - plusieurs fichiers/classes + main.ino central |
| Sécurité prototype Arduino  | Risque d'endommagement/perte lors transport école-maison |  Montage démontable + Faire le moins de route possible     |
| Calibration variable        | Position MAX change selon lumière/pièce                  | Recalibration auto à chaque démarrage (bouton 3s)         |
| Gestion 15+ états complexes | États imbriqués + transitions multiples                  | Machine à états finie enum Etat + switch optimisé         |

## Historique du projet

| **Date**           | **Labo**          | **Mise à jour**                            | 
| -------------- | ------------- | -------------------------------------------------- | 
| 5 avril 2024  | Partie 01       | Création - Système d'alarme HC-SR04 + Gyrophare    | 
| 25 avril 2024  | Partie 02       | Ajout PorteGarage - Calibration + Moteur pas-à-pas | 
| 7 mai 2024     | Partie 03       | Refactorisation IR - Manette + Verrouillage        | 
| 6 février 2026 | Documentation | README complet + GitHub structuré                  | 

 
