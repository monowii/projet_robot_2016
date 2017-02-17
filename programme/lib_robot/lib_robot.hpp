#ifndef LIB_ROBOT_H
#define LIB_ROBOT_H

#include <mbed.h>

//ENTREES ET SORTIES
#include "lib_robot_io.hpp"
void afficher_leds_capteurs();
void attente_jack();
void afficher_equipe();


//GLOBALES
#include "lib_robot_globales.hpp"


//AUTOMATES
#include "lib_robot_automate.hpp"

//TESTS ET REGLAGES
bool test_capteurs();
bool test_moteurs();

bool regler_seuil();
bool regler_coef_virage_suivi();
bool regler_vitesse_suivi_ligne();

bool regler_raccourci_actif();
bool regler_vitesse_raccourci();
bool regler_vitesse_pre_raccourci();
bool regler_coef_virage_raccourci();
bool regler_timer_raccourci_debut_detection();
bool regler_timer_raccourci_fin_detection();

#endif