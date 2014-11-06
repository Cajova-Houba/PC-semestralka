/*
 * Knihovna funkci slouzicich pro praci se zasobnikem. 
 */

#include "zasobnik.h"

/*
 * Funkce vlozi znak na vrchol zasobniku.
 */
 void push(int *sp, char stck[], char znak)
 {
	 stck[*sp] = znak;
	 (*sp)++;
 }
 
/*
 * Funkce vybere znak z vrcholu zasobniku.
 */
 char pop(int *sp, char stck[])
 {
	  /*SP ukazuje na prvni volnou pozici, pokud SP == 0, zasobnik je prazdny*/
	  if(*sp <= 0)
	  {
		  return '\00';
	  }
	  else
	  {
		  (*sp)--;
		  return stck[*sp];
	  }
 }
  
/*
 * Funkce ukaze znak na vrcholu zasobniku.
 */
 char show(int *sp, char stck[])
 {
	   if(*sp <=0 )
	   {
		   return '\00';
	   }
	   else
	   {
		   return stck[*sp-1];
	   }
 }
 
 /*
  * Nasledujici fce maji stejny vyznam jako predchozi, pouze pracuji s 
  * doublovym zasobnikem.
  */
/*
 * Funkce vlozi znak na vrchol zasobniku.
 */
 void pushd(int *sp, double stck[], double cislo)
 {
	 stck[*sp] = cislo;
	 (*sp)++;
 }
 
/*
 * Funkce vybere znak z vrcholu zasobniku.
 */
 double popd(int *sp, double stck[])
 {
	  /*SP ukazuje na prvni volnou pozici, pokud SP == 0, zasobnik je prazdny*/
	  if(*sp <= 0)
	  {
		  return 0.0;
	  }
	  else
	  {
		  (*sp)--;
		  return stck[*sp];
	  }
 }
  
/*
 * Funkce ukaze znak na vrcholu zasobniku.
 */
 double showd(int *sp, double stck[])
 {
	   if(*sp <=0 )
	   {
		   return 0.0;
	   }
	   else
	   {
		   return stck[*sp-1];
	   }
 }
