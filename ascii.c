#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ascii.h"


int afficher_position(Position pos) {
    int i, j;

    for (i = 7; i >= 0; i--) {
        for (j = 0; j < 8; j++) {
            if (est_case_occupee(pos, (8 * i) + j))
                printf("+ ");
            else
                printf(". ");
        }
        printf("\n");
    }

    return 1;
}


void afficher_tab(int tab[][8]) {
    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            printf("%d ", tab[i][j]);
        printf("\n");
    }
}

/* Fonction qui calcule les positions attaquées par une dame en case 'c'
   Allume les bits de '*pos' sur les positions attaquées
   Renvoie 1 si les bits sont allumés, 0 sinon */
int calculer_cases_attaquees(Position *pos, Case c) {
    int colonne;
    int ligne, max_ligne;
    int tab[8][8];

    assert(NULL != pos);

    if (c < 0 || c > 63)
        return 0;

    colonne = c % 8;
    for (; colonne < 64; colonne += 8) {
        if (colonne != c)
            *pos = allume_bit(*pos, colonne);
    }

    ligne = (c / 8) * 8;
    for (max_ligne = ligne + 8; ligne < max_ligne; ligne += 1) {
        if (ligne != c)
            *pos = allume_bit(*pos, ligne);
    }

    inserer_dans_tab(tab, *pos);
    allume_diago(tab, c);
    inserer_dans_pos(tab, pos);

    return 1;
}

/* Fonction qui copie les bits de 'pos' dans un tableau 2 dimensions */
void inserer_dans_tab(int tab[][8], Position pos) {
    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            tab[i][j] = trouve_bit(pos, (8 * (7 - i)) + j);
    }
}

/* Fonction qui copie les bits du tableau 2 dimensions dans 'pos' */
void inserer_dans_pos(int tab[][8], Position *pos) {
    int i, j;

    assert(NULL != pos);

    *pos = 0;
    for (i = 0; i < 8; i++) {
        for (j = 7; j >= 0; j--) {

            *pos = (*pos | tab[i][j]);
            if ( !(i == 7 && j == 0) )
                *pos = *pos << 1;
        }
    }
}

void allume_diago(int tab[][8], Case c) {
    int i, j;
    int x, y, fin = 0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ( ((8 * i) + j) == c ) {
                x = 7 - i;
                y = j;
                fin = 1;
                break;
            }
        }
        if (fin)
            break;
    }

    /* diagonale inférieure gauche */
    for (i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--)
        tab[i][j] = 1;
    /* diagonale inférieur droite */
    for (i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++)
        tab[i][j] = 1;

    /* diagonale supérieure gauche */
    for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
        tab[i][j] = 1;
    /* diagonale supérieure droite */
    for (i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++)
        tab[i][j] = 1;
}


void initialise_tab_cases_attaquees(Position tab[]) {
    int i;
    Position pos = 0;

    for (i = 0; i < 64; i++) {
        calculer_cases_attaquees(&pos, i);
        tab[i] = pos;
        pos = 0;
    }
}

int est_sans_attaque_mutuelle(Position pos) {
    Position attaques = 0, tmp = pos;
    int n = 0;

    for (; tmp != 0; tmp = (tmp >> 1), n += 1) {
        if ( (1uLL << n) & pos )
            attaques = (attaques | tab_cases_attaquees[n]);
    }
    
    if ( attaques & pos )
        return 0;
    return 1;
}