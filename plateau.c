#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "plateau.h"


int est_case_occupee(Position pos, Case c) {
    if ( (pos & (1uLL << c)) >> c )
        return 1;
    return 0;
}