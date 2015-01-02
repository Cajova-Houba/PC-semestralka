#ifndef COMPUTE_H
#define COMPUTE_H
#include "charToken.h"

/*
 * Funkce spocita hodnotu vyrazu zadaneho seznamem tokenu v postfixove notaci.
 * Pokud fce v seznamu tokenu narazi na promennou, nahradi ji hodnotou x_val.
 */ 
double compute(chrTkn *root, double x_val);

#endif
