#ifndef CARTE
#define CARTE
#include <vector>
#include <iostream>
#include "Bateau.h"
#include "Coordonnee.h"

//Type d'erreur
#define MISS 0
#define OUTOFBOUND 1
#define DEJATIRER 2

class Carte {
    public:
        Carte(int tailleEnX = 10, int tailleEnY = 10);
        ~Carte();
        bool initialiserBateau(std::vector<Bateau*> bateau);
        int tirer(Coordonnee position);
        bool dejaTirer(Coordonnee position);
        int getTailleEnX();
        int getTailleEnY();
        bool afficher();

    private:
        int* *tableau;
        int tailleEnX;
        int tailleEnY;
        int nbBateau;
};

#endif