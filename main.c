#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "charToken.h"
#include "shuntyard.h"
#include "compute.h"
/*#define DBG*/

int main(int argc, char *argv[])
{
	/* Deklarace promennych */
	int vstup_len = 200, res_len = 401, vyst_len = 50, i, len = 0; /*len je skutecna delka nacteneho vstupu*/
	char vstup[vstup_len], out_name[vyst_len];  
	char arg3[255], *omez; /*do arg3 se nakopiruje argument obsahujici omezeni, do omez uklada vysledek strtok()*/
	chrTkn *root = NULL;   /*Seznam tokenu pred prevedenim na postfix*/
	chrTkn *postRoot = NULL;  /*Seznam tokenu prevedeny na postfix*/
	double res[res_len][2], x_val = 0.0;  /*pole pro vysledky ve tvaru [x,f(x)]*/
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
        printf("Chyba: spatny pocet argumentu.\n");
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
				printf("Chyba: omezeni musi byt zadano ve tvaru x_min:x_max:y_min:y_max.\n");
				return 1;
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
	
	/* Prevedeni retezce na tokeny */
	root = preproc(len,vstup);
	/* Kontrola zda nenastala chyba */
	if (root == NULL)
	{
		printf("Chyba: zpracovani vstupu.\n");
		return 1;
	}
	
	#ifdef DBG
	printf("Vstup prevedeny na tokeny: ");
	vypis(root);
	#endif
	
	/* Prevedeni na postfix notaci */
	postRoot = shuntingYard(root);
	
	#ifdef DBG
	printf("Postfix: ");
	vypis(postRoot);
	#endif
	
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

/*
fname - jmeno vystupnihou souboru
values - pole hodnot fce x=[i,0] f(x)=[i,1]
val_len - delka pole hodnot fce
limits - omezeni definicniho oboru, oboru hodnot [D_min,D_max,H_min,H_max] 
*/
void zapisDoSouboru(char *fname, double values[][2], int val_len, double limits[])
{
	FILE *f_vystup = fopen(fname, "w");
	/*defaultni rozmery stranky jsou 595*842 px (A4)*/
	int a4w=595, a4h=842;
	int i;
	/*pro vypsani hodnot na osu x bude pouzit rozsah <floor(D_min);ceil(D_max)>*/	
	limits[0] = floor(limits[0]);
	limits[1] = ceil(limits[1]);
	float delkax = (limits[1] - limits[0]); /*delka osy x*/
	float delkay = (limits[3] - limits[2]); /*delka osy y*/
	int odsazeniy = 20; /*odsazeni ze spodu*/
	int odsazenix = 40; /*odsazeni z leva*/
	/*zvoleni optimalniho meritka tak, aby se graf vesel na sirku/vysku A4 - odsazeni po stranach*/	
	float meritko = fmin((a4w-2*odsazenix)/(float)delkax,(a4h-2*odsazeniy)/(float)delkay);
	int ok; /*oprava ocasku pri vykreslovani*/
	float krokx,kroky; /*krok popisku os*/
	float delkac; /*delka popiskove carky na ose x,y*/
	int pocx=15,pocy=15; /*pocet hodnot na osach x,y*/
	
	char p[3], lnt[7], mvt[7];
	strcpy(p,"%%");
	strcpy(lnt,"lineto");
	strcpy(mvt,"moveto");
	
	#ifdef DBG
	printf("limits: %.3f %.3f %.3f %.3f\n",limits[0],limits[1],limits[2],limits[3]);
	printf("delkax: %.3f delkay: %.3f\n",delkax,delkay);
	#endif
	
	/*normalizace hodnot*/
	/*for(i = 1; i < val_len; i++)
	{
		values[i][0] -= limits[0]; /*x hodnota - x_min*/
		/*values[i][1] -= limits[2]; /*y hodnota - y_min*/
	/*}*/
	
	fprintf(f_vystup,"%%!PS-Adobe-3.0\n"); /*Hlavicka PostScript*/
	fprintf(f_vystup,"%sCreator: Zdenek Vales\n",p); /*Autor*/
	fprintf(f_vystup,"%sTitle: Vykresleni funkce\n",p);
	fprintf(f_vystup,"%sEndComments\n\n",p); /*Konec hlavicky v prologu*/
	
	/*nastaveni fontu*/
	fprintf(f_vystup,"/Courier findfont \n8 scalefont \nsetfont\n\n");
	
	/*translate a scale slouzi k spravnemu posunuti a naslednemu zvetseni na potrebnou velikost*/
	fprintf(f_vystup,"0.5 setlinewidth \nmatrix currentmatrix \nnewpath \n%d %d translate\n%.3f %.3f scale \n",odsazenix,odsazeniy,meritko,meritko); /*osy*/
	fprintf(f_vystup,"0 0 moveto\n%.3f 0 lineto\n",delkax);/*x osa*/
	fprintf(f_vystup,"%.3f %.3f lineto\n",delkax,delkay);
	fprintf(f_vystup,"0 %.3f lineto \nclosepath \nsetmatrix \nstroke \n\n",delkay);/*uzavreni cesty, dokresleni osy y*/
	
	/*carky na osach*/
	krokx = delkax / pocx;
	kroky = delkay / pocy;
	
	/*carky na ose x - definice*/
	delkac = 5.0;
	fprintf(f_vystup,"/carkax {\ntranslate \n0 0 moveto \n0 %.3f lineto \n",delkac); /*carka ve spod*/
	fprintf(f_vystup,"0 %.3f moveto \n0 %.3f lineto \n} def \n\n",delkay*meritko,delkay*meritko-delkac); /*carka nahore*/
	
	/*carky na ose y - definice*/
	fprintf(f_vystup,"/carkay {\ntranslate \n0 0 moveto \n%3.f 0 lineto \n",delkac); /*carka v levo*/
	fprintf(f_vystup,"%.3f 0 moveto \n%3.f 0 lineto \n} def \n\n",delkax*meritko,delkax*meritko-delkac); /*carka v levo*/
	
	/*carky na ose x - vykresleni*/
	fprintf(f_vystup,"matrix currentmatrix \nnewpath \n%d %d translate \n",odsazenix,odsazeniy);
	for(i = 0; i < pocx; i++)
	{
		fprintf(f_vystup,"%.3f 0 carkax \n",krokx*meritko,kroky*meritko);
	}
	fprintf(f_vystup,"setmatrix \nstroke \n\n");
	
	/*carky na ose y - vykresleni*/
	fprintf(f_vystup,"matrix currentmatrix \nnewpath \n%d %d translate \n",odsazenix,odsazeniy);
	for(i = 0; i < pocy; i++)
	{
		fprintf(f_vystup,"0 %.3f carkay \n",kroky*meritko);
	}
	fprintf(f_vystup,"setmatrix \nstroke \n\n");
	
	/*popisky na osach*/
	fprintf(f_vystup,"/popisx {\ntranslate \n0 0 moveto \ntrue charpath \n} def\n\n/popisy {\ntranslate \n0 0 moveto \ntrue charpath \n} def\n\n");
	
	/*x*/
	fprintf(f_vystup,"matrix currentmatrix \n%d %d translate \n",odsazenix,odsazeniy/2);
	fprintf(f_vystup,"(%.2f) 0 0 popisx\n",limits[0]);
	for(i = 1; i <= pocx; i++)
	{
		fprintf(f_vystup,"(%.2f) %.3f 0 popisx\n",limits[0]+i*krokx,krokx*meritko);
	}
	fprintf(f_vystup,"setmatrix \nstroke\n\n");
	
	/*y*/
	fprintf(f_vystup,"matrix currentmatrix \n%d %d translate \n",odsazenix/3,odsazeniy);
	fprintf(f_vystup,"(%.2f) 0 0 popisy\n",limits[2]);
	for(i = 1; i <= pocy; i++)
	{
		fprintf(f_vystup,"(%.2f) 0 %.3f popisx\n",limits[2]+i*kroky,kroky*meritko);
	}
	fprintf(f_vystup,"setmatrix \nstroke\n\n");
	
	/*graf fce*/
	fprintf(f_vystup,"1 setlinewidth \nmatrix currentmatrix \nnewpath \n"); /*funkce*/
	/*limits[0] a limits[2] predstavuji odsazeni z leva a ze spoda o minimalni hodnoty, jedna se tedy o normalizaci*/
	fprintf(f_vystup,"%d %d translate \n%.3f %.3f scale \n",odsazenix,odsazeniy,meritko,meritko);
	fprintf(f_vystup, "%.3f %.3f moveto\n",(values[0][0]-limits[0]),(values[0][1]-limits[2]));
	ok = 0;
	for(i = 1; i < val_len; i++)
	{
		fprintf(f_vystup, "%.3f %.3f ",(values[i][0]-limits[0]),(values[i][1]-limits[2]));
		/*omezeni oborem hodnot*/
		if (values[i][1] >= limits[2] && values[i][1] <= limits[3])
		{
			/*
			* pokud se z posledni pozice mimo omezeni na soucasnou, ktera se do omezeni vejde provede prikaz lineto
			* vznikne nechteny ocasek 
			*/
			if(ok)
			{
				fprintf(f_vystup, "%s\n",lnt);
			}
			else
			{
				fprintf(f_vystup, "%s\n",mvt);
				ok = 1;
			}
		}
		else
		{
			ok=0;
			fprintf(f_vystup, "%s\n",mvt);
		}
	}
	
	/*fprintf(f_vystup,"closepath\n");*/
	fprintf(f_vystup,"setmatrix \n1 0 0 setrgbcolor \nstroke \nshowpage \n");
	
	fprintf(f_vystup,"%sEOF\n",p); /*Konec souboru*/
	fclose(f_vystup);
}
