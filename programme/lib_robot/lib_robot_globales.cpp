#include "lib_robot_globales.hpp"

int capteur_rac_droite, capteur_droite_extreme, capteur_droite, capteur_gauche, capteur_gauche_extreme, capteur_rac_gauche;
float seuil_capteurs = 0.24f;
float vitesse_suivi_ligne = 0.63f;
float coef_virage_suivi_ligne = 0.35f;

bool raccourci_actif = true;
float vitesse_pre_raccourci = 0.3f;
float vitesse_raccourci = 0.5f;
float coef_virage_raccourci = 0.3f;
float timer_raccourci_debut_detection = 0.5f; //en secondes
float timer_raccourci_fin_detection = 0.9f; //en secondes

BusOut leds(PB_3, PA_7, PA_6, PA_5, PA_3, PA_1, PA_0, PA_2);

const short int pot_max = 3900;