#ifndef LIB_ROBOT_AUTOMATE_H
#define LIB_ROBOT_AUTOMATE_H

#include <mbed.h>

typedef enum {TOUT_DROIT, DROITE, GAUCHE, STOP} AM_SUIVI_LIGNE; //Automate de suivi de ligne
extern AM_SUIVI_LIGNE am_suivi_ligne;
void automate_suivi_ligne();

typedef enum {SUIVI_LIGNE, PRE_RACCOURCI, PRE_RACCOURCI_VIRAGE, RACCOURCI, FIN_RACCOURCI_VIRAGE} AM_RACCOURCI;
extern AM_RACCOURCI am_raccourci;
extern Timer timer_raccourci;
void automate_raccourci();

#endif