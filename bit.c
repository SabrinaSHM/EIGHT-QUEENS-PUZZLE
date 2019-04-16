#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bit.h"


/* Test si le bit de position n de l'entier x de type unsigned long long est 0 ou 1 */
int testBit_ull(unsigned long long x, int n) {
    return (x & (1uLL << n)) ? 1 : 0;
}

/* affiche la representation binaire sur 64 bits de n */
void afficher_binaire(unsigned long long n) {
    int i = 0;

    printf("%llu : ", (unsigned long long)n);
    printf("HEXA %x : ", (unsigned int)n);

    for (i = ((8 * sizeof(unsigned long long))-1); i >= 0; i--) {
        if ((i+1)%8 == 0)
            printf("|");

        testBit_ull(n, i) == 0ull ? printf("0") : printf("1");
    }
    printf("\n");
}

/* Fonction qui allume le bit en position 'position' sur l'entier 'unsigned long long' n
   Renvoie l'entier avec le bit allumé */
unsigned long long allume_bit(unsigned long long n, int position) {
    return ((1uLL << position) | n);
}

/* Fonction qui éteint le bit en position 'position' sur l'entier 'unsigned long long' n
   Renvoie l'entier avec le bit éteint */
unsigned long long eteint_bit(unsigned long long n, int position) {
    return (n & ~(1uLL << position));
}

/* Fonction qui indique si le bit en position 'position' sur 'pos' est allumé ou éteint
   Renvoie 1 si le bit est allumé, 0 sinon */
int trouve_bit(Position pos, int position) {
    return ( (pos & (1uLL << position)) >> position );
}


/* Fonction qui prend en paramètre '*pos' et allume son bit en case 'c'
   Renvoie 1 si le bit a été allumé, 0 s'il l'était déjà */
int placer_dame_position(Position *pos, Case c) {
    assert(NULL != pos);

    if (est_case_occupee(*pos, c))
        return 0;

    *pos = allume_bit(*pos, c);
    return 1;
}