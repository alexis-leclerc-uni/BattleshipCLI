#include "Joueur.h"
//Description : Construit une instance de Joueur
//Entrée : Aucune entrée
//Sortie : Aucune sortie
Joueur::Joueur(int tailleEnX, int taillEnY)
{
    carte = new Carte(tailleEnX, taillEnY);
}
//Description : Déconstruteur d'une instance de Joueur
//Entrée : Aucune entrée
//Sortie : Aucune sortie
Joueur::~Joueur()
{
    for (int i = 0; i < bateau.size(); i++)
    {
        delete bateau[i];
    }
    delete carte;
}
//Description : retourne si le joueur a perdu
//Entrée : Aucune entrée
//Sortie : Retourne un bool (vrai si le joueur a perdu)
bool Joueur::aPerdu()
{
    for (int i = 0; i < bateau.size(); i++)
    {
        if (!bateau[i]->getCoule()) // Il en faut au moins un bateau vivant
            return false;
    }
    return true;
}
//Description : Tirer permet d'envoyer un missile sur la carte de l'adversaire
//Entrée : Prend la position du tir, le joueur adversaire
//Sortie : Retourne si le tir est effectué (même si le tir n'est pas un hit, il retourne vrai)
int Joueur::tirer(Coordonnee position, Joueur* adversaire)
{
    //S'il y a une erreur (déjà tirer ou Out Of Bound)
    int etatCase = adversaire->carte->tirer(position);
    //std::cout << "Etat Case = " << etatCase << std::endl;
    if (etatCase == DEJATIRER || etatCase == OUTOFBOUND)
        return etatCase;
    if (etatCase == MISS)
        return MISS;
    //Le tir est réussi
    etatCase -= 3; // pour obtenir l'index du bateau

    if (adversaire->bateau[etatCase]->endommagerBateau(position))
        return 3; //Erreur dans endommagerBateau
    return 0; // Le tout est réussi
}
//Description : La fonction permet d'installer un bateau sur la carte
//Entrée : Prend la position, l'orientation et la taille
//Sortie : Retourne si le bateau a été placé
bool Joueur::ajouterBateau(int x, int y, bool horizontal, int taille)
{
    //Vérifie que le bateau est dans la carte
    if (horizontal) //horizontal
    {
        if (!(0 <= x && x + taille - 1 < carte->getTailleEnX() && 0 <= y && y < carte->getTailleEnY()))
            return false;
    }
    else { //vertical
        if (!(0 <= y && y + taille - 1 < carte->getTailleEnY() && 0 <= x && x < carte->getTailleEnX()))
            return false;
    }
    //Vérifie qu'il n'y a pas de superposition entre bateau
    for (int i = 0; i < bateau.size(); i++)
    {
        if (horizontal == true && bateau[i]->getOrientation() == false && bateau[i]->getCoordonnee().y <= y && y < bateau[i]->getCoordonnee().y + bateau[i]->getTaille() && x <= bateau[i]->getCoordonnee().x && bateau[i]->getCoordonnee().x < x + taille)
            return false;
        if (horizontal == false && bateau[i]->getOrientation() == true && bateau[i]->getCoordonnee().x <= x && x < bateau[i]->getCoordonnee().x + bateau[i]->getTaille() && y <= bateau[i]->getCoordonnee().y && bateau[i]->getCoordonnee().y < y + taille)
            return false;
        if (horizontal == true && bateau[i]->getOrientation() == true && y == bateau[i]->getCoordonnee().y && bateau[i]->getCoordonnee().x - taille < x && x < bateau[i]->getCoordonnee().x + bateau[i]->getTaille())
            return false;
        if (horizontal == false && bateau[i]->getOrientation() == false && x == bateau[i]->getCoordonnee().x && bateau[i]->getCoordonnee().y - taille < y && y < bateau[i]->getCoordonnee().y + bateau[i]->getTaille())
            return false;
    }
    // Le bateau peut être placé
    bateau.push_back(new Bateau(x, y, horizontal, taille));
    actualiseCarte();
    return true;
}
//Description : Afficher la carte du joueur
//Entrée : Aucune entrée
//Sortie : Retourne s'il a réussi à afficher la carte du joueur
bool Joueur::afficherHistoriqueTir(std::ostream& s)
{
    int sizeX, sizeY;
    sizeX = carte->getTailleEnX();
    sizeY = carte->getTailleEnY();

    std::string beginRouge = "\033[31m";
    std::string beginGris = "\033[31m";
    std::string escape= "\033[0m";

    std::string contenuCase = "";


    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            switch (this->tweaksAffichage(carte->getPositionTableau(y, x)))
            {
                case 0:
                    contenuCase = " ";
                    break;
                case 1:
                    contenuCase = "*";
                    break;
                case 2:
                    contenuCase = beginRouge + "*" + escape;
                    break;
                case 3:
                    contenuCase = " ";
                    break;
            }
            s << "[" << contenuCase << "]";
            //s << "[" << carte->getPositionTableau(y, x) << "]";
        }
        s << std::endl;
    }
    
    return false;
}
bool Joueur::afficherCarteBateau(std::ostream& s)
{
    int sizeX, sizeY;
    sizeX = carte->getTailleEnX();
    sizeY = carte->getTailleEnY();

    std::string beginRouge = "\033[31m";
    std::string beginGris = "\033[38;5;214m";
    std::string escape= "\033[0m";

    std::string contenuCase = "";


    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            switch (this->tweaksAffichage(carte->getPositionTableau(y, x)))
            {
                case 0:
                    contenuCase = " ";
                    break;
                case 1:
                    contenuCase = "*";
                    break;
                case 2:
                    contenuCase = beginRouge + "*" + escape;
                    break;
                case 3:
                    contenuCase = beginGris + "*" + escape;
                    break;
            }
            s << "[" << contenuCase << "]";
            //s << "[" << carte->getPositionTableau(y, x) << "]";
        }
        s << std::endl;
    }
    
    return false;
}
//Description : Actualise la carte du joueur
//Entrée : Aucune entrée
//Sortie : Retourne un bool (vrai si l'opération est réussie)
bool Joueur::actualiseCarte()
{
    return carte->initialiserBateau(bateau);
}

int Joueur::tweaksAffichage(int nombre) {
    if (nombre > 2) {
        return 3;
    }
    return nombre;
}