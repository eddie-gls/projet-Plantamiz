#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define HAUTEUR 25
#define LARGEUR 45
#include <windows.h>

// Déplacement du curseur
void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}


void afficherCadre() {
    int i;
    int lignes = 25;
    int colonnes = 45;


    gotoligcol(0, 0);
    printf("%c", 0xDA);
    for (i = 1; i < colonnes - 1; i++) {
        printf("%c", 0xC4);
    }
    printf("%c", 0xBF);

    for (i = 1; i < lignes - 1; i++) {
        gotoligcol(i, 0);
        printf("%c", 0xB3);
        gotoligcol(i, colonnes - 1);
        printf("%c", 0xB3);
    }

    gotoligcol(lignes - 1, 0);
    printf("%c", 0xC0);
    for (i = 1; i < colonnes - 1; i++) {
        printf("%c", 0xC4);
    }
    printf("%c", 0xD9);
}
void afficherMat(char matrice[LIGNES][COLONNES]) {
    int i, j;


    srand(time(NULL));

    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES; j++) {
            int n = rand() % 5; // rand permet de generer une lettre parmi les 5 ....
            switch (n) {
                case 0: matrice[i][j] = 'S'; Color(14, 0); break; // Jaune
                case 1: matrice[i][j] = 'F'; Color(12, 0); break; //  Rouge
                case 2: matrice[i][j] = 'P'; Color(10, 0); break; //  Vert
                case 3: matrice[i][j] = 'O'; Color(11, 0); break; // Bleu clair
                case 4: matrice[i][j] = 'M'; Color(13, 0); break; //  Violet
            }


            printf("%c", matrice[i][j]);
        }
        printf("\n"); // saut de ligne après chaque ligne de matrice
    }

void deplacecurseur(char touche, int *x, int *y) {
    if (kbhit()) {
        touche = getch();
        if (touche == 's' && *y < HAUTEUR){
            gotoligcol(*x,(*y)++);

        }
        else if (touche == 'z' && *y > 1) {
            gotoligcol(*x,(*y)--);
        };
        else if (touche == 'q' && *x > 1) {
            gotoligcol((*x)--,*y);
        };
        else if (touche == 'd' && *x < LARGEUR){
            gotoligcol((*x)++,*y);
        };
    }
}

void afficherregles(){

    printf("utiliser z,q,s,d pour permuter les items et les aligner avant la fin du temps\n");
}

void permumation((int *grille)[COLS],r1,r2,c1,c2){

    int temp;
    temp=grille[r1][c1];
    grille[r1][c1]=grille[r2][c2];
    grille[r2][c2]=temp;
}

int menu(){

    int choix;
    printf("1.Niveau facile\n");
    printf("2.Niveau normal\n");
    printf("3.Niveau difficile\n");
    scanf("%d",&choix);
    return choix;
}

 int main (){
     return 0;
 }
