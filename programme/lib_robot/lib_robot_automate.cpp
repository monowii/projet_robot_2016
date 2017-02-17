#include "lib_robot_automate.hpp"
#include "lib_robot_globales.hpp"
#include "lib_robot_io.hpp"

AM_SUIVI_LIGNE am_suivi_ligne;
AM_RACCOURCI am_raccourci;

Timer timer_raccourci;

void automate_suivi_ligne() {
    float vitesse_instantanee;
    switch (am_raccourci) {
        case SUIVI_LIGNE:
            vitesse_instantanee = vitesse_suivi_ligne;
            break;
        case PRE_RACCOURCI:
            vitesse_instantanee = vitesse_pre_raccourci;
            break;
        case RACCOURCI:
            vitesse_instantanee = vitesse_raccourci;
            break;
        default:
            vitesse_instantanee = vitesse_suivi_ligne;
    }
    
    switch (am_suivi_ligne) {
        case TOUT_DROIT:
            moteur_d.write(vitesse_instantanee);
            moteur_g.write(vitesse_instantanee);

            if (!fin_course.read())
                am_suivi_ligne = STOP;
            else if (capteur_droite && !capteur_gauche)
                am_suivi_ligne = DROITE;
            else if (capteur_gauche && !capteur_droite)
                am_suivi_ligne = GAUCHE;
            break;

        case DROITE:
            moteur_d.write(vitesse_instantanee*coef_virage_suivi_ligne);

            if (!fin_course.read())
                am_suivi_ligne = STOP;
            else if (capteur_droite && capteur_gauche)
                am_suivi_ligne = TOUT_DROIT;
            break;
            
        case GAUCHE:
            moteur_g.write(vitesse_instantanee*coef_virage_suivi_ligne);

            if (!fin_course.read())
                am_suivi_ligne = STOP;
            else if (capteur_droite && capteur_gauche)
                am_suivi_ligne = TOUT_DROIT;
            break;
            
        case STOP:
            moteur_d.write(0);
            moteur_g.write(0);
            break;
    }
}

void automate_raccourci() {
    float temps_raccourci;
    
    switch(am_raccourci) {
        case SUIVI_LIGNE:
            automate_suivi_ligne();
            
            if (raccourci_actif && capteur_rac_gauche && !capteur_rac_droite) {
                am_raccourci = PRE_RACCOURCI;
                timer_raccourci.start();
            }

            break;

        case PRE_RACCOURCI:
            automate_suivi_ligne();

            temps_raccourci = timer_raccourci.read();

            if (capteur_rac_gauche && !capteur_rac_droite && temps_raccourci > timer_raccourci_debut_detection) {
                ihm.LCD_clear();
                ihm.LCD_gotoxy(0, 0);
                ihm.LCD_printf("temps_raccourci");
                ihm.LCD_gotoxy(1, 0);
                ihm.LCD_printf("%.4f", temps_raccourci);
                
                am_raccourci = PRE_RACCOURCI_VIRAGE;
                timer_raccourci.stop();
                timer_raccourci.reset();
                timer_raccourci.start();
            }
            if (temps_raccourci > timer_raccourci_fin_detection) {
                ihm.LCD_clear();
                ihm.LCD_gotoxy(0, 0);
                ihm.LCD_printf("temps_raccourci");
                ihm.LCD_gotoxy(1, 0);
                ihm.LCD_printf("%.4f", temps_raccourci);
                
                timer_raccourci.stop();
                timer_raccourci.reset();
                am_raccourci = SUIVI_LIGNE;
            }
            break;
        case PRE_RACCOURCI_VIRAGE:
            moteur_d.write(coef_virage_raccourci);
            moteur_g.write(0);

            temps_raccourci = timer_raccourci.read();

            if (temps_raccourci > 1 && capteur_droite) {
                am_raccourci = RACCOURCI;
            }
            break;

        case RACCOURCI:
            automate_suivi_ligne();

            if (capteur_rac_gauche) {
                am_raccourci = FIN_RACCOURCI_VIRAGE;
                timer_raccourci.reset();
            }
            break;

        case FIN_RACCOURCI_VIRAGE:
            moteur_d.write(coef_virage_raccourci);
            moteur_g.write(0);

            temps_raccourci = timer_raccourci.read();

            if (temps_raccourci > 1 && capteur_droite) {
                am_raccourci = SUIVI_LIGNE;
                timer_raccourci.stop();
                timer_raccourci.reset();
                
                raccourci_actif = false;
                
            }
            break;
    }
}