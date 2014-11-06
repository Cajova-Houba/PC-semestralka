/*
 * Knihovna funkci, ktera se stara o vypocet matematickych vyrazu
 * v postfixove notaci.
 */

#include <stdlib.h>
#include <math.h>
#include "charToken.h"
#include "zasobnik.h"
#include "compute.h"

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

 
double compute(chrTkn *root)
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
				case '+':	tmpRes = addD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case '-':	tmpRes = subD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case '*':	tmpRes = mulD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case '/':	tmpRes = divD(popd(&sp,stack),popd(&sp,stack));
							break;
							
				case '^':	tmpRes = powD(popd(&sp,stack),popd(&sp,stack));
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
