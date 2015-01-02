#ifndef ZASOBNIK_H
#define ZASOBNIK_H

/*
 * Funkce vlozi znak na vrchol zasobniku.
 */
void push(int *sp, char stck[], char znak);

/*
 * Funkce vybere znak z vrcholu zasobniku.
 */
char pop(int *sp, char stck[]);

/*
 * Funkce ukaze znak na vrcholu zasobniku.
 */
char show(int *sp, char stck[]);


 /*
  * Nasledujici fce maji stejny vyznam jako predchozi, pouze pracuji s 
  * doublovym zasobnikem.
  */
/*
 * Funkce vlozi hodnotu na vrchol zasobniku.
 */
void pushd(int *sp, double stck[], double cislo);

/*
 * Funkce vybere hodnotu z vrcholu zasobniku.
 */
double popd(int *sp, double stck[]);

/*
 * Funkce ukaze hodnotu na vrcholu zasobniku.
 */
double showd(int *sp, double stck[]);

/*Flagy podteceni zasobniku*/
extern int UFc,UFd;

#endif
