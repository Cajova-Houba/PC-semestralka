#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "charToken.h"
#include "shuntyard.h"
#include "compute.h"

int main(int argc, char *argv[])
{
	int vstup_len = 200, res_len = 201, vyst_len = 50, i, len = 0; /*len je skutecna delka nacteneho vstupu*/
	char vstup[vstup_len], out_name[vyst_len];  
	char arg3[255], *omez; /*do arg3 se nakopiruje argument obsahujici omezeni, do omez uklada vysledek strtok()*/
	chrTkn *root = NULL;   /*Seznam tokenu pred prevedenim na postfix*/
	chrTkn *postRoot = NULL;  /*Seznam tokenu prevedeny na postfix*/
	double res[res_len][2], x_val = 0.0;  /*pole pro vysledky ve tvaru [x,f(x)]*/
	double omezeni[4] = {-10.0 , 10.0 , -10.0 , 10.0}; /*omezeni ve tvaru x_min,x_max,y_min,y_max*/
	double krok; /*krok pro x*/
	
	/* Inicializace retezcu */
	for(i = 0; i < vstup_len; i++)
	{
		vstup[i] = '\0';
		if( i < vyst_len)
		{
			out_name[i] = '\0';
		}
	}
	
    /* Nacitni z argumentu */
    if (argc < 2)
    { 
        printf("Chyba: spatny pocet argumentu.\n");
		return 1;
    }
    else
    {
        strcpy(vstup, argv[1]);
		strcpy(out_name, argv[2]);
		
		/* Nacteni omezeni */
		if(argc > 2)
		{
			strcpy(arg3,argv[3]);
			
			i = 0;
			omez = strtok(arg3,":");
			while( omez != NULL)
			{
				omezeni[i] = atof(omez);
				omez = strtok(NULL,":");
				i++;
			}
			
			/* Spatny pocet omezeni */
			if(i != 4)
			{
				printf("Chyba: omezeni musi byt zadano ve tvaru x_min:x_max:y_min:y_max.\n");
				return 1;
			}
		}
    }
   	printf("Vstup: %s\n",vstup);
	/* Zjisteni skutecne delky vstupu */
	len = 0;
	for (i = 0; i < vstup_len; i++)
	{
		if (!(vstup[i] == '\0'))
		{
			len++;
		}
	}
	
	/* Prevedeni retezce na tokeny */
	root = preproc(len,vstup);
	/* Kontrola zda nenastala chyba */
	if (root == NULL)
	{
		printf("Chyba: zpracovani vstupu.\n");
		return 1;
	}
	printf("Vstup prevedeny na tokeny: ");
	vypis(root);
	
	/* Prevedeni na postfix notaci */
	postRoot = shuntingYard(root);
	printf("Postfix: ");
	vypis(postRoot);
	
	/* Vypocet v D=<d_min;d_max> */
	x_val = omezeni[0];
	krok = (omezeni[1]-omezeni[0]) / (res_len-1);
	printf("D = <%.3f,%.3f>\nkrok = %.3f\n",omezeni[0],omezeni[1],krok);
	for (i = 0; i < res_len; i++)
	{
		res[i][0] = x_val;
		res[i][1] = compute(postRoot, x_val);
		x_val += krok;
	}
	
	/* Vypsani vysledku */
	printf("x %6s\n","f(x)");
	for(i =0; i < res_len; i++)
	{
		printf("%.3f %5.3f\n",res[i][0],res[i][1]);
	}
	
	/* Zapsani vysledku do souboru */
	
	smaz(root);
	smaz(postRoot);

	return 0;
}
