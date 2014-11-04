#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "charToken.h"

chrTkn *createToken(int value, int jeCislo)
{
	chrTkn *res;
	res = malloc(sizeof(chrTkn));
	res->dalsi = NULL;
	res->val = value;
	res->jeCislo = jeCislo;
	
	return res;
}

/*
 * Funkce vlozi novy token na konec seznamu.
 * Pokud je zadany pocatek seznamu NULL, vytvori jej.
 * Funkce vraci ukazatel na zacatek seznamu.
 */ 
chrTkn *vlozNaKonec(chrTkn *r, int value, int jeCislo)
{
	chrTkn *tmp = NULL;
	if(r == NULL)
	{
		r = createToken(value, jeCislo);
		return r;
	}
	
	/* Posunuti na konec seznamu */
	tmp = r;
	while(tmp->dalsi != NULL)
	{
		tmp = tmp->dalsi;
	}
	tmp->dalsi = createToken(value,jeCislo);
	
	return r;
}

void smaz(chrTkn *r)
{
	if(r->dalsi != NULL)
	{
		smaz(r->dalsi);
	}
	free(r);
}

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
			printf("%d",tmp->val);
		}
		else
		{
			printf("%c",(char)tmp->val);
		}
		tmp = tmp->dalsi;
	}
	printf("\n");
}

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
		printf("Znak: %i\n",tmp->val);
		tmp = tmp->dalsi;
	}
	printf("\n");
}

/*
 * Funkce zkopiruje obsah jednoho tokenu do druheho, nekopiruje vsak odkaz na dalsi token. 
 */
void copy(chrTkn *source, chrTkn *dest)
{
	if ((source == NULL)  || (dest == NULL))
	{
		return;
	}
	
	dest->val = source->val;
	dest->jeCislo = source->jeCislo;
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
	
	return (char)(source->val);
}

/*
 * Funkce vrati ciselnou hodnotu v zadanem tokenu. Pokud token obsahuje znak,
 * vrati fce 0.
 */ 
int getVali(chrTkn *source)
{
	if (source == NULL)
	{
		return 0;
	}
	
	if(!source->jeCislo)
	{
		return 0;
	}
	
	return source->val;
}
