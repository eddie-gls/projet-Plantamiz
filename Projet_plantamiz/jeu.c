#include "jeu.h"

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}



// D�placement du curseur
void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void afficherCadre() {
    int i;

    gotoligcol(0, 0);
    printf("%c", 0xDA);
    for (i = 1; i < LARGEUR - 1; i++){
         printf("%c", 0xC4);
    }
    gotoligcol(0,LARGEUR);
    printf("%c", 0xBF);

    for (i = 1; i < HAUTEUR - 1; i++) {
        gotoligcol(i, 0);
        printf("%c", 0xB3);
        gotoligcol(i, LARGEUR - 1);
        printf("%c", 0xB3);
    }

    gotoligcol(HAUTEUR - 1, 0);
    printf("%c", 0xC0);
    for (i = 1; i < LARGEUR - 1; i++) {
        printf("%c", 0xC4);
    }
    gotoligcol(HAUTEUR,LARGEUR);
    printf("%c", 0xD9);
}
void afficherMat(char matrice[HAUTEUR][LARGEUR]) {
    int i, j;
    char lettres[] = {'S', 'F', 'P', 'O', 'M'};

    srand(time(NULL));

    for (i = 0; i < HAUTEUR; i++) {
        for (j = 0; j < LARGEUR; j++) {
            matrice[i][j] = lettres[rand() % 5];
            switch (matrice[i][j]) {
                case 'S':
                    Color(14, 0);// Jaune
                    break;
                case 'F':
                    Color(12, 0);//  Rouge
                    break;
                case 'P':
                    Color(10, 0); //  Vert
                    break;
                case 'O':
                    Color(11, 0);
                    break; // Bleu clair
                case 'M':
                    Color(4, 0); // Rouge foncé
                    break;
            }


            printf("%c", matrice[i][j]);
        }

    }
}

void deplacecurseur(char touche, int *x, int *y) {
    if (kbhit()) {
        touche = getch();
        if (touche == 's' && *y < HAUTEUR) (*y)++;
        else if (touche == 'z' && *y > 1) (*y)--;
        else if (touche == 'q' && *x > 1) (*x)--;
        else if (touche == 'd' && *x < LARGEUR) (*x)++;
        gotoligcol(*y,*x);
    }
}

int detectionfigure(char grille[HAUTEUR][LARGEUR], int *score) {
    int compteur = 0;
    char temp[HAUTEUR][LARGEUR] = {0};

    /* ==========================
       =  DETECTION HORIZONTALE  =
       ========================== */
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (grille[i][j] != ' ') {

                char c = grille[i][j];

                // ===== RECTANGLE Lxl =====
                int largeur = 1;
                int hauteur = 1;

                // Largeur maximale
                while (j + largeur < LARGEUR && grille[i][j + largeur] == c) {
                    largeur++;
                }

                // Hauteur maximale
                while (i + hauteur < HAUTEUR) {
                    int k;
                    for (k = 0; k < largeur; k++) {
                        if (grille[i + hauteur][j + k] != c) {
                            break;
                        }
                    }
                    if (k < largeur) {
                        break;
                    }
                    hauteur++;
                }

                // Si rectangle >= 2x2
                if (largeur >= 2 && hauteur >= 2) {
                    for (int x = 0; x < hauteur; x++) {
                        for (int y = 0; y < largeur; y++) {
                            temp[i + x][j + y] = 1;
                        }
                    }
                    *score += 2*largeur * hauteur;
                    compteur++;
                }

                // ===== ALIGNEMENT HORIZONTALE =====
                int L = 1;
                int start = j;

                while (start + L < LARGEUR && grille[i][start + L] == c) {
                    L++;
                }

                // Figure H si L >=3
                if (L >= 3 && i - 1 >= 0 && i + 1 < HAUTEUR) {
                    int centre = start + L / 2;
                    if (grille[i - 1][centre] == c && grille[i + 1][centre] == c) {

                        int nb_cases_H = 0;
                        for (int k = 0; k < L; k++) {
                            if (!temp[i][start + k]) {
                                nb_cases_H++;
                            }
                        }
                        if (!temp[i - 1][centre]) {
                            nb_cases_H++;
                        }
                        if (!temp[i + 1][centre]) {
                            nb_cases_H++;
                        }

                        for (int k = 0; k < L; k++) {
                            temp[i][start + k] = 1;
                        }
                        temp[i - 1][centre] = 1;
                        temp[i + 1][centre] = 1;

                        *score += 2 * nb_cases_H;
                        compteur++;
                    }
                }

                // Alignements 3-5
                if (L >= 3 && L < 6) {
                    for (int k = 0; k < L; k++) {
                        temp[i][start + k] = 1;
                    }
                    *score += L;
                    compteur++;
                }

                // Alignements >=6
                else if (L >= 6) {
                    int suppr = 0;
                    for (int x = 0; x < HAUTEUR; x++) {
                        for (int y = 0; y < LARGEUR; y++) {
                            if (grille[x][y] == c) {
                                temp[x][y] = 1;
                                suppr++;
                            }
                        }
                    }
                    *score += suppr;
                    compteur++;
                }

                j += (L - 1);
            }
        }
    }

    /* ==========================
       =  DETECTION VERTICALE    =
       ========================== */
    for (int col = 0; col < LARGEUR; col++) {
        for (int row = 0; row < HAUTEUR; row++) {
            if (grille[row][col] != ' ') {

                char c = grille[row][col];
                int H = 1;
                int start = row;

                while (start + H < HAUTEUR && grille[start + H][col] == c) {
                    H++;
                }

                if (H >= 3 && H < 6) {
                    for (int k = 0; k < H; k++) {
                        temp[start + k][col] = 1;
                    }
                    *score += H;
                    compteur++;
                }
                else if (H >= 6) {
                    int suppr = 0;
                    for (int x = 0; x < HAUTEUR; x++) {
                        for (int y = 0; y < LARGEUR; y++) {
                            if (grille[x][y] == c) {
                                temp[x][y] = 1;
                                suppr++;
                            }
                        }
                    }
                    *score += suppr;
                    compteur++;
                }

                row += (H - 1);
            }
        }
    }

    /* ==========================
       =  SUPPRESSION DES CASES  =
       ========================== */
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (temp[i][j] == 1) {
                grille[i][j] = ' ';
            }
        }
    }

    return compteur;
}




void permutation(char grille[HAUTEUR][LARGEUR], int x, int y) {
    char touche = getch(); // lit la direction apres avoir appuye sur espace
    int x2 = x, y2 = y;

    // Determine la case à echanger selon la direction
    if (touche == 'z' && y > 0)
        y2--;
    else if (touche == 's' && y < HAUTEUR - 1)
        y2++;
    else if (touche == 'q' && x > 0)
        x2--;
    else if (touche == 'd' && x < LARGEUR - 1)
        x2++;
    else
        return; // touche invalide, on sort sans rien faire

    // echange les deux cases
    char temp = grille[y][x];
    grille[y][x] = grille[y2][x2];
    grille[y2][x2] = temp;
}
int gravite(char grille[HAUTEUR][LARGEUR]) {
    int mouvement = 0;

    for (int j = 0; j < LARGEUR; j++) {
        for (int i = HAUTEUR - 1; i > 0; i--) {
            if (grille[i][j] == ' ' && grille[i-1][j] != ' ') {
                grille[i][j] = grille[i-1][j];
                grille[i-1][j] = ' ';
                mouvement = 1;
            }
        }
    }

    return mouvement;
}
void remplir(char grille [HAUTEUR][LARGEUR]){
    char lettres[] = {'S', 'F', 'P', 'O', 'M'};
    // Assurez-vous d'avoir bien initialisé la graine du générateur aléatoire (srand(time(NULL));) au début du programme

    for (int i = 0; i < LARGEUR; i++){
        if (grille[0][i] == ' '){
            char nouveau_caractere;

            do {
                // Génère un caractère aléatoire parmi les 5 disponibles
                nouveau_caractere = lettres[rand() % 5];
            } while (
                // Vérification HORIZONTALE : Le nouveau caractère crée-t-il un alignement de 3 avec [i-1] et [i-2] ?
                (i >= 2 && nouveau_caractere == grille[0][i-1] && nouveau_caractere == grille[0][i-2])
                // OU
                // Vérification VERTICALE : Le nouveau caractère crée-t-il un alignement de 3 avec [1][i] et [2][i] ?
                || (HAUTEUR >= 3 && nouveau_caractere == grille[1][i] && nouveau_caractere == grille[2][i])
            );

            // Place le caractère qui ne crée pas de match
            grille[0][i] = nouveau_caractere;
        }
    }
}
void calibrermat (char matrice[HAUTEUR][LARGEUR]){
    int score_bidon = 0;
    while(detectionfigure(matrice, &score_bidon) > 0){
        // La détectionfigure a marqué les cases à supprimer. La gravité les fait tomber et les ' ' remontent.
        while(gravite(matrice) > 0){} // Appliquer la gravité jusqu'à ce que plus rien ne bouge
        remplir(matrice); // Remplir les cases vides (le haut)
        // La boucle 'while' vérifie si le remplissage a créé de nouvelles figures
    }
}

int sauvegarderprogression(char nom_joueur[], int niveau){
	FILE* pf=fopen("sauvegarde.txt","w");
	if (pf==NULL){
		perror("Impossible de créer le fichier");
		return 1;
	}
	fprintf(pf, "%s\n",nom_joueur);
	fprintf(pf,"%d\n",niveau);

	if (fclose(pf)==0){
		printf("fichier sauvegarder");
	}
	else{
		perror("erreur lors de la sauvegarde du fichier");
	}
	return 1;
}

int chargerprogression(char nom_joueur[],int *niveau){
	FILE* pf=fopen("sauvegarde.txt","r");
	if (pf==NULL){
		perror("Erreur lors de l'ouverture du fichier de sauvegarde");
		return 1;
	}
	printf("Fichier de sauvegarde ouvert \n");
	fscanf(pf,"%s",nom_joueur);
	fscanf(pf,"%d",niveau);
	fclose(pf);
	return 1;

}

void affichervie(int vies){
	gotoligcol(1,10);
	Color(1,0);
	printf("Vies restantes: %d \n",vies);
	Color(7,0);
}

void vieperdu(int *vies){
	if(*vies>0){
		*vies = *vies - 1;
	}
}

int Perdu(int vies){
	if(vies==0){
		printf("Vous avez perdu\n");
		return 1;
	}
	else{
		return 0;
	}
}
int jeu(int niveau, char nom_joueur[]) {
    char matrice[HAUTEUR][LARGEUR];
    int vies = 5;
    int coups_max = 50 + (niveau - 1) * 10;
    int coups_restants = coups_max;
    int score_actuel = 0;
    int score_contrat = 500 + (niveau - 1) * 200;
    int x_curseur = 1, y_curseur = 1;
    char touche;

    srand(time(NULL));

    // 1. Initialisation et Calibration
    afficherCadre();
    afficherMat(matrice);

    gotoligcol(HAUTEUR + 3, 0);
    printf("Calibrage du plateau en cours...");

    // Calibrage qui doit boucler
    calibrermat(matrice);

    score_actuel = 0; // Remise à zéro du score après calibration
    afficherMat(matrice);
    gotoligcol(HAUTEUR + 3, 0); printf("                                 ");


    // 2. Boucle de Jeu
    while (coups_restants > 0 && !Perdu(vies) && score_actuel < score_contrat) {

        // Affichage des informations
        gotoligcol(HAUTEUR + 1, 0);
        Color(7, 0);
        printf("Joueur: %s | Niveau: %d | Objectif: %d | Coups: %d | Score: %d |             ",
               nom_joueur, niveau, score_contrat, coups_restants, score_actuel);

        affichervie(vies); // Signature corrigée

        gotoligcol(y_curseur, x_curseur);

        if (_kbhit()) {
            touche = _getch();
            deplacecurseur(touche, &x_curseur, &y_curseur);

            if (touche == ' ') {

                // 1. Permutation
                // La fonction permutation lit une direction (z,q,s,d) et fait l'échange avec la case cible.
                permutation(matrice, x_curseur - 1, y_curseur - 1);

                afficherMat(matrice);
                coups_restants--;

                // 2. Réactions en chaîne (Détection -> Gravité -> Remplissage)
                int figures_detectees = 0;

                do {
                    figures_detectees = detectionfigure(matrice, &score_actuel);

                    if (figures_detectees > 0) {
                        afficherMat(matrice);

                        // Application de la gravité
                        while(gravite(matrice) > 0) {
                           afficherMat(matrice);
                        }

                        remplir(matrice);
                        afficherMat(matrice);
                    }
                } while (figures_detectees > 0);
            }
        }
    }

    // 3. Fin de Jeu
    gotoligcol(HAUTEUR + 5, 0);
    Color(15, 0);

    if (Perdu(vies)) {
        printf("GAME OVER. Vous avez perdu toutes vos vies. Score final : %d\n", score_actuel);
        sauvegarderprogression(nom_joueur, niveau); // Sauvegarde l'état actuel
        return 0;
    } else if (score_actuel >= score_contrat) {
        printf("VICTOIRE ! Contrat (Score >= %d) rempli ! Passage au niveau %d.\n", score_contrat, niveau + 1);
        sauvegarderprogression(nom_joueur, niveau + 1); // Sauvegarde le niveau suivant
        return 1;
    } else {
        printf("Fin des coups. Contrat (Score >= %d) non rempli. Score final : %d\n", score_contrat, score_actuel);
        vieperdu(&vies);
        sauvegarderprogression(nom_joueur, niveau);
        return 0;
    }
}
