#include <stdio.h>
#include <math.h>
#include <string.h>
#include "zapisovac.h"
/*#define DBG*/

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
	int fVyska = 6; /*vyska fontu vychazi priblizne na 6 bodu*/
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
	/*pocet hodnot na osach x,y. Vyska fontu je 6 bodu, pokud by se na vysku hodnoty nevesly, bude jich zobrazeno mene*/
	int pocx=15,pocy=(int)fmin(15,floor(delkay*meritko / fVyska)); 
	
	char p[3], lnt[7], mvt[7];
	strcpy(p,"%%");
	strcpy(lnt,"lineto");
	strcpy(mvt,"moveto");
	
	#ifdef DBG
	printf("limits: %.3f %.3f %.3f %.3f\n",limits[0],limits[1],limits[2],limits[3]);
	printf("delkax: %.3f delkay: %.3f\n",delkax,delkay);
	#endif
	
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
	fprintf(f_vystup,"/carkax {\nnewpath \n0 0 0 setrgbcolor \ntranslate \n0 0 moveto \n0 %.3f lineto \n",delkac); /*carka ve spod*/
	fprintf(f_vystup,"0 %.3f moveto \n0 %.3f lineto \nstroke \n",delkay*meritko,delkay*meritko-delkac); /*carka nahore*/
	/*cara uprostred, ma jinou barvu nez ostatni cary na osach a osy prekryva, osetreno podminkou*/
	fprintf(f_vystup,"1 eq {newpath 0.5 0.5 0.5 setrgbcolor 0 %.3f moveto 0 %.3f lineto stroke } if\n} def \n\n",delkac,delkay*meritko-delkac);
	
	/*carky na ose y - definice*/
	fprintf(f_vystup,"/carkay {\nnewpath \n0 0 0 setrgbcolor \ntranslate \n0 0 moveto \n%3.f 0 lineto \n",delkac); /*carka v levo*/
	fprintf(f_vystup,"%.3f 0 moveto \n%3.f 0 lineto \nstroke \n",delkax*meritko,delkax*meritko-delkac); /*carka v levo*/
	/*cara uprostred, ma jinou barvu nez ostatni cary na osach a osy prekryva, osetreno podminkou*/
	fprintf(f_vystup,"1 eq {newpath 0.5 0.5 0.5 setrgbcolor %.3f 0 moveto %.3f 0 lineto stroke} if\n} def \n\n",delkac,delkax*meritko-delkac);
	
	/*carky na ose x - vykresleni*/
	fprintf(f_vystup,"matrix currentmatrix \n%d %d translate \n",odsazenix,odsazeniy);
	for(i = 0; i < pocx; i++)
	{
		fprintf(f_vystup,"%d %.3f 0 carkax \n",(i<pocx-1),krokx*meritko);
	}
	fprintf(f_vystup,"setmatrix \n\n");
	
	/*carky na ose y - vykresleni*/
	fprintf(f_vystup,"matrix currentmatrix \n%d %d translate \n",odsazenix,odsazeniy);
	for(i = 0; i < pocy; i++)
	{
		fprintf(f_vystup,"%d 0 %.3f carkay \n",(i<pocy-1),kroky*meritko);
	}
	fprintf(f_vystup,"setmatrix \n0 0 0 setrgbcolor \n\n\n");
	
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
	fprintf(f_vystup,"matrix currentmatrix \n%d %d translate \n",odsazenix/4,odsazeniy-fVyska/2);
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
	
	fprintf(f_vystup,"setmatrix \n1 0 0 setrgbcolor \nstroke \nshowpage \n");
	
	fprintf(f_vystup,"%sEOF\n",p); /*Konec souboru*/
	fclose(f_vystup);
}