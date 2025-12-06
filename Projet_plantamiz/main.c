#include "main.h"
#include "jeu.h"

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

    while (choix<1 || choix>3){
        printf("Veuillez saisir un nombre entre 1 et 3\n");
        scanf("%d",&choix);
    }

    return choix;
}

int main () {
    // 1. Démarrage du jeu
    srand(time(NULL));
    afficherregles();

    char nom_joueur[100];
    int niveau_sauvegarde = 1;

    // 2. Charger la progression
    if (chargerprogression(nom_joueur, &niveau_sauvegarde) == 1) {
        // La fonction chargerprogression doit être implémentée dans jeu.c
        printf("Progression chargee pour %s au niveau %d.\n", nom_joueur, niveau_sauvegarde);
    } else {
        printf("Entrez votre nom : ");
        scanf("%s", nom_joueur);
    }

    // 3. Choix du niveau
    int choix_niveau = menu();

    // 4. Lancement de la boucle de jeu
    jeu(choix_niveau, nom_joueur);

    return 0;
}
