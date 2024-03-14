// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "lib/jeu.h"
#include <fstream>

int main()
{
	/*
	std::vector<Joueur*> joueur;
	joueur.push_back(new Joueur(10, 10));
	joueur.push_back(new Joueur(10, 10));
	
	joueur[0]->ajouterBateau(2, 2, true, 4);
	joueur[1]->ajouterBateau(2, 2, true, 4);
	Coordonnee pos = { 2,2 };
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Tirer = " << joueur[1]->tirer(pos, joueur[0]) << std::endl;
		pos.x += 1;
	}
	
	std::cout << joueur[0]->aPerdu() << std::endl;
	
	delete joueur[0];
	delete joueur[1];
	return 0;	
	*/
    std::ifstream myFile("lib/Test.txt", std::ios_base::in);
    Jeu jeu;
    int reponse;
    while ((reponse = jeu.menuStartUp(std::cout, myFile)) == INCORRECT) {}
    if (reponse == QUITTER)
        return 0;
    //Le joueur commence
    do {
        jeu.menuReglage(std::cout, myFile);
        //jeu.menuReglage(std::cout, std::cin);
        jeu.ajouterJoueur();
        jeu.ajouterJoueur();
        jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        //jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(0)); // Joueur 1 place ses bateaux
        jeu.menuInitJoueur(std::cout, myFile, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        //jeu.menuInitJoueur(std::cout, std::cin, jeu.getJoueur(1)); // Joueur 2 place ses bateaux
        
        
        while ((reponse = jeu.menuFin(std::cout, std::cin)) == INCORRECT) {}
        if (reponse == QUITTER)
            return 0;
    } while (true);
    myFile.close();
    //Écrire la base
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
