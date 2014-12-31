/*
 * Knihovna funkci, ktera se stara o vypocet matematickych vyrazu
 * v postfixove notaci.
 * Operatory a fce: viz charToken.h
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <errno.h>
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
	double tmp;
	tmp = a/b;
	
	/*pripadna chyba v rozsahu*/
	if(errno == ERANGE)
	{
		errno = 0;	
		return 0;
	}
	else
	{
		return tmp;
	}
}
 
double powD(double a, double exp)
{
	double tmp;
	tmp = pow(a,exp);
	
	/*pripadna chyba v rozsahu*/
	if(errno == ERANGE)
	{
		errno = 0;
		return 0;
	}
	else
	{
		return tmp;
	} 
}

/* Ostatni fce */
double expD(double a)
{
	double tmp;
	tmp = exp(a);
	
	/*pripadna chyba v rozsahu*/
	if(errno == ERANGE)
	{
		errno = 0;
		return 0;
	}
	else
	{
		return tmp;
	}
}

double lnD(double a)
{
	double tmp;
	tmp = log(a);
	
	/*pripadna chyba v rozsahu*/
	if(errno == ERANGE || errno == EDOM)
	{
		errno = 0;
		return 0;
	}
	else
	{
		return tmp;
	}
}

double logD(double a)
{
	double tmp;
	tmp = log10(a);
	
	/*pripadna chyba v rozsahu*/
	if(errno == ERANGE || errno == EDOM)
	{
		errno = 0;
		return 0;
	}
	else
	{
		return tmp;
	}
}

/* Goniometricke fce*/
double sinD(double a)
{
    return sin(a);
}

double cosD(double a)
{
    return cos(a);
}

double tanD(double a)
{
	return tan(a);
}

double cotanD(double a)
{
	return 1/(tan(a));
}

/* Cyklometricke fce*/
double asinD(double a)
{
    if(a > 1)
	{
		a = 1;
	}
	
	if (a < -1)
	{
		a = -1;
	}
	
	return asin(a);
}

double acosD(double a)
{
    if(a > 1)
	{
		a = 1;
	}
	
	if (a < -1)
	{
		a = -1;
	}
	
	return acos(a);
}

double atanD(double a)
{
	return atan(a);
}

double acotanD(double a)
{
	return (PI/2 - atan(a));
}

/* Hyperbolicke fce*/
double sinhD(double a)
{
	/*sinh(x) = (e^(2x) - 1)/(2*e^x)*/
    return (expD(2*a) - 1)/(2*expD(a));
}

double coshD(double a)
{
	/*cosh(x) = (e^(2x) + 1)/(2*e^x)*/
    return (expD(2*a) + 1)/(2*expD(a));
}

double tanhD(double a)
{
	/*tanh(x) = sinh(x)/cosh(x)*/
	return sinh(a)/cosh(a);
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
							
				case ASIN:		tmpRes = asinD(popd(&sp,stack));
							break;
				
				case ACOS:		tmpRes = acosD(popd(&sp,stack));
							break;
				
				case ATAN:		tmpRes = atanD(popd(&sp,stack));
							break;

				case ACOTAN:	tmpRes = acotanD(popd(&sp,stack));
							break;
							
				case SINH:		tmpRes = sinhD(popd(&sp,stack));
							break;
				
				case COSH:		tmpRes = coshD(popd(&sp,stack));
							break;
				
				case TANH:		tmpRes = tanhD(popd(&sp,stack));
							break;							
							
				case ABS:		tmpRes = fabs(popd(&sp,stack));
							break;
				
				case EXP:		tmpRes = expD(popd(&sp,stack));
							break;
							
				case LN:		tmpRes = lnD(popd(&sp,stack));
							break;
				
				case LOG:		tmpRes = logD(popd(&sp,stack));
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
