#ifndef CHARTOKEN_H
#define CHARTOKEN_H

/*
 * Token pro shunting yard algoritmus. Retezec je linearni seznam
 * tokenu. U jednoznakovych retezcu je tento znak ulozen v kodu asci.
 */
typedef struct charToken{
	int val;
	int jeCislo;
	struct charToken *dalsi;
} chrTkn;

chrTkn *vlozNaKonec(chrTkn *r, int value, int jeCislo);
chrTkn *createToken(int value, int jeCislo);
void vypis(chrTkn *r);
void smaz(chrTkn *r);

#endif
