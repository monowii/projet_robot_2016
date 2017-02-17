#include "lib_robot.hpp"

void reglages_et_tests() {
    //periodes de pwm de 20kHz
    moteur_d.period_us(50);
    moteur_g.period_us(50);
    
    if (test_capteurs()) return;
    if (test_moteurs()) return;

    if (regler_seuil()) return;
    if (regler_vitesse_suivi_ligne()) return;
    if (regler_coef_virage_suivi()) return;
    
    if (regler_raccourci_actif()) return;
    if (regler_vitesse_raccourci()) return;
    if (regler_vitesse_pre_raccourci()) return;
    if (regler_coef_virage_raccourci()) return;
    if (regler_timer_raccourci_debut_detection()) return;
    if (regler_timer_raccourci_fin_detection()) return;
}

int main() {
    afficher_equipe();

    reglages_et_tests();

    attente_jack();

    while(1) {
        maj_capteurs();
        afficher_leds_capteurs();

        automate_raccourci();
    }
}
