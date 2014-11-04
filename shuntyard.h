#ifndef _shuntyard_h
#define _shuntyard_h
#include "charToken.h"

int shuntingYard2(char input[], char postbuff[], int inLen);
chrTkn *preproc(int vstupLen, char input[]);
chrTkn *shuntingYard(chrTkn *vstup);
#endif
