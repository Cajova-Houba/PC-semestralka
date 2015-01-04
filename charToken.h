#ifndef CHARTOKEN_H
#define CHARTOKEN_H

/*
 * Token pro shunting yard algoritmus. Retezec je linearni seznam
 * tokenu, ktere muzou obsahovat bud cislo, nebo znakovy token.
 */
typedef struct charToken{
	double dVal;
	char cVal;
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
chrTkn *vlozNaKonec(chrTkn *r, double dVal, char cVal, int jeCislo);

/*
 * Funkce vlozi realne cislo na konec seznamu tokenu.
 * Nove vytvoreny token vrati.
 */
chrTkn *vlozNaKonecD(chrTkn *r, double dVal);

/*
 * Funkce vlozi znak na konec seznamu tokenu.
 * Nove vytvoreny token vrati.
 */
chrTkn *vlozNaKonecC(chrTkn *r, char cVal);

/*
 * Funkce vytvori a inicialiuje novy token, ktery vrati jako vysledek.
 */
chrTkn *createToken(double dVal, char cVal, int jeCislo);

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
 * Funkce vrati znakovou hodnotu tokenu. Pokud je token ciselny, vrati \0.
 */
char getValc(chrTkn *source);

/*
 * Funkce vrati ciselnou hodnotu v zadanem tokenu. Pokud token obsahuje znak,
 * vrati fce 0.
 */ 
double getVald(chrTkn *source);

#endif
