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
    if (scanf("%d", &choix) != 1) {
        // Vider le buffer si l'utilisateur rentre une lettre
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        choix = 0;
    }

    while (choix < 1 || choix > 3){
        printf("Saisie invalide (1-3) : ");
        if (scanf("%d", &choix) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
    }
    return choix;
}

int main () {
    // Ecran de lancement(initialisation)
    srand(time(NULL));
    char nom_joueur[100];
    int niveau_sauvegarde = 1;
    int choix_niveau = 1;
    printf("Entrer votre pseudo:");
    scanf("%s", &nom_joueur);
    // Charger la progression
    if (chargerprogression(nom_joueur, &niveau_sauvegarde) == 1) {
        printf("Progression chargee pour %s au niveau %d.\n", nom_joueur, niveau_sauvegarde);
        printf("Voulez-vous continuer ? (1:Oui / 0:Non) : ");
        int rep;
        scanf("%d", &rep);
        if(rep == 1) {
            choix_niveau = niveau_sauvegarde;
        }
        else {
            afficherregles();
            choix_niveau = menu();
        }
    }
    else {
        afficherregles();
        printf("Entrez votre nom : ");
        scanf("%s", nom_joueur);
        choix_niveau = menu();
    }
    jeu(choix_niveau, nom_joueur);
    return 0;
}
