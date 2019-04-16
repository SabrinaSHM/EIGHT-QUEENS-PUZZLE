#ifndef __ASCII__
#define __ASCII__

#include "plateau.h"
#include "bit.h"

Position tab_cases_attaquees[64];


int afficher_position(Position pos);

int calculer_cases_attaquees(Position *pos, Case c);

void afficher_tab(int tab[][8]);
void inserer_dans_tab(int tab[][8], Position pos);
void inserer_dans_pos(int tab[][8], Position *pos);
void allume_diago(int tab[][8], Case c);

void initialise_tab_cases_attaquees(Position tab[]);
int est_sans_attaque_mutuelle(Position pos);


#endif