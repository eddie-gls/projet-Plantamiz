#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define HAUTEUR 25
#define LARGEUR 45
#include <windows.h>
void afficherregles();// affiche les regles du jeu
int menu(); // choix du niveau de difficulte
int main (); // permet d'aller dans la fonction menu, afficherregles et permet d'acceder au jeu.
#endif // MAIN_H_INCLUDED
