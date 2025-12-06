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
    // Cadre extérieur pour entourer la matrice de 25x45
    // Le cadre va de 0 à LARGEUR+1 en X et 0 à HAUTEUR+1 en Y
    
    gotoligcol(0, 0);
    printf("%c", 0xDA);
    for (i = 0; i < LARGEUR; i++){ // Correction pour couvrir toute la largeur
         printf("%c", 0xC4);
    }
    printf("%c", 0xBF);

    for (i = 0; i < HAUTEUR; i++) { // Correction pour couvrir toute la hauteur
        gotoligcol(i + 1, 0);
        printf("%c", 0xB3);
        gotoligcol(i + 1, LARGEUR + 1);
        printf("%c", 0xB3);
    }

    gotoligcol(HAUTEUR + 1, 0);
    printf("%c", 0xC0);
    for (i = 0; i < LARGEUR; i++) {
        printf("%c", 0xC4);
    }
    printf("%c", 0xD9);
}
void initialiserMat(char matrice[HAUTEUR][LARGEUR]){
	char lettres[] = {'S', 'F', 'P', 'O', 'M'};
    // srand(time(NULL)); est déplacé dans main()
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            matrice[i][j] = lettres[rand() % 5];
        }
    }
}
void afficherMat(char matrice[HAUTEUR][LARGEUR]) {
    int i, j;
    
    for (i = 0; i < HAUTEUR; i++) {
        for (j = 0; j < LARGEUR; j++) {
            // On décale de +1 car le cadre est en 0
            gotoligcol(i + 1, j + 1);
            
            switch (matrice[i][j]) {
                case 'S': Color(14, 0); break; // Jaune
                case 'F': Color(12, 0); break; // Rouge
                case 'P': Color(10, 0); break; // Vert
                case 'O': Color(11, 0); break; // Bleu clair
                case 'M': Color(4, 0);  break; // Rouge foncé
                default:  Color(0, 0);  break; // Vide
            }
            printf("%c", matrice[i][j]);
        }
    }
    Color(7, 0); // Remettre blanc
}

void deplacecurseur(char touche, int *x, int *y) {

    if (kbhit()) {
        touche = getch();
        if (touche == 's' && *y < HAUTEUR-1) (*y)++;
        else if (touche == 'z' && *y > 1) (*y)--;
        else if (touche == 'q' && *x > 1) (*x)--;
        else if (touche == 'd' && *x < LARGEUR-1) (*x)++;
        gotoligcol(*y,*x);
    }
}

int detectionfigure(char grille[HAUTEUR][LARGEUR], int *score) {
    int compteur = 0;
    char temp[HAUTEUR][LARGEUR] = {0};

    // --- DETECTION HORIZONTALE ---
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (grille[i][j] != ' ') {
                char c = grille[i][j];
                
                // Rectangle
                int largeur = 1, hauteur = 1;
                while (j + largeur < LARGEUR && grille[i][j + largeur] == c) largeur++;
                while (i + hauteur < HAUTEUR) {
                    int k;
                    for (k = 0; k < largeur; k++) if (grille[i + hauteur][j + k] != c) break;
                    if (k < largeur) break;
                    hauteur++;
                }

                if (largeur >= 2 && hauteur >= 2) {
                    for (int x = 0; x < hauteur; x++)
                        for (int y = 0; y < largeur; y++) temp[i + x][j + y] = 1;
                    *score += 2*largeur * hauteur;
                    compteur++;
                }

                // Alignement H
                int L = 1;
                int start = j;
                while (start + L < LARGEUR && grille[i][start + L] == c) L++;

                if (L >= 3) {
                    // Figure H
                    if (i - 1 >= 0 && i + 1 < HAUTEUR) {
                        int centre = start + L / 2;
                        if (grille[i - 1][centre] == c && grille[i + 1][centre] == c) {
                            for (int k = 0; k < L; k++) temp[i][start + k] = 1;
                            temp[i - 1][centre] = 1;
                            temp[i + 1][centre] = 1;
                            *score += 10; // Simplification score H
                            compteur++;
                        }
                    }
                    // Alignement simple
                    for (int k = 0; k < L; k++) temp[i][start + k] = 1;
                    *score += L;
                    compteur++;
                }
                j += (L - 1); // Sauter les cases traitées
            }
        }
    }

    // --- DETECTION VERTICALE ---
    for (int col = 0; col < LARGEUR; col++) {
        for (int row = 0; row < HAUTEUR; row++) {
            if (grille[row][col] != ' ') {
                char c = grille[row][col];
                int H = 1;
                int start = row;

                while (start + H < HAUTEUR && grille[start + H][col] == c) H++;

                if (H >= 3) {
                    for (int k = 0; k < H; k++) temp[start + k][col] = 1;
                    *score += H;
                    compteur++;
                }
                row += (H - 1);
            }
        }
    }

    // SUPPRESSION
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (temp[i][j] == 1) grille[i][j] = ' ';
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

    for (int j = 0; j < LARGEUR; j++){ // Utiliser j pour les colonnes (indices de 0 à 44)
        if (grille[0][j] == ' '){ // Vérifie la case la plus haute
            char nouveau_caractere;
			int tentatives = 0;

            do {
                nouveau_caractere = lettres[rand() % 5];
				tentatives++;
            } while (tentatives < 10 && j >= 2 && nouveau == grille[0][j-1] && nouveau == grille[0][j-2]);

            // Place le caractère
            grille[0][j] = nouveau_caractere;
        }
    }
}

void calibrermat (char matrice[HAUTEUR][LARGEUR]){
    int score_bidon = 0;
    int stable = 0;
    
    // Boucle jusqu'à ce que le plateau soit stable (plus de figures, plus de gravité)
    while(!stable){
        stable = 1;
        
        // 1. Détection et suppression
        if(detectionfigure(matrice, &score_bidon) > 0) {
            stable = 0;
            // 2. Gravité tant que ça bouge
            while(gravite(matrice)); 
            // 3. Remplissage des trous en haut
            remplir(matrice);
            while(gravite(matrice)); // Gravité après remplissage
        }
        
        // Sécurité : Remplir si trous restants (cas initial)
        for(int j=0; j<LARGEUR; j++) {
            if(matrice[HAUTEUR-1][j] == ' ') {
                 remplir(matrice);
                 while(gravite(matrice));
                 stable = 0;
            }
        }
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
    gotoligcol(HAUTEUR + 2, 0); // Affichage sous le tableau
    Color(12,0);
    printf("Vies : ");
    for(int i=0; i<vies; i++) printf("%c ", 3); // Coeurs
    printf("     "); // Efface les anciens coeurs si vies perdues
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


    // 1. Initialisation et Calibration
    afficherCadre();
    initialiserMat(matrice);

    gotoligcol(HAUTEUR + 3, 0);
    printf("Calibrage du plateau en cours...");

    // Calibrage qui doit boucler
    calibrermat(matrice);
	gotoligcol(HAUTEUR + 3, 0);
    printf("            "); // Efface le message

    score_actuel = 0; // Remise à zéro du score après calibration
    afficherMat(matrice);
    


    // 2. Boucle de Jeu
    while (coups_restants > 0 && !Perdu(vies) && score_actuel < score_contrat) {

        // Affichage des informations
        gotoligcol(HAUTEUR + 1, 0);
        Color(7, 0);

        printf("Joueur: %s | Niveau: %d | Objectif: %d | Coups: %d | Score: %d ",nom_joueur, niveau, score_contrat, coups_restants, score_actuel);


        affichervie(vies); // Signature corrigée

        gotoligcol(y_curseur, x_curseur);

        if (_kbhit()) {
            touche = _getch();
           

            if (touche == ' ') {

                // 1. Permutation
                // La fonction permutation lit une direction (z,q,s,d) et fait l'échange avec la case cible.
                permutation(matrice, x_curseur - 1, y_curseur - 1);

                afficherMat(matrice);
                coups_restants--;
				afficherMat(matrice);
                Sleep(200); // Petite pause visuelle

               // Cascade
                int combo;
                do {
                    combo = detectionfigure(matrice, &score_actuel);
                    if (combo > 0) {
                        afficherMat(matrice);
                        Sleep(100); // Animation
                        while(gravite(matrice)) {
                             afficherMat(matrice); // Voir tomber
                        }
                        remplir(matrice);
                        while(gravite(matrice)); // Faire tomber les nouveaux
                        afficherMat(matrice);
                    }
                } while (combo > 0);
                
            } else {
                deplacecurseur(touche, &x_curseur, &y_curseur);
            }
        }
        Sleep(50); // Important pour ne pas surcharger le processeur
    }

    // Fin de partie
    gotoligcol(10, 10);
    if (Perdu(vies)) {
        printf("GAME OVER. Score: %d", score_actuel);
        sauvegarderprogression(nom_joueur, niveau);
        return 0;
    } else if (score_actuel >= score_contrat) {
        printf("NIVEAU REUSSI ! Passage au niveau %d", niveau + 1);
        sauvegarderprogression(nom_joueur, niveau + 1);
        getch();
        return 1;
    } else {
        printf("ECHEC CONTRAT (Coups epuises). Vie perdue.");
        vieperdu(&vies);
        sauvegarderprogression(nom_joueur, niveau);
        getch();
        return 0;
    }
}
