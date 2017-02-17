#include "lib_robot_io.hpp"
#include "lib_robot_globales.hpp"

PwmOut moteur_d(PB_5);
PwmOut moteur_g(PB_4);

DigitalIn jack(PB_7, PullUp);
DigitalIn fin_course(PB_6, PullDown);

DigitalIn bp_haut(PA_9, PullUp);
DigitalIn bp_bas(PB_0, PullUp);
DigitalIn bp_gauche(PB_7, PullUp);
DigitalIn bp_droite(PA_10, PullUp);

BusOut BusSelectMux(PA_8, PF_1, PF_0);
AnalogIn AnaIn(PB_1);

IHM ihm;

float lire_pot(int pot_max)
{
    BusSelectMux = 7;
    unsigned short val = AnaIn.read_u16() >> 4; //Enlever les 4 bits de poids faibles (car constants)
    float pot = (float)val / (float)pot_max; //On reduit la valeur de pot dans l'interval [0,1]
    if (pot > 1)
        return 1;
    else
        return pot;
}

float lire_capteur(int capteur)
{
    BusSelectMux = capteur;
    return AnaIn.read();
}

int etat_seuil(float val, float seuil)
{
    return val >= seuil ? 1 : 0;
}

void maj_capteurs() {
    capteur_rac_droite = etat_seuil(lire_capteur(0), 0.4);
    capteur_droite_extreme = etat_seuil(lire_capteur(1), seuil_capteurs);
    capteur_droite = etat_seuil(lire_capteur(2), seuil_capteurs);
    capteur_gauche = etat_seuil(lire_capteur(3), seuil_capteurs);
    capteur_gauche_extreme = etat_seuil(lire_capteur(4), seuil_capteurs);
    capteur_rac_gauche = etat_seuil(lire_capteur(5), 0.7);
}

