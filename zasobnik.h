#ifndef ZASOBNIK_H
#define ZASOBNIK_H

/*
 * Funkce vlozi znak na vrchol zasobniku.
 * Pokud dojde k preteceni, fce nastavi flag OFc na 1.
 */
void push(int *sp, char stck[], char znak, int stck_len);

/*
 * Funkce ukaze znak na vrcholu zasobniku. 
 * Pokud dojde k podteceni, fce vrati \0 a nastavi flag UFc na 1.
 */
char pop(int *sp, char stck[]);

/*
 * Funkce ukaze znak na vrcholu zasobniku. 
 * Pokud dojde k podteceni, fce vrati \0 a nastavi flag UFc na 1.
 */
char show(int *sp, char stck[]);


 /*
  * Nasledujici fce maji stejny vyznam jako predchozi, pouze pracuji s 
  * doublovym zasobnikem.
  */
/*
 * Funkce vlozi hodnotu na vrchol zasobniku.
 * Pokud dojde k preteceni, fce nastavi flag OFd na 1.
 */
void pushd(int *sp, double stck[], double cislo, int stck_len);

/*
 * Funkce ukaze znak na vrcholu zasobniku.
 * Pokud dojde k podteceni, fce vrati 0.0 a nastavi flag UFd na 1.
 */
double popd(int *sp, double stck[]);

/*
 * Funkce ukaze znak na vrcholu zasobniku.
 * Pokud dojde k podteceni, fce vrati 0.0 a nastavi flag UFd na 1.
 */
double showd(int *sp, double stck[]);

/*Flagy podteceni zasobniku*/
extern int UFc,UFd;

/*Flagy preteceni zasobniku*/
extern int OFc,OFd;

#endif
