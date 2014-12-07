#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charToken.h"
#include "shuntyard.h"
#include "compute.h"

int main(int argc, char *argv[])
{
	int lenMax = 50, len = lenMax, i, chyba=0, res_len = 201;
	char vstup[len], vystup[len], out_name[len];
	chrTkn *root = NULL;
	chrTkn *postRoot = NULL;
	double res[res_len][2], x_val = 0.0;
	double d_min = -10.0, d_max = 10.0; /*definicni obor*/
	double h_min = -10.0, h_max = 10.0; /*obor hodnot*/
	
	for (i = 0; i < len; i++)
	{
		vystup[i] = '\0';
		vstup[i] = '\0';
		out_name[i] = '\0';
	}
	
	/*strcpy(vstup, "(5+(25-(5+(5-2^2)-3*2)+5)-2*5)\0");*/
	//strcpy(vstup, "(5+5)\0");
    /* Nacitni z argumentu*/
    if (argc < 2)
    { 
        printf("Chyba: spatny pocet argumentu.\n");
		exit(1);
    }
    else
    {
        strcpy(vstup, argv[1]);
		strcpy(out_name, argv[2]);
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
	
	/*Vypocet v D=<d_min;d_max>*/
	x_val = d_min;
	for (i = 0; i < res_len; i++)
	{
		res[i][0] = x_val;
		res[i][1] = compute(postRoot, x_val);
		x_val += 0.1;
	}
	
	/*Vypsani vysledku*/
	printf("x %6s\n","f(x)");
	for(i =0; i < res_len; i++)
	{
		printf("%.1f %5.2f\n",res[i][0],res[i][1]);
	}
	smaz(root);
	smaz(postRoot);

	return 0;
}
