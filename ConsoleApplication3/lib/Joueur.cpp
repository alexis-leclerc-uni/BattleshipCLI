#include "Joueur.h"
//Description : Construit une instance de Joueur
//Entrée : Aucune entrée
//Sortie : Aucune sortie
Joueur::Joueur(int tailleEnX, int taillEnY)
{
    carte = new Carte(tailleEnX, taillEnY);
    chargement = -1;
    typeMissile = -1;
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
//Description : Retourne le nombre de bateau
//Entrée : Aucune entrée
//Sortie : Retourne le nombre de bateau
int Joueur::nBateau()
{
    int total = 0;
    for (int i = 0; i < bateau.size(); i++)
    {
        if (!bateau[i]->getCoule()) // Il en faut au moins un bateau vivant
            total += 1;
    }
    return total;
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
int Joueur::getChargement()
{
    return chargement;
}
//Description : passe le tour s'il est en chargement
//Entrée : Aucune entrée
//Sortie : Aucune sortie
void Joueur::setChargement(int charge)
{
    chargement = charge;
    return;
}
int Joueur::getTypeMissile()
{
    return typeMissile;
}
void Joueur::setTypeMissile(int type)
{
    typeMissile = type;
    return;
}
Coordonnee Joueur::getCordAttente()
{
    return cordAttente;
}
void Joueur::setCordAttente(Coordonnee cord)
{
    cordAttente = cord;
    return;
}
//Description : Afficher la carte du joueur
//Entrée : Aucune entrée
//Sortie : Retourne s'il a réussi à afficher la carte du joueur
bool Joueur::afficher()
{
    return false;
}
//Description : Actualise la carte du joueur
//Entrée : Aucune entrée
//Sortie : Retourne un bool (vrai si l'opération est réussie)
bool Joueur::actualiseCarte()
{
    return carte->initialiserBateau(bateau);
}