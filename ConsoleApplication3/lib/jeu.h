#ifndef JEU
#define JEU

#define CONFIRMER 0
#define QUITTER 1
#define INCORRECT 2

#include <iostream>
#include "Joueur.h"

class Jeu {
    public:
        Jeu();
        ~Jeu();
        bool afficherStartUp(std::ostream& sout);
        int menuStartUp(std::ostream& sout, std::istream& sin);
        bool afficherReglage(std::ostream& sout);
        bool afficherTailleEnX(std::ostream& sout);
        bool afficherTailleEnY(std::ostream& sout);
        int menuReglage(std::ostream& sout, std::istream& sin);
        bool afficherInitJoueur(std::ostream& sout, Joueur *joueur);
        bool afficherInitTaille(std::ostream& sout, Joueur *joueur, int taille);
        int menuInitJoueur(std::ostream& sout, std::istream& sin,Joueur* joueur);
        bool afficherTir(std::ostream& sout, Joueur *joueur, Joueur *adversaire);
        int menuTir(std::ostream& sout, std::istream& sin,Joueur* joueur, Joueur* adversaire);
        bool afficherFin(std::ostream& sout);
        int menuFin(std::ostream& sout, std::istream& sin);
        void ajouterJoueur();
        Joueur* getJoueur(int index);
    private:
        int tailleEnX;
        int tailleEnY;
        std::vector<Joueur*> vecJoueur;
};

#endif