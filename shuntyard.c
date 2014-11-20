/*
 * Knihovna obsahuje implementaci shunting yard algoritmu, ktery slouzi 
 * k prevodu z infixove notace do postfix notace.
 */
#include <string.h>
#include <stdio.h>
#include "shuntyard.h"
#include "charToken.h"
#include "zasobnik.h"

/*
 * Funkce zjisti, zda je zadany znak matematicky operator.
 */
 int isOperator(char op)
 {
	/*Operator je funkce*/
	if(op >=ABS && op<=TANH)
	{
		return 1;
	}
	
	 switch(op)
	 {
		 case PLUS:
		 case MINUS:
		 case KRAT:
		 case DELENO:
		 case UMIN:
		 case MOCN: return 1;
				   break;
		 
		 default: return 0;
	 }
 }
 
/*
 * Funkce vrati prioritu matematickeho operatoru.
 * Pokud bude zadan jiny znak nez operator, fce vrati 0.
 */
 int getPriority(char op)
 {
	 if(!isOperator(op))
	 {
		 return 0; 
	 }
	 
	 /*Operator je fce*/
	 if(op >= ABS && op <= TANH)
	 {
		return 5;
	 }
	 
	 switch (op)
	 {
		 case PLUS:
		 case MINUS: return 1;
		 case KRAT:
		 case DELENO: return 2;
		 case UMIN: return 3;
		 case MOCN: return 4; 
			 
		 default: return 0;	 
	 }
 }
 
 /*
  * Funkce vraci 1 pokud je operator asociativni zleva.
  */
 int asocZleva(char op)
 {
	 switch (op)
	 {
		 case MOCN: return 0;
		 
		 default: return 1;
			 
	 } 
 }
 
 /*
  * Funkce precte dodany seznam tokenu a vrati novy seznam, kde tokeny
  * tvori matematicky vyraz v postfixove notaci.
  * Pokud fce vrati NULL, doslo k chybe.
  */
 chrTkn *shuntingYard(chrTkn *vstup)
 {
	char stack[255];
	chrTkn *tmp = NULL;
	chrTkn *vystup = NULL;
	/*Prave zpracovavany znak, operator1, operator2*/
	char znak = '\0', op1 = '\0', op2='\0';
	/*stack pointer*/
	int sp=0,i;
	
	if (vstup == NULL)
	{
		printf("Chyba: NULL na vstupu.\n");
		return NULL;
	}
	
	/*Inicializace zasobniku*/
	for(i=0;i<255;i++)
	{
		stack[i] = '\0';
	}
	
	tmp = vstup;
	/*Shunting yard*/
	while(tmp != NULL)
	{
		if(tmp->jeCislo)
		{
			/*Cislo - dej na vystup*/
			vystup = vlozNaKonec(vystup,tmp->val,1);
			/*printf("Nalezeno cislo %i, vlozeno na vystup\n",tmp->val);*/
		}
		else
		{
			/*Znak*/
			znak = getValc(tmp);
			
			
			/*Promenna - dej na vystup*/
			if(znak == 'x')
			{
				vystup = vlozNaKonec(vystup,znak,0);
			}
			
			/*Operator*/
			if(isOperator(znak))
			{
				  op1 = znak;
				  /*printf("Nalezen operator: %c. Zasobnik: %s\n",op1,stack);*/
				  /*
				  * Dokud je na zasobniku operator, kontroluj prioritu a pripadne presun do vystupni fronty.
				  */
				  while(isOperator(show(&sp,stack)))
				  {
					  op2 = show(&sp,stack);
					  /*printf("Zasobnik: %s\n Operator: %c",stack,op2);*/
					  
					  /*Asociace zleva*/
					  if(asocZleva(op1))
					  {
						  /*
						  * vkladej operatory ze zasobniku na vystup dokud bude jejich priorita vetsi nebo rovna 
						  * priorite prave proverovaneho operatoru. Pak dej proverovany operator na zasobnik
						  */
						  if(getPriority(op1) <= getPriority(op2)) 
						  {
							  /*printf("Davam operator %c do vystupu na pozici %d.\n",op2,cur);*/
							  vystup = vlozNaKonec(vystup,pop(&sp,stack),0);
						  }
						  else
						  {
							  break;
						  }
					  }
					  else
					  {
						  /*
						  * Stejne jako u asociace zleva, pouze op1 < op2
						  */
						  if(getPriority(op1) < getPriority(op2)) 
						  {
							  /*printf("Davam operator %c do vystupu na pozici %d.\n",op2,cur);*/
							  vystup = vlozNaKonec(vystup,pop(&sp,stack),0);
						  }
						  else
						  {
							  break;
						  }
					  }
				  }/*end while*/
				  /*Vlozeni operatoru na zasobnik*/
				  /*printf("Vkladam operator %c do zasobniku na pozici %d\n",op1,sp);*/
				  push(&sp,stack,op1);
			}/*end if operator*/
			
		   /*
		    * Zavorky.
		    */
		    if(znak == '(')
		    {
				/*printf("Nalezena leva zavorka. Vkladam na zasobnik na pozici %d.\n",sp);*/
				push(&sp,stack,'(');
			}
			if(znak == ')')
			{
				/*
				 * Dokud na vrcholu zasobniku neni leva zavorka, davej znaky na vystup.
				 * Levou zavorku na vystup nedavej, pouze vyjmi ze  zasobniku.
				 */
				 while(show(&sp,stack) != '(')
				 {
					 /*printf("Vkladam znak %c do vystupu na pozici %d.\n",show(&sp,stack),cur);*/
					 vystup = vlozNaKonec(vystup,pop(&sp,stack),0);
					 /*postbuff[cur++] = pop(&sp,stack);*/
					 
					 /*Neuzavreny vyraz*/
					 if(sp == 0)
					 {
						 printf("Chyba: Neuzavreny vyraz.\n");
						 return NULL;
					 }
				 }
				 /*vyjmuti leve zavorky ze zasobniku*/
				 pop(&sp,stack);
			}
		}
		
		tmp = tmp->dalsi;
	}
	/*Zpracovany vsechny tokeny na vstupu, zbyva vyprazdnit zasobnik.*/
	while(sp)
    {
		/*printf("%d : %s\n",sp,stack);*/
		if(show(&sp,stack) == '(')
		{
			printf("Chyba: Neuzavreny vyraz.\n");
			return NULL;
		}
        vystup = vlozNaKonec(vystup,pop(&sp,stack),0);
    }
	
	return vystup; 
 }

/*
 * Funkce hleda v zadanem retezci, od zadane pozice nazev jedne z funkci, jejiz kod pak vrati.
 * Funkce predpoklada, ze zadany retezec konci '\0'. Vzhledem k tomu, ze hledani probiha v celem zadanem retezci
 * je nutne zadat pouze tu cast retezce, kde se ma nazev fce nachazet.
 * Pokud nastane chyba, funkce vrati 0. 
 */
int najdiFci(char *text)
{	
	if(strstr(text,"abs\0"))
	{
		return ABS;
	}
	else if(strstr(text,"exp\0"))
	{
		return EXP;
	}
	else if(strstr(text,"ln\0"))
	{
		return LN;
	}
	else if(strstr(text,"log\0"))
	{
		return LOG;
	}
	else if(strstr(text,"sin\0"))
	{
		return SIN;
	}
	else if(strstr(text,"cos\0"))
	{
		return COS;
	}
	else if(strstr(text,"tan\0"))
	{
		return TAN;
	}
	else if(strstr(text,"cotan\0"))
	{
		return COTAN;
	}
	else if(strstr(text,"asin\0"))
	{
		return ASIN;
	}
	else if(strstr(text,"acos\0"))
	{
		return ACOS;
	}
	else if(strstr(text,"atan\0"))
	{
		return ATAN;
	}
	else if(strstr(text,"sinh\0"))
	{
		return SINH;
	}
	else if(strstr(text,"cosh\0"))
	{
		return COSH;
	}
	else if(strstr(text,"tanh\0"))
	{
		return TANH;
	}
	else
	{
		return 0;
	}
}
 
 /*
 * Funkce prevede pole charu na spojovy seznam tokenu.
 * Pokud dojde k chybe, fce vraci null.
 */
chrTkn *preproc(int vstupLen, char input[])
{
	int i=0,cislo=0,k=0;
	char *znak = NULL; /*ukazatel na cast retezce, ve kterem by melo byt jmeno fce*/
	int kodFce = 0;
	
	chrTkn *root = NULL;
	
	while(i < vstupLen)
	{
			/*Operatory*/
			if(isOperator(input[i]) || (input[i] == ')') || (input[i] == '('))
			{
				/*Kontrola zda se nejedna o unarni - */ 
				if(input[i] == '-')
				{
					if ((i == 0) || (input[i-1] == ')') || (input[i-1] == '(') || isOperator(input[i-1]))
					{
						root = vlozNaKonec(root,'_',0);
					}
					else
					{
						root = vlozNaKonec(root,input[i],0);
					}
				}
				else
				{
					root = vlozNaKonec(root,input[i],0);
				}
				/*printf("Nalezen operator %c\n",input[i]);*/
				
				i++;
				continue;
			}
			
			/*Promenna*/
			if(input[i] == 'x')
			{
                        root = vlozNaKonec(root,input[i],0);
            }
            		
			/*Cislo*/
			if(input[i] >= '0' && input[i] <= '9')
			{
				cislo = 0;
				while(input[i] >='0' && input[i] <= '9' && i < vstupLen)
				{
					/*nacitani cisla podle zanku*/
					cislo *= 10;
					cislo += (input[i] - '0');
					i++;
				}
				/*printf("Nalezeno cislo %i\n",cislo);*/
				root = vlozNaKonec(root,cislo,1);
				
				continue;
			}
			
			/*Jiny znak nez promenna, bude potreba najit fci. Pokud bude nalezena pouze cast fce (napr si misto sin)
			 * fce vrati NULL.*/
			if ((input[i] >= 'a') && (input[i] <= 'z'))
			{
				/*Kontrola delky vstupu*/
				for(k=5;k>1;k--)
				{
					if(i+k < vstupLen)
					{
						znak = strncpy(znak,(char*)input[i],k);
						break;
					}
				}
				if(znak == NULL)
				{
					printf("Chyba pri nalezeni fce na pozici %d.\n",i);
					smaz(root);
					return NULL;
				}
				
				kodFce = najdiFci(znak);
				if(kodFce == 0)
				{
					printf("Chyba pri nalezeni fce na pozici %d.\n",i);
					smaz(root);
					return NULL;
				}
				else
				{
					root = vlozNaKonec(root, kodFce, 0);
				}
			}
			
			/*
			 * Pokud narazi na prazdny charakter, ukonci pruchod retezcem.
			 * Neni nutno inicializovat cele staticke pole vstupu, pouze
			 * staci pridat na konec znak \0. Pri nacitani vstupu ze statickeho
			 * pole se bez pouziti \0 objevuji artefakty.
			 */ 
			if(input[i] == '\0')
			{
				return root;
			}
			
			i++;
	}
	
	return root;
}
