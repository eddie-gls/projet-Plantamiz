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
 int main (){
     return 0;
 }
