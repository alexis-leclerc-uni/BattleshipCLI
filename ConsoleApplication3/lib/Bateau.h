#ifndef BATEAU
#define BATEAU

#include "Coordonnee.h"

class Bateau {
    public:
        Bateau(int x, int y, bool orientation, int taille);
        ~Bateau();
        bool getCoule();
        bool endommagerBateau(Coordonnee position);
        Coordonnee getCoordonnee();
        bool getOrientation();
        int getTaille();

    private:
        int taille;
        bool coule;
        bool* cases;
        Coordonnee coordonnee;
        bool horizontal; // Si vrai, le bateau est horizontal. Alors que si c'est faux, le bateau est verticale
};

#endif