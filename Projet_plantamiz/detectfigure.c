#include <stdio.h>
#include <stdlib.h>

#define HAUTEUR 25
#define LARGEUR 45

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
