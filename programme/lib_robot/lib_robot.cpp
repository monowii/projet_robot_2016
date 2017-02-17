#include "lib_robot.hpp"
#include <cmath>
#include <string>

void afficher_leds_capteurs() {
    leds = capteur_rac_droite | capteur_droite_extreme<<1 | capteur_droite<<2 | capteur_gauche<<3 | capteur_gauche_extreme<<4 | capteur_rac_gauche<<5;
    //affichage de l'etat des capteurs sur le bus de leds
}

bool test_moteurs() {
    while (1) {
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("test moteurs");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("bp droite");
        wait(0.05);
        
        if (!bp_droite.read()) {
            float vitesse_test = 0;
            
            for (int i = 0 ; i < 5 ; i++) {
                while (vitesse_test < 1.0f) {
                    moteur_d.write(vitesse_test);
                    vitesse_test += 0.02f;
                    wait(0.02);
                }
                wait(10);
                moteur_d.write(0);
                vitesse_test = 0;
                
                while (vitesse_test < 1) {
                    moteur_g.write(vitesse_test);
                    vitesse_test += 0.02f;
                    wait(0.02);
                }
                wait(10);
                moteur_g.write(0);
                vitesse_test = 0;
            }
        }
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool test_capteurs() {
    while (1) {
        maj_capteurs();
        afficher_leds_capteurs();
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("tests pot %.4f", lire_pot(pot_max));
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("bp %d jack %d", !fin_course.read(), !jack.read());
        
        wait(0.05);
        
        if (jack.read()) {
            leds = 0;
            return true;
        }
        if (!bp_haut.read()) {
            leds = 0;
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_seuil() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        maj_capteurs();
        afficher_leds_capteurs();
        
        float pot = lire_pot(pot_max);
        if (abs(pot - seuil_capteurs) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            seuil_capteurs = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("seuil capteurs");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", seuil_capteurs);
        
        wait(0.05);
        
        if (jack.read()) {
            leds = 0;
            return true;
        }
        if (!bp_haut.read()) {
            leds = 0;
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
    
}

bool regler_coef_virage_suivi() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - coef_virage_suivi_ligne) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            coef_virage_suivi_ligne = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("coef virage suivi");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", coef_virage_suivi_ligne);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_vitesse_suivi_ligne() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - vitesse_suivi_ligne) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            vitesse_suivi_ligne = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("vitesse suivi");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", vitesse_suivi_ligne);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_raccourci_actif() {
    while (1) {
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("raccourci actif");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%s", raccourci_actif ? "vrai" : "faux");
        wait(0.05);
        
        if (!bp_droite.read()) {
            raccourci_actif = !raccourci_actif;
            while(!bp_droite.read()); //Attendre relachement
        }
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_vitesse_raccourci() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - vitesse_raccourci) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            vitesse_raccourci = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("vitesse rac");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", vitesse_raccourci);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_vitesse_pre_raccourci() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - vitesse_pre_raccourci) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            vitesse_pre_raccourci = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("vitesse pre rac");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", vitesse_pre_raccourci);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_coef_virage_raccourci() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - coef_virage_raccourci) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            coef_virage_raccourci = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("coef vir rac");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", coef_virage_raccourci);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_timer_raccourci_debut_detection() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - timer_raccourci_debut_detection) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            timer_raccourci_debut_detection = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("timer rac debut");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", timer_raccourci_debut_detection);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

bool regler_timer_raccourci_fin_detection() {
    bool repasse_par_val_defaut = false;
    
    while (1) {
        float pot = lire_pot(pot_max);
        if (abs(pot - timer_raccourci_fin_detection) < 0.05f)
            repasse_par_val_defaut = true;
        
        if (repasse_par_val_defaut)
            timer_raccourci_fin_detection = pot;
        
        ihm.LCD_clear();
        ihm.LCD_gotoxy(0, 0);
        ihm.LCD_printf("timer rac fin");
        ihm.LCD_gotoxy(1, 0);
        ihm.LCD_printf("%.4f", timer_raccourci_fin_detection);
        wait(0.05);
        
        if (jack.read()) {
            return true;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return false;
        }
    }
}

void attente_jack() {
    ihm.LCD_clear();
    ihm.LCD_gotoxy(0, 0);
    ihm.LCD_printf("ATTENTE JACK");
    
    while(!jack.read()); //Attente debrancher jack
    
    ihm.LCD_clear();
}

void afficher_equipe() {
    std::string noms("JULES DUPEROUX, SARAH CAMPOS, HUGO LUU");
    
    ihm.LCD_clear();
    ihm.LCD_gotoxy(0, 0);
    ihm.LCD_printf("=[REP BERTELLI]=");
    
    Timer tick;
    tick.start();
    
    int i = 0;
    while (i < noms.size()) {
        if (tick.read() > 0.2f) {
            std::string msg = noms.substr(i, 16);
            ihm.LCD_gotoxy(1, 0);
            ihm.LCD_printf("%s", msg);
            
            tick.reset();
            tick.start();
            i++;
        }
        
        if (jack.read()) {
            return;
        }
        if (!bp_haut.read()) {
            while(!bp_haut.read()); //Attendre relachement
            return;
        }
    }
    
    
}
