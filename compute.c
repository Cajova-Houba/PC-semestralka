/*
 * Knihovna funkci, ktera se stara o vypocet matematickych vyrazu
 * v postfixove notaci.
 * Operatory a fce: viz charToken.h
 */

#include <stdlib.h>
#include <math.h>
#include "charToken.h"
#include "zasobnik.h"
#include "compute.h"

#define PI 3.14159265

/* Standardni operatory a fce*/
double addD(double a, double b)
{
	return a+b;
}

double subD(double a, double b)
{
	return a-b;
}

double mulD(double a, double b)
{
	return a*b;
}

double divD(double a, double b)
{
	return a/b;
}

double powD(double a, double exp)
{
	return pow(a,exp); 
}


/* Goniometricke fce*/
double sinD(double a)
{
    return sin(a*PI/180);
}

double cosD(double a)
{
    return cos(a*PI/180);
}

double tanD(double a)
{
	return tan(a*PI/180);
}

double cotanD(double a)
{
	return 1/(tan(a*PI/180));
}
 
double compute(chrTkn *root, double x_val)
{
	chrTkn *tmp = NULL;
	/*vysledek prave provedene operace*/
	double tmpRes = 0;
	int spLen = 255, sp = 0, i;
	double stack[spLen];
	char znak = '\0';
	tmp = root;
	
	/*inicializace zasobniku*/
	for (i = 0; i < spLen; i++)
	{
		stack[i] = 0.0;
	}
	
	
	while(tmp != NULL)
	{
		if(tmp->jeCislo)
		{
			/*vlozeni cisla na zasobnik*/
			pushd(&sp,stack,(double)tmp->val);
		}
		else
		{
			znak = tmp->val;
			/*provedeni operace*/
			switch(znak)
			{
                case 'x':   tmpRes = x_val;
                            break;
                                   
				case PLUS:		tmpRes = addD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case MINUS:		tmpRes = subD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case KRAT:		tmpRes = mulD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case DELENO:	tmpRes = divD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case MOCN:		tmpRes = powD(popd(&sp,stack),popd(&sp,stack));
							break;
				
				case UMIN:		tmpRes = (-1)*popd(&sp,stack);
                            break;
							
                case SIN:		tmpRes = sinD(popd(&sp,stack));
							break;
				
				case COS:		tmpRes = cosD(popd(&sp,stack));
							break;
				
				case TAN:		tmpRes = tanD(popd(&sp,stack));
							break;

				case COTAN:		tmpRes = cotanD(popd(&sp,stack));
							break;							
			}
			
			
			/*vlozeni vysledku oprace na zasobnik*/
			pushd(&sp,stack,tmpRes);
		}
		
		tmp = tmp->dalsi;
	}
	
	/*v zasobniku by mel zbyt jediny prvek a to je vysledek*/
	return popd(&sp,stack);
}
