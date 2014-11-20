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

/*
 * Vycet kodu fci. Fce je v tokenu pokud val € kodyFunkci a jeCislo == 0.
 */
enum kodyFunkci{
    ABS=1,
    EXP,
    LN,
    LOG,
    SIN,
    COS,
    TAN,
    COTAN,
    ASIN,
    ACOS,
    ATAN,
    SINH,
    COSH,
    TANH,
    KRAT='*',
    PLUS='+',
    MINUS='-',
    DELENO='/',
    MOCN='^',
    UMIN='_',
    
};
     

/*
 * Funkce vytvori novy token a vlozi ho na konec seznamu predaneho v r.
 * Pokud je r==null, je vytvoren novy root. Fce vraci ukazatel na root
 * seznamu.
 */
chrTkn *vlozNaKonec(chrTkn *r, int value, int jeCislo);
chrTkn *createToken(int value, int jeCislo);
void vypis(chrTkn *r);
void smaz(chrTkn *r);
void vypisASCII(chrTkn *r);

#endif
