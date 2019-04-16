#ifndef __BIT__
#define __BIT__

#include "plateau.h"


void afficher_binaire(unsigned long long n);
int testBit_ull(unsigned long long x, int n);

unsigned long long allume_bit(unsigned long long n, int position);
unsigned long long eteint_bit(unsigned long long n, int position);
int trouve_bit(Position pos, int position);

int placer_dame_position(Position *pos, Case c);


#endif