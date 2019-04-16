#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "bit.h"
#include "ascii.h"
#include "graphique.h"
#include "plateau.h"


int main(int argc, char *argv[]) {
    Position pos = 0;

    initialise_tab_cases_attaquees(tab_cases_attaquees);
    jeu_graphique(&pos);

    return 0;
}