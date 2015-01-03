#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "charToken.h"
#include "shuntyard.h"
#include "compute.h"
#include "zapisovac.h"
#define DBG

/*
 * Vypise dodanou chybu.
 */
void vypisChybu(char *err)
{
	printf("Error: %s\n",err);
}

/*
 * Hlavni funkce programu. Nacita hodnoty z argumentu, vola vykonavaci funkce.
 */
int main(int argc, char *argv[])
{
	/* Deklarace promennych */
	/*kompilator visual studio 2013 nebere deklaraci delky poli vstup,out_name a res z promennych*/
	#define VSTUP_LEN 200
	#define VYST_LEN 50
	#define RES_LEN 401
	int vstup_len = VSTUP_LEN, res_len = RES_LEN, vyst_len = VYST_LEN, i, len = 0; /*len je skutecna delka nacteneho vstupu*/
	char vstup[VSTUP_LEN], out_name[VYST_LEN];  
	char arg3[255], *omez; /*do arg3 se nakopiruje argument obsahujici omezeni, do omez uklada vysledek strtok()*/
	chrTkn *root = NULL;   /*Seznam tokenu pred prevedenim na postfix*/
	chrTkn *postRoot = NULL;  /*Seznam tokenu prevedeny na postfix*/
	double res[RES_LEN][2], x_val = 0.0;  /*pole pro vysledky ve tvaru [x,f(x)]*/
	double omezeni[4] = {-10.0 , 10.0 , -10.0 , 10.0}; /*omezeni ve tvaru x_min,x_max,y_min,y_max*/
	double krok; /*krok pro x*/
	double y_min,y_max;
	
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
    if (argc < 3)
    { 
        /*printf("Chyba: spatny pocet argumentu.\n");*/
		vypisChybu("Some parameters are missing. Use program as shown: graph.exe math+function output.file <x_min:x_max:y_min:y_max>");
		return 1;
    }
    else
    {
        strcpy(vstup, argv[1]);
		strcpy(out_name, argv[2]);
		
		/* Nacteni omezeni */
		if(argc == 4)
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
				/*printf("Chyba: omezeni musi byt zadano ve tvaru x_min:x_max:y_min:y_max.\n");*/
				vypisChybu("Error in parsing last parameter. Limitations must be must be expressed as shown: x_min:x_max:y_min:y_max");
				return 2;
			}
		}
    }
	
	#ifdef DBG
   	printf("Vstup: %s\n",vstup);
	#endif
	/* Zjisteni skutecne delky vstupu */
	len = 0;
	for (i = 0; i < vstup_len; i++)
	{
		if (!(vstup[i] == '\0'))
		{
			len++;
		}
	}
	
	if (len == 0)
	{
		vypisChybu("No input.");
		return 4;
	}
	
	/* Prevedeni retezce na tokeny */
	root = preproc(len,vstup);
	/* Kontrola zda nenastala chyba */
	if (root == NULL)
	{
		/*printf("Chyba: zpracovani vstupu.\n");*/
		vypisChybu("Error when tokenizing input. Please check if math function is typed correctly.");
		return 3;
	}
	
	#ifdef DBG
	printf("Vstup prevedeny na tokeny: ");
	vypis(root);
	#endif
	
	/* Prevedeni na postfix notaci */
	postRoot = shuntingYard(root);
	
	if(postRoot == NULL)
	{
		/*shuntingYard si chyby vypisuje sam*/
		return 6;
	}
	
	#ifdef DBG
	printf("Postfix: ");
	vypis(postRoot);
	#endif
	
	/* Validace postfix notace*/
	if(validateRPN(postRoot) != 0)
	{
		vypisChybu("Error when validating postfix notation. Please check if math function is typed correctly.");
		return 5;
	}
	
	
	/* Vypocet v D=<d_min;d_max> */
	x_val = omezeni[0];
	krok = (omezeni[1]-omezeni[0]) / (res_len-1);
	
	/*Vypocet fcnich hodnot, zjisteni y_min, y_max*/
	for (i = 0; i < res_len; i++)
	{
		res[i][0] = x_val;
		res[i][1] = compute(postRoot, x_val);
		x_val += krok;
		
		/*zjisteni y_min a y_max*/
		if( i == 0 )
		{
			y_min = res[i][1];
			y_max = res[i][1];
		}
		else
		{
			if(y_min > res[i][1])
			{
				y_min = res[i][1];
			}
			
			if(y_max < res[i][1])
			{
				y_max = res[i][1];
			}
		}
	}
	
	#ifdef DBG
	printf("D = <%.3f;%.3f>\nkrok = %.3f\n",omezeni[0],omezeni[1],krok);
	printf("H = <%.3f;%.3f>\n",y_min,y_max);
	
	/* Vypsani vysledku */
	printf("x %6s\n","f(x)");
	for(i =0; i < res_len; i++)
	{
		printf("%.3f %5.3f\n",res[i][0],res[i][1]);
	}
	#endif
	
	/* Zapsani vysledku do souboru */
	zapisDoSouboru(out_name,res,res_len,omezeni);
	
	smaz(root);
	smaz(postRoot);

	return 0;
}
