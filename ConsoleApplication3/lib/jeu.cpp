#include "jeu.h"

//Description : Construit le jeu
//Entrée : rien
//Sortie : rien
Jeu::Jeu()
{
}
//Description : Déconstruit le jeu (déallouer la mémoire des Joueur)
//Entrée : rien
//Sortie : rien
Jeu::~Jeu()
{
    for (int i = 0; i < vecJoueur.size(); i++)
        delete vecJoueur[i];
}
//Description : Afficher le menu de démarrage (Demande s'il veut commencer et le joueur doit répondre par y/n)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherStartUp(std::ostream& sout)
{
    sout << "Bienvenue au Battleship" << std::endl;
    sout << "Continuer? Y/N" << std::endl;
    return false;
}
//Description : Demande au joueur s'il veut commencer une partie ou quitter
//Entrée : un canal de communication
//Sortie : 0 pour Confirmer et 1 pour Quitter
int Jeu::menuStartUp(std::ostream& sout, std::istream& sin)
{
    afficherStartUp(sout);
    char c;
    sin >> c;
    if (c == 'y' || c == 'Y')
        return CONFIRMER;
    if (c == 'n' || c == 'n')
        return QUITTER;
    return INCORRECT;
}
//Description : Afficher le menu de réglage
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherReglage(std::ostream& sout)
{
    sout << "C'est le temps des reglages" << std::endl;
    return false;
}
//Description : Afficher le menu de réglage (demande la taille en X)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTailleEnX(std::ostream& sout)
{
    sout << "Inscrivez la taille en X : ";
    return false;
}
//Description : Afficher le menu de réglage (demande la taille en Y)
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTailleEnY(std::ostream& sout)
{
    sout << "Inscrivez la taille en Y : ";
    return false;
}
//Description : Demande au joueur la taille de la carte
//Entrée : un canal de communication
//Sortie : 0 pour Confirmer la taille choisie, 1 pour revenir en arrière
int Jeu::menuReglage(std::ostream& sout, std::istream& sin)
{
    afficherReglage(sout);
    do {
        afficherTailleEnX(sout);
        sin >> tailleEnX;
    } while (tailleEnX <= 0);
    do {
        afficherTailleEnY(sout);
        sin >> tailleEnY;
    } while (tailleEnY <= 0);

    return CONFIRMER;
}
//Description : Afficher le menu pour que le joueur initialise ses bateaux
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherInitJoueur(std::ostream& sout, Joueur *joueur)
{
    sout << "Il faut placer les bateaux" << std::endl;
    return false;
}
//Description : Indique la taille du bateau
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherInitTaille(std::ostream& sout, Joueur *joueur, int taille)
{
    sout << "La taille est de " << taille << ". Placer selon le format suivant : x y horizontal" << std::endl;
    return false;
}
//Description : Le joueur installe ses bateaux
//Entrée : un canal de communication et la taille du bateau
//Sortie : 0 pour Confirmer, 1 pour revenir en arrière
int Jeu::menuInitJoueur(std::ostream& sout, std::istream& sin,Joueur* joueur)
{
    afficherInitJoueur(sout, joueur);
    int tailleBateau[] = {5,4,3,3,2};
    int x = -1; int y = -1;
    bool horizontal;
    for (int i = 0; i < 3; i++)
    {
        joueur->afficherCarteBateau(sout);
        do {
            afficherInitTaille(sout, joueur, tailleBateau[i]);
            sin >> x >> y >> horizontal;
        } while (!joueur->ajouterBateau(x,y,horizontal,tailleBateau[i]));
        
    }
    return CONFIRMER;
}
//Description : Afficher le menu pour que le joueur tir sur l'adversaire
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherTir(std::ostream& sout, Joueur *joueur, Joueur *adversaire)
{
    adversaire->afficherHistoriqueTir(sout);
    if (vecJoueur[0] == joueur)
        sout << "Joueur 1 : ";
    else
        sout << "Joueur 2 : ";
    sout << "Rentrer la position de votre missile (x y) : ";
    return false;
}
//Description : Le joueur tir sur son adversaire
//Entrée : un canal de communication
//Sortie : 0 si tout va bien
int Jeu::menuTir(std::ostream& sout, std::istream& sin,Joueur* joueur, Joueur* adversaire)
{
    Coordonnee cord = {-1,-1};
    int reponse;
    do {
        afficherTir(sout, joueur, adversaire);
        sin >> cord.x >> cord.y;
        reponse = joueur->tirer(cord, adversaire);
    } while (reponse == 1 || reponse == 2);
    return false;
}
//Description : Afficher le menu de fin
//Entrée : un canal de communication
//Sortie : Vrai si ça affiche
bool Jeu::afficherFin(std::ostream& sout)
{
    if (vecJoueur[1]->aPerdu())
        sout << "Le joueur 1 a gagné!!! ";
    else
        sout << "Le joueur 2 a gagné!!! ";
    sout << "Bravo, c'est la fin. Voulez-vous recommencer (Y/N) : ";
    return false;
}
//Description : Demande au joueur s'il veut continuer
//Entrée : un canal de communication
//Sortie : 0 si on recommence, 1 si on quitte
int Jeu::menuFin(std::ostream& sout, std::istream& sin)
{
    afficherFin(sout);
    char c;
    sin >> c;
    if (c == 'y' || c == 'Y')
        return CONFIRMER;
    if (c == 'n' || c == 'n')
        return QUITTER;
    return INCORRECT;
}
//Description : Ajoute un joueur au vector
//Entrée : rien
//Sortie : rien
void Jeu::ajouterJoueur()
{
    vecJoueur.push_back(new Joueur(tailleEnX,tailleEnY));
    return;
}
//Description : renvoie le joueur sélectionné
//Entrée : rien
//Sortie : le pointeur du joueur sélectionné
Joueur* Jeu::getJoueur(int index)
{
    return vecJoueur[index];
}