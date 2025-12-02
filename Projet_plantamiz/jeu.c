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
                case 0:
                    Color(14, 0);// Jaune
                    break;
                case 1:
                    Color(12, 0);//  Rouge
                    break;
                case 2:
                    Color(10, 0); //  Vert
                    break;
                case 3:
                    Color(11, 0);
                    break; // Bleu clair
                case 4:
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


void suprimefigure(int LIGNES, int COLONNES) {
    matrice[LIGNES][COLONNES] = ' ';
}

void detectionAlignementHorizontal() {
    for (int i = 1; i < LIGNES; i++){
        int compteur = 1;
        for (int j = 1; j < COLONNES;j++){
            if matrice[i][j]=matrice[i][j+1]{
                compteur ++;
                if (compteur >= 3){
                    for (int k=j-compteur; k < j; k++){ //Si l'alignement atteint 3 ou plus, on appelle la fonction  supprimefigure
                        supprimefigure(matrice[i][k]);
                    }

                }
            else {
                compteur=1
            }

            }

        }

    }
}

void detectionAlignementVertical() {
    for (int j = 1; j < COLONNES; j++){
        int compteur = 1;
        for (int i = 1; i < LIGNES; i++){
            if matrice[i][j]=matrice[i+1][j]{
                compteur ++;
                if (compteur >= 3){
                    for (int k=j-compteur; k < j; k++){
                        supprimefigure(matrice[k][j]);
                    }

                }
            else {
                compteur=1
            }

            }

        }

    }
}
void calibrermat (void afficherMat(char matrice[HAUTEUR][LARGEUR])){
    if ()
}




void permutation(int grille[HAUTEUR][LARGEUR], int x, int y) {
    char touche = getch(); // lit la direction apr�s avoir appuy� sur espace
    int x2 = x, y2 = y;

    // Détermine la case à échanger selon la direction
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

    // �change les deux cases
    int temp = grille[y][x];
    grille[y][x] = grille[y2][x2];
    grille[y2][x2] = temp;
}
typedef struct lieu {
    int x;
    int y;
    struct  lieu* next;
} lieu;

lieu* lieualignement(char grille[HAUTEUR][LARGEUR]){
    lieu* liste= NULL;
    lieu*fin=NULL;
    for (int i=0; i<HAUTEUR; i++){
        for (int j=0;j<LARGEUR; j++){

            if (grille[i][j]== 0) {
                lieu* p= malloc (sizeof(lieu));
                p->x=i;
                p->y=j;
                p->next = NULL;
                if (liste==NULL){
                    liste=p;
                    fin=p;
                }
                else{
                    fin->next =p;
                    fin=p;
                }
            }
        }
    }
    return liste;
}

void sauvegarderprogression(char nom_joueur[], int niveau){
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

void affichervie(int hauteur, int largeur, int vies){
	gotoligcol(1,10);
	color(1,0);
	printf("Vies restantes: %d \n",vies);
	color(7,0);
}

void vieperdu(int *vies){
	if(*vies>0){
		*vies = *vies - 1;
	}
}

int Perdu(vies){
	if(vies=0){
		printf("Vous avez perdu\n");
		return 1;
	}
	else{
		return 0;
	}
}
