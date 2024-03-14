#ifndef JOUEUR
#define JOUEUR
#include <vector>
#include "Bateau.h"
#include "Carte.h"
#include <iostream>

#define M_NORMAL  1
#define M_SONDE   2
#define M_LIGNE   3
#define M_COLONNE 4
#define M_BOMBE   5
 
class Joueur {
    public:
        Joueur(int tailleEnX, int tailleEnY);
        ~Joueur();
        bool aPerdu();
        int nBateau();
        int tirer(Coordonnee position, Joueur* adversaire);
        bool ajouterBateau(int x, int y, bool horizontal, int taille);
<<<<<<< HEAD
        int getChargement();
        void setChargement(int);
        int getTypeMissile();
        void setTypeMissile(int);
        Coordonnee getCordAttente();
        void setCordAttente(Coordonnee);
        bool afficher();
=======
        bool afficherHistoriqueTir(std::ostream& s);
        bool afficherCarteBateau(std::ostream& s);
>>>>>>> master
        bool actualiseCarte();
    private:
        std::vector<Bateau*> bateau;
        Carte *carte;
<<<<<<< HEAD
        int chargement;
        int typeMissile;
        Coordonnee cordAttente;

=======
        int tweaksAffichage(int nombre);
>>>>>>> master

};

#endif