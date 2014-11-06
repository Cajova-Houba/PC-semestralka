#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charToken.h"
#include "shuntyard.h"
#include "compute.h"

int main(int argc, char *argv[])
{
	int len = 50,i,chyba=0;
	char vstup[len], vystup[len];
	chrTkn *root = NULL;
	chrTkn *postRoot = NULL;
	double res = 0.0;
	
	strcpy(vstup, "(5+(25-(5+(5-2^2)-3*2)+5)-2*5)\0");
	printf("Vstup: %s\n",vstup);
	//strcpy(vstup, "(5+5)\0");
	//strcpy(vstup,argv[1]);
	for (i = 0; i < len; i++)
	{
		vystup[i] = '\0';
	}
	
	/*Prevedeni retezce na tokeny*/
	root = preproc(len,vstup);
	printf("Vstup prevedeny na tokeny: ");
	vypis(root);
	
	/*Prevedeni na postfix notaci*/
	postRoot = shuntingYard(root);
	printf("Postfix: ");
	vypis(postRoot);
	
	/*vypocet*/
	res = compute(postRoot);
	printf("Vysledek: %f\n",res);
	
	free(root);
	free(postRoot);

	return 0;
}
