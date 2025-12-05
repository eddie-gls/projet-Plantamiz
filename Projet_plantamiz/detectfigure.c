#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define HAUTEUR 25
#define LARGEUR 45
int detectionfigure(char grille[HAUTEUR][LARGEUR],int *score){
    int compteur=0;
    char temp[HAUTEUR][LARGEUR]={0};
    // detection de l'alignement horizontal
    for (int i=0; i<HAUTEUR;i++){
        for (int j=0; j<LARGEUR;j++){ // parcours de la grille

            int L=1;
            int temp2=j;
            while(temp2+L<LARGEUR && grille[i][temp2]!= ' ' && grille[i][temp2]==grille[i][temp2+L]){
                L++;

            }
            if (L>=3 && L<6){
                compteur++;
                for(int k=0;k<L;k++ ){
                    temp[i][temp2+k]=1;
                }
                *score +=L;
            }
            j+= (L-1);
        }
    }
    // detection de l'alignement vertical
    for (int l = 0; l < LARGEUR; l++) {
        for (int m = 0; m < HAUTEUR; m++) {
            int H = 1;
            int tempv = m;
            while (tempv + H < HAUTEUR && grille[tempv][l] != ' ' && grille[tempv][l] == grille[tempv + H][l]) {
                H++;
            }
            if (H >= 3 && H < 6) {
                compteur++;
                for (int k = 0; k < H; k++) {
                    temp[tempv + k][l] = 1;
                }
                *score += H;
            }
            m += (H - 1);
        }
    }
    return compteur;
}
