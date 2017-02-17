#ifndef LIB_ROBOT_GLOBALES_H
#define LIB_ROBOT_GLOBALES_H

#include <mbed.h>

extern int capteur_rac_droite, capteur_droite_extreme, capteur_droite, capteur_gauche, capteur_gauche_extreme, capteur_rac_gauche; //valeurs des capteurs après lecture avec lire_capteurs();
extern float vitesse_suivi_ligne; //vitesse du robot
extern float coef_virage_suivi_ligne; //coefficient (de preference <1) de la vitesse dans les virages
extern float seuil_capteurs; //seuil pour que son etat logique passe a 1

extern bool raccourci_actif;
extern float vitesse_pre_raccourci;
extern float vitesse_raccourci;
extern float coef_virage_raccourci;
extern float timer_raccourci_debut_detection;
extern float timer_raccourci_fin_detection;

extern BusOut leds; //Les 8 leds de la carte d'extension NBoard

extern const short int pot_max; //Le potentiometre n'atteint jamais la valeur max, on la definit donc avec un test

#endif