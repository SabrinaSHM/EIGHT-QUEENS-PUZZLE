#ifndef __GRAPHIQUE___
#define __GRAPHIQUE___

#include <MLV/MLV_all.h>
#include "plateau.h"
#include "bit.h"
#include "ascii.h"

typedef struct {
    int x;
    int y;
    int taille;
} DamierCase;

typedef struct {
    int x;
    int y;
} Clic;

typedef struct {
    int x;
    int y;
    int largeur;
    int hauteur;
} Bouton;


void jeu_graphique(Position *pos);

void creer_fenetre();
void ferme_fenetre();

void afficher_position_graphique(Position pos, DamierCase tab[][8]);
void creer_grille(int taille, DamierCase tab[][8]);
void afficher_grad(DamierCase tab[][8]);

int clic_sur_case(int *ind_i, int *ind_j, DamierCase tab[][8], Clic c);
int jouer_coup(Position *pos, DamierCase tab[][8], Clic c);

void clignote_erreur(DamierCase tab[][8], int i, int j);
void affiche_victoire(int taille_grille);

int verif_boutons(Bouton boutons[], Clic c);


#endif