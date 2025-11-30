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
                    Color(4, 0); // Rouge fonc�
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
