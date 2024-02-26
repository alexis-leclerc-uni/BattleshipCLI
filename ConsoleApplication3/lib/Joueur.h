#ifndef JOUEUR
#define JOUEUR
#include <vector>
#include "Bateau.h"
#include "Carte.h"
#include <iostream>

class Joueur {
    public:
        Joueur(int tailleEnX, int tailleEnY);
        ~Joueur();
        bool aPerdu();
        int tirer(Coordonnee position, Joueur* adversaire);
        bool ajouterBateau(int x, int y, bool horizontal, int taille);
        bool afficher(std::ostream& s);
        bool actualiseCarte();
    private:
        std::vector<Bateau*> bateau;
        Carte *carte;

};

#endif