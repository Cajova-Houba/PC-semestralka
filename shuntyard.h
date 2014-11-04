#ifndef _shuntyard_h
#define _shuntyard_h
#include "charToken.h"

int shuntingYard(char input[], char postbuff[], int inLen);
chrTkn *preproc(int vstupLen, char input[]);
chrTkn *shuntingYard2(chrTkn *vstup);
#endif
