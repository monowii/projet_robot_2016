#ifndef LIB_ROBOT_IO_H
#define LIB_ROBOT_IO_H

#include "IHM.h"

extern PwmOut moteur_d; //Moteur DROITE
extern PwmOut moteur_g; //Moteur GAUCHE

extern DigitalIn jack; //NUM0 - jack demarrage
extern DigitalIn fin_course; //NUM1 - capteur fin de course

extern DigitalIn bp_haut;
extern DigitalIn bp_bas;
extern DigitalIn bp_gauche;
extern DigitalIn bp_droite;

extern BusOut BusSelectMux; //Bus de selection de l'entrée analogique
extern AnalogIn AnaIn; //Sortie du mux connecté sur AnaIn

extern IHM ihm;

void maj_capteurs();
float lire_capteur(int capteur); //Lire la valeur analogique d'un capteur (dans [0,1])
int etat_seuil(float val, float seuil); //retourne vrai si la valeur est supérieur ou égale au seuil, sinon faux

float lire_pot(int pot_max); //Lire la valeur du potentiometre bleu dans l'interval [0,1]

#endif