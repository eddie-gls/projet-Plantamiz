#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
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
void permutation(char grille[HAUTEUR][LARGEUR], int x, int y); // permutation de deux objets
int detectionfigure(char grille[HAUTEUR][LARGEUR], int *score); //detecte les figures demandé par le programme
int gravite(char grille[HAUTEUR][LARGEUR]); // applique la gravité.
void remplir(char grille [HAUTEUR][LARGEUR]); // rempit toutes les cases vides
void calibrermat (char matrice[HAUTEUR][LARGEUR]); //calibre la matrice au début du jeu
int sauvegarderprogression(char nom_joueur[], int niveau); // sauvegarde la progression du joueur, son nom et son niveau
int chargerprogression(char nom_joueur[],int *niveau); // permet de reprendre son niveau et son nom de joueur
void affichervie(int vies); // affiche les vies du joueur
void vieperdu(int *vies); // enlève une vie au joueur
int Perdu(int vies); // GAME OVER quand le joueur n'a plus de vies
int jeu(int niveau, char nom_joueur[]); // corps général du jeu
void initialiserMat(char matrice[HAUTEUR][LARGEUR]); // Initialise la matrice avec ses items
#endif // JEU_H_INCLUDED
