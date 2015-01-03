#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "charToken.h"

/*
 * Funkce vytvori a inicialiuje novy token, ktery vrati jako vysledek.
 */
chrTkn *createToken(double dVal, char cVal, int jeCislo)
{
	chrTkn *res;
	res = malloc(sizeof(chrTkn));
	res->dalsi = NULL;
	res->dVal = dVal;
	res->cVal = cVal;
	res->jeCislo = jeCislo;
	
	return res;
}

/*
 * Funkce vlozi novy token na konec seznamu.
 * Pokud je zadany pocatek seznamu NULL, vytvori jej.
 * Funkce vraci ukazatel na zacatek seznamu.
 */ 
chrTkn *vlozNaKonec(chrTkn *r, double dVal, char cVal, int jeCislo)
{
	chrTkn *tmp = NULL;
	if(r == NULL)
	{
		r = createToken(dVal, cVal, jeCislo);
		return r;
	}
	
	/* Posunuti na konec seznamu */
	tmp = r;
	while(tmp->dalsi != NULL)
	{
		tmp = tmp->dalsi;
	}
	tmp->dalsi = createToken(dVal, cVal, jeCislo);
	
	return r;
}

/*
 * Funkce vlozi realne cislo na konec seznamu tokenu.
 * Nove vytvoreny token vrati.
 */
chrTkn *vlozNaKonecD(chrTkn *r, double dVal)
{
	return vlozNaKonec(r,dVal,'\0',1);
}

/*
 * Funkce vlozi znak na konec seznamu tokenu.
 * Nove vytvoreny token vrati.
 */
chrTkn *vlozNaKonecC(chrTkn *r, char cVal)
{
	return vlozNaKonec(r,0.0,cVal,0);
}

/*
 * Funkce rekurzivne smaze dodany seznam tokenu.
 */
void smaz(chrTkn *r)
{
	if(r->dalsi != NULL)
	{
		smaz(r->dalsi);
	}
	free(r);
}

/*
 * Funkce vypise zadany seznam tokenu na jeden radek.
 */
void vypis(chrTkn *r)
{
	chrTkn *tmp = NULL;
	if(r == NULL)
	{
		return;
	}
	
	tmp = r;
	while(tmp != NULL)
	{
		if(tmp->jeCislo)
		{
			printf("%.3f",tmp->dVal);
		}
		else
		{
			printf("%c",tmp->cVal);
		}
		tmp = tmp->dalsi;
	}
	printf("\n");
}

/*
 * Funkce vypise zadany seznam tokenu jako ASCII hodnoty.
 */
void vypisASCII(chrTkn *r)
{
	chrTkn *tmp = NULL;
	if(r == NULL)
	{
		return;
	}
	
	tmp = r;
	while(tmp != NULL)
	{
		printf("Znak: %d\n",tmp->cVal);
		tmp = tmp->dalsi;
	}
	printf("\n");
}

/*
 * Funkce vrati znakovou hodnotu tokenu. Pokud je token ciselny, vrati \0.
 */
char getValc(chrTkn *source)
{
	if (source == NULL)
	{
		return '\0';
	}
	
	if(source->jeCislo)
	{
		return '\0';
	}
	
	return (source->cVal);
}

/*
 * Funkce vrati ciselnou hodnotu v zadanem tokenu. Pokud token obsahuje znak,
 * vrati fce 0.
 */ 
double getVald(chrTkn *source)
{
	if (source == NULL)
	{
		return 0;
	}
	
	if(!source->jeCislo)
	{
		return 0;
	}
	
	return source->dVal;
}
