#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define HAUTEUR 25
#define LARGEUR 45

void deplacecurseur(char touche, int *x, int *y) {
    if (kbhit()) {
        touche = getch();
        if (touche == 's' && *y < HAUTEUR) (*y)++;
        else if (touche == 'z' && *y > 1) (*y)--;
        else if (touche == 'q' && *x > 1) (*x)--;
        else if (touche == 'd' && *x < LARGEUR) (*x)++;
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
