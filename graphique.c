#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#define LARGEUR_FENETRE 1280
#define HAUTEUR_FENETRE 720
#define BACKGROUND MLV_rgba(249, 249, 249, 255)
#define COLOR_CASE_PAIR MLV_rgba(245, 245, 245, 255)
#define COLOR_CASE_IMPAIR MLV_rgba(150, 150, 150, 255)
#define COLOR_BOARD MLV_rgba(50, 50, 50, 255)
#define COLOR_ERROR MLV_rgba(255, 0, 0, 125)
#define BG_VICTORY MLV_rgba(127, 255, 0, 255)


#include "graphique.h"


void jeu_graphique(Position *pos) {
    int taille_grille = HAUTEUR_FENETRE / 1.1 + ((HAUTEUR_FENETRE - (HAUTEUR_FENETRE / 1.1)) / 3);
    int nb_dames = 0;
    DamierCase tab_damier[8][8];
    Clic c;

    char *chaines[] = {"Annuler un coup", "Quitter"};
    Bouton boutons[2];
    int l_text, h_text;

    assert(NULL != pos);


    creer_fenetre();


    MLV_get_size_of_text("Quitter", &l_text, &h_text);
    boutons[1].x = (LARGEUR_FENETRE + taille_grille) / 2 - (l_text / 1.5);
    boutons[1].y = HAUTEUR_FENETRE / 2;
    boutons[1].largeur = l_text * 2;
    boutons[1].hauteur = h_text * 2.5;

    MLV_draw_text_box(
        boutons[1].x, boutons[1].y,
        boutons[1].largeur, boutons[1].hauteur,
        chaines[1],
        0, COLOR_BOARD, COLOR_BOARD, BACKGROUND,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
    );


    creer_grille(taille_grille, tab_damier);
    afficher_position_graphique(*pos, tab_damier);

    while (nb_dames < 8) {
        MLV_wait_mouse( &(c.x), &(c.y) );

        if ( verif_boutons(boutons, c) == 1 ) {
            return;
        }

        if ( jouer_coup(pos, tab_damier, c) ) {
            afficher_position(*pos);
            printf("\n");

            afficher_position_graphique(*pos, tab_damier);
            nb_dames++;
        }
    }
    
    affiche_victoire(taille_grille);
    ferme_fenetre();
}


void creer_fenetre() {
    MLV_create_window("Les huit dames", "Les huit dames", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    MLV_clear_window(BACKGROUND);
    MLV_actualise_window();
}

void ferme_fenetre() {
    MLV_wait_mouse(NULL, NULL);
    MLV_free_window();
}


/* * Fonction qui créée la grille de jeu donnée par la 'taille'
   * Les coordonnées de chaque case de la grille sont gardées
     en mémoire dans le tableau 2 dimensions de type DamierCase */
void creer_grille(int taille, DamierCase tab[][8]) {
    int i, j;
    int taille_case = taille / 8;
    
    assert(taille > 0);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {

            tab[i][j].x = taille_case * j;
            tab[i][j].y = taille_case * i;
            tab[i][j].taille = taille_case;

        }
    }
}


/* Fonction qui affiche la grille de jeu donnée par le tableau 'tab'
   Affiche les dames grâce au paramètre pos */
void afficher_position_graphique(Position pos, DamierCase tab[][8]) {
    int i, j, n;
    int bord;
    MLV_Image *dame = NULL;

    dame = MLV_load_image("dame.png");
    MLV_resize_image_with_proportions(dame, tab[0][0].taille, tab[0][0].taille);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {

            if ( !((i + j) % 2) ) {
                MLV_draw_filled_rectangle(
                    tab[i][j].x, tab[i][j].y,
                    tab[i][j].taille, tab[i][j].taille,
                    COLOR_CASE_PAIR
                );
            }

            else {
                MLV_draw_filled_rectangle(
                    tab[i][j].x, tab[i][j].y,
                    tab[i][j].taille, tab[i][j].taille,
                    COLOR_CASE_IMPAIR
                );
            }

            if ( est_case_occupee(pos, 56 - (i * 8) + j) )
                MLV_draw_image(dame, tab[i][j].x, tab[i][j].y);
        }
    }

    bord = tab[0][0].taille / 2;
    for (n = 0; n < bord; n++) {
        MLV_draw_line(
            tab[0][7].x + tab[0][7].taille + n, 0,
            tab[7][7].x + tab[7][7].taille + n, tab[7][7].y + tab[7][7].taille + bord - 1,
            COLOR_BOARD
        );

        MLV_draw_line(
            0, tab[7][0].y + tab[7][0].taille + n,
            tab[7][7].x + tab[7][7].taille + bord - 1, tab[7][0].y + tab[7][0].taille + n,
            COLOR_BOARD
        );
    }

    afficher_grad(tab);
}

void afficher_grad(DamierCase tab[][8]) {
    int n;
    char *grad_nb[] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    char *grad_lettre[] = {"A", "B", "C", "D", "E", "F", "G", "H"};

    for (n = 0; n < 8; n++) {
        MLV_draw_text(
            tab[7][7].x + tab[0][0].taille + (tab[0][0].taille / 5),
            tab[n][7].y + (tab[0][0].taille / 2.5),
            grad_nb[7 - n], 
            MLV_COLOR_WHITE
        );

        MLV_draw_text(
            tab[n][7].y + (tab[0][0].taille / 2.5),
            tab[7][7].x + tab[0][0].taille + (tab[0][0].taille / 7),
            grad_lettre[n],
            MLV_COLOR_WHITE
        );
    }
    MLV_actualise_window();
}


/* Fonction qui à partir d'un clic, récupère les indices du tableau correspondant à la case sélectionnée
   Renvoie 1 si les coordonnées correspondent bien à une case de la grille, 0 sinon */
int clic_sur_case(int *ind_i, int *ind_j, DamierCase tab[][8], Clic c) {
    int i, j;

    assert(NULL != ind_i);
    assert(NULL != ind_j);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {

            if ( tab[i][j].x <= c.x && c.x < (tab[i][j].x + tab[i][j].taille) ) {
                if ( tab[i][j].y <= c.y && c.y < (tab[i][j].y + tab[i][j].taille) ) {
                    *ind_i = i;
                    *ind_j = j;
                    return 1;
                }
            }

        }
    }
    return 0;
}

/* * Fonction qui place une dame
   * Si une dame peut être placée, le bit correspondant à la case cliquée sera allumé dans '*pos'
   * Renvoie 1 si une dame a été placée, 0 sinon */
int jouer_coup(Position *pos, DamierCase tab[][8], Clic c) {
    int ind_i, ind_j;

    assert(NULL != pos);

    if ( clic_sur_case(&ind_i, &ind_j, tab, c) ) {

        if ( !(placer_dame_position(pos, 56 - (ind_i * 8) + ind_j)) )
            return 0;

        if ( !(est_sans_attaque_mutuelle(*pos)) ) {
            *pos = eteint_bit(*pos, 56 - (ind_i * 8) + ind_j);
            clignote_erreur(tab, ind_i, ind_j);
            return 0;
        }

        return 1;
    }

    return 0;
}

void clignote_erreur(DamierCase tab[][8], int i, int j) {
    int n;

    for (n = 0; n < 4; n++) {
        MLV_draw_filled_rectangle(
            tab[i][j].x, tab[i][j].y,
            tab[i][j].taille, tab[i][j].taille,
            COLOR_ERROR
        );
        MLV_actualise_window();
        MLV_wait_milliseconds(100);

        if ( (i + j) % 2 )
            MLV_draw_filled_rectangle(
                tab[i][j].x, tab[i][j].y,
                tab[i][j].taille, tab[i][j].taille,
                COLOR_CASE_IMPAIR
            );
        else
            MLV_draw_filled_rectangle(
                tab[i][j].x, tab[i][j].y,
                tab[i][j].taille, tab[i][j].taille,
                COLOR_CASE_PAIR
            );
        MLV_actualise_window();
        MLV_wait_milliseconds(100);
    }
}

void affiche_victoire(int taille_grille) {
    int l_text;

    MLV_get_size_of_text("Vous gagnez la partie !", &l_text, NULL);
    MLV_draw_adapted_text_box(
        (taille_grille + LARGEUR_FENETRE) / 2 - (l_text / 2),
        (HAUTEUR_FENETRE / 4),
        "Vous gagnez la partie !",
        13, COLOR_BOARD, COLOR_BOARD,
        BG_VICTORY, MLV_TEXT_CENTER
    );
    MLV_actualise_window();
}

int verif_boutons(Bouton boutons[], Clic c) {
    if ( boutons[1].x < c.x && c.x < (boutons[1].x + boutons[1].largeur) ) {
        if ( boutons[1].y < c.y && c.y < (boutons[1].y + boutons[1].hauteur) )
            return 1;
    }

    return 0;
}