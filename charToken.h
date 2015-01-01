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
	ACOTAN,
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

/*
 * Funkce vytvori a inicialiuje novy token, ktery vrati jako vysledek.
 */
chrTkn *createToken(int value, int jeCislo);

/*
 * Funkce vypise zadany seznam tokenu na jeden radek.
 */
void vypis(chrTkn *r);

/*
 * Funkce rekurzivne smaze dodany seznam tokenu.
 */
void smaz(chrTkn *r);

/*
 * Funkce vypise zadany seznam tokenu jako ASCII hodnoty.
 */
void vypisASCII(chrTkn *r);

/*
 * Funkce zkopiruje obsah jednoho tokenu do druheho, nekopiruje vsak odkaz na dalsi token. 
 */
void copy(chrTkn *source, chrTkn *dest);

/*
 * Funkce vrati znakovou hodnotu tokenu. Pokud je token ciselny, vrati \0.
 */
char getValc(chrTkn *source);

#endif
