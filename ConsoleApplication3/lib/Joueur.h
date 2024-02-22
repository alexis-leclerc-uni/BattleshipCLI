#ifndef JOUEUR
#define JOUEUR
#include <vector>
#include <iostream>
#include "Bateau.h"
#include "Carte.h"


class Joueur {
    public:
        Joueur();
        ~Joueur();
        bool aPerdu();
        uint8_t tirer(Coordonnee position, Joueur adversaire);
        bool ajouterBateau(int x, int y, bool horizontal, int taille);
        bool afficher(std::ostream &s);
        bool actualiseCarte();
    private:
        std::vector<Bateau*> bateau;
        Carte carte;
        int nbBateau;

};

#endif