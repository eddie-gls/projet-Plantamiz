#include "main.h"
void afficherregles(){

    printf("Utilisez z,q,s,d pour se deplacer sur la map.\n");
    printf("Permutez deux items en appuyant sur la touche espace + (z,q,s,d) \n");
    printf("Alignez assez d'objet pour avoir le nombre de point suffisant pour accomplir le contrat avant la fin du temps. \n");
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
