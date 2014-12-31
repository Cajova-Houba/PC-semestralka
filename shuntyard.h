#ifndef _shuntyard_h
#define _shuntyard_h
#include "charToken.h"

/*
Stare, nepouzivat!!
*/
int shuntingYard2(char input[], char postbuff[], int inLen);

/*
Funkce prevede retezcovy vstup na seznam tokenu.
*/
chrTkn *preproc(int vstupLen, char input[]);

/*
Funkce provede ShuntingYard algoritmus nad zadanym tokenovym vstupem a vysledek vrati jako seznam tokenu.
*/
chrTkn *shuntingYard(chrTkn *vstup);
/*
Funkce jednoduchym algoritmem overi spravnost zadane postfixove notace.
Pokud je vse v poradku, vrati 0.
*/
int validateRPN(chrTkn *root);
#endif
