/*
 * Knihovna funkci slouzicich pro praci se zasobnikem. 
 */
#include <stdio.h>
#include "zasobnik.h"

/*podteceni znakoveho zasobniku, podteceni double zasobniku*/
int UFc = 0, UFd = 0;
/*preteceni znakoveho a double zasobniku*/
int OFc = 0, OFd = 0;

/*
 * Funkce vlozi znak na vrchol zasobniku.
 * Pokud dojde k preteceni, fce nastavi flag OFc na 1.
 */
 void push(int *sp, char stck[], char znak, int stck_len)
 {
	OFc = 0;
	if((*sp) == stck_len)
	{
		/*printf("Error: Stack overflow at %c symbol.\n",znak);*/
		OFc = 1;
		return;
	}
	stck[*sp] = znak;
	(*sp)++;
 }
 
/*
 * Funkce vybere znak z vrcholu zasobniku.
 * Pokud dojde k podteceni, fce vrati \0 a nastavi flag UFc na 1.
 */
 char pop(int *sp, char stck[])
 {
	  /*SP ukazuje na prvni volnou pozici, pokud SP == 0, zasobnik je prazdny*/
	  UFc = 0;
	  if(*sp <= 0)
	  {
		UFc = 1;
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
 * Pokud dojde k podteceni, fce vrati \0 a nastavi flag UFc na 1.
 */
 char show(int *sp, char stck[])
 {
	   UFc = 0;
	   if(*sp <=0 )
	   {
			UFc = 1;
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
 * Funkce vlozi hodnotu na vrchol zasobniku.
 * Pokud dojde k preteceni, fce nastavi flag OFd na 1.
 */
 void pushd(int *sp, double stck[], double cislo, int stck_len)
 {
	OFd = 0;
	if((*sp) == stck_len)
	{
		/*printf("Error: Stack overflow at %.3f value.\n",cislo);*/
		OFd = 1;
		return;
	}
	stck[*sp] = cislo;
	(*sp)++;
 }
 
/*
 * Funkce vybere znak z vrcholu zasobniku.
 * Pokud dojde k podteceni, fce vrati 0.0 a nastavi flag UFd na 1.
 */
 double popd(int *sp, double stck[])
 {
	  /*SP ukazuje na prvni volnou pozici, pokud SP == 0, zasobnik je prazdny*/
	  UFd = 0;
	  if(*sp <= 0)
	  {
		  UFd = 1;
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
 * Pokud dojde k podteceni, fce vrati 0.0 a nastavi flag UFd na 1.
 */
 double showd(int *sp, double stck[])
 {
	   UFd = 0;
	   if(*sp <=0 )
	   {
		   UFd = 0;
		   return 0.0;
	   }
	   else
	   {
		   return stck[*sp-1];
	   }
 }
