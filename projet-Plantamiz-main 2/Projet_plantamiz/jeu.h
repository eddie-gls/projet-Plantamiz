#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>n
#include <conio.h>
#include <time.h>
#define HAUTEUR 25
#define LARGEUR 45
#include <windows.h>
void Color(int couleurDuTexte,int couleurDeFond); // fonction d'affichage de couleurs
void gotoligcol(int lig, int col); //déplacement du curseur à la position (lig, col)
void afficherCadre(); //affiche la zone du jeu
void afficherMat(char matrice[HAUTEUR][LARGEUR]); // affiche la matrice avec les items générer de manière aléatoire
void deplacecurseur(char touche, int *x, int *y); // déplace le curseur en fonction de la touche presser
void permutation(int grille[HAUTEUR][LARGEUR], int x, int y); // permutation de deux objets

#endif // JEU_H_INCLUDED
