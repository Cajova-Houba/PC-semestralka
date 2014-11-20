#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charToken.h"
#include "shuntyard.h"
#include "compute.h"

int main(int argc, char *argv[])
{
	int lenMax = 50, len = lenMax,i,chyba=0;
	char vstup[len], vystup[len];
	chrTkn *root = NULL;
	chrTkn *postRoot = NULL;
	double res = 0.0, x_val = 0.0;
	
	for (i = 0; i < len; i++)
	{
		vystup[i] = '\0';
		vstup[i] = '\0';
	}
	
	/*strcpy(vstup, "(5+(25-(5+(5-2^2)-3*2)+5)-2*5)\0");*/
	//strcpy(vstup, "(5+5)\0");
    /* Nacitni z argumentu*/
    if (argc > 1)
    { 
        strcpy(vstup,argv[1]);
        if (argc > 2)
        {
            x_val = atof(argv[2]);
        }
    }
    else
    {
        strcpy(vstup, "-2*4\0");
    }
   	printf("Vstup: %s\n",vstup);
	/*zjisteni delky vstupu*/
	len = 0;
	for (i = 0; i < lenMax; i++)
	{
		if (!(vstup[i] == '\0'))
		{
			len++;
		}
	}
	
	
	
	
	/*Prevedeni retezce na tokeny*/
	root = preproc(len,vstup);
	/*Kontrola zda nenastala chyba*/
	if (root == NULL)
	{
		printf("Chyba: zpracovani vstupu.\n");
		return 1;
	}
	printf("Vstup prevedeny na tokeny: ");
	vypis(root);
	
	/*Prevedeni na postfix notaci*/
	postRoot = shuntingYard(root);
	printf("Postfix: ");
	vypis(postRoot);
	
	/*vypocet*/
	res = compute(postRoot,x_val);
	printf("Vysledek: %f\n",res);
	
	smaz(root);
	smaz(postRoot);

	return 0;
}
