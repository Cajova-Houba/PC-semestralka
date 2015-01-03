/*
 * Knihovna obsahuje implementaci shunting yard algoritmu, ktery slouzi 
 * k prevodu z infixove notace do postfix notace.
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shuntyard.h"
#include "charToken.h"
#include "zasobnik.h"

#define DBG

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
 
 /*Funkce kontroluje preteceni znakoveho zasobniku*/
 int checkOFc(char znak)
{
	if(OFd)
	{
		#ifdef DBG 
		printf("Error: Stack overflow at %c symbol.\n",znak);
		#endif
		
		OFd = 0;
		return 1;
	}
	
	return 0;
}
 
 /*
  * Funkce precte dodany seznam tokenu a vrati novy seznam, kde tokeny
  * tvori matematicky vyraz v postfixove notaci.
  * Pokud fce vrati NULL, doslo k chybe.
  */
 chrTkn *shuntingYard(chrTkn *vstup)
 {
	#define STACK_LEN 255
	char stack[STACK_LEN];
	chrTkn *tmp = NULL;
	chrTkn *vystup = NULL;
	/*Prave zpracovavany znak, operator1, operator2*/
	char znak = '\0', op1 = '\0', op2='\0';
	/*stack pointer*/
	int sp=0,i;
	
	if (vstup == NULL)
	{
		printf("Error: NULL input.\n");
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
			vystup = vlozNaKonecD(vystup,tmp->dVal);
			
			#ifdef DBG
			printf("Nalezeno cislo %.3f, vlozeno na vystup\n",tmp->dVal);
			#endif
		}
		else
		{
			/*Znak*/
			znak = getValc(tmp);
			
			
			/*Promenna - dej na vystup*/
			if(znak == 'x')
			{
				vystup = vlozNaKonecC(vystup,znak);
			}
			
			/*Operator*/
			if(isOperator(znak))
			{
				op1 = znak;
				  
				#ifdef DBG
				printf("Nalezen operator: %c. Zasobnik: %s\n",op1,stack);
				#endif
				  
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
							vystup = vlozNaKonecC(vystup,pop(&sp,stack));
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
								vystup = vlozNaKonecC(vystup,pop(&sp,stack));
							}
							else
							{
								break;
							}
						}
				}/*end while*/
				/*Vlozeni operatoru na zasobnik*/
				#ifdef DBG
				printf("Vkladam operator %c do zasobniku na pozici %d\n",op1,sp);
				#endif
				push(&sp,stack,op1,STACK_LEN);
				if(checkOFc(op1))
				{
					return NULL;	
				}
			}/*end if operator*/
			
		   /*
		    * Zavorky.
		    */
		    if(znak == '(')
		    {
				#ifdef DBG
				printf("Nalezena leva zavorka. Vkladam na zasobnik na pozici %d.\n",sp);
				#endif
				
				push(&sp,stack,'(',STACK_LEN);
				if(checkOFc('('))
				{
					return NULL;	
				}
			}
			if(znak == ')')
			{
				/*
				* Dokud na vrcholu zasobniku neni leva zavorka, davej znaky na vystup.
				* Levou zavorku na vystup nedavej, pouze vyjmi ze  zasobniku.
				*/
				while(show(&sp,stack) != '(')
				{
					#ifdef DBG
					printf("Vkladam znak %c na vystup.\n",show(&sp,stack));
					#endif
					 
					vystup = vlozNaKonecC(vystup,pop(&sp,stack));
					/*postbuff[cur++] = pop(&sp,stack);*/
					 
					/*Neuzavreny vyraz*/
					if(sp == 0)
					{
						printf("Error: Unclosed bracket.\n");
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
			printf("Error: Unclosed bracket.\n");
			return NULL;
		}
        vystup = vlozNaKonecC(vystup,pop(&sp,stack));
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
	else if(strstr(text,"acotan\0"))
	{
		return ACOTAN;
	}
	else
	{
		return 0;
	}
}

/*
 * Funkce je nahradou fce strncpy() se kterou jsou pouze problemy.
 * Funkce vraci odkaz na nove alokovaonu pamet, kterou je treba uvolnit.
 */
char *realStrncpy(char source[], int cnt)
{
	char *res;
	int i;
	
	res = malloc((cnt+1)*sizeof(char));
	for(i = 0; i < cnt; i++)
	{
		res[i] = source[i];
	}
	
	res[cnt] = '\0';
	return res;
}

 
 /*
 * Funkce prevede pole charu na spojovy seznam tokenu.
 * Pokud dojde k chybe, fce vraci null.
 */
chrTkn *preproc(int vstupLen, char input[])
{
	#ifdef DBG
	printf("Start preprocesingu.. ");
	#endif
	int i=0;
	int od=0,poc=0; /*odkud a pocet znaku v retezci tvorici cislo*/
	double cislo=0; /*nalezene cislo*/
	char *tmp; /*zde bude zkopirovano nalezene cislo*/
	unsigned int k=0;
	char znak[10];/*ukazatel na cast retezce, ve kterem by melo byt jmeno fce*/
	int kodFce = 0;
	
	chrTkn *root = NULL;
	
	/*inicializace znak*/
	for (i = 0; i < 10; i++)
	{
		znak[i] = '\0';
	}
	i=0;
	
	while(i < vstupLen)
	{
			/*Operatory*/
			if(isOperator(input[i]) || (input[i] == ')') || (input[i] == '('))
			{
				/*Kontrola zda se nejedna o unarni - */ 
				if(input[i] == '-')
				{
					if ((i == 0) || (input[i-1] == '(') || isOperator(input[i-1]))
					{
						root = vlozNaKonecC(root,'_');
					}
					else
					{
						root = vlozNaKonecC(root,input[i]);
					}
				}
				else
				{
					root = vlozNaKonecC(root,input[i]);
				}
				/*printf("Nalezen operator %c\n",input[i]);*/
				
				i++;
				continue;
			}
			
			/*Promenna*/
			else if(input[i] == 'x')
			{
                        root = vlozNaKonecC(root,input[i]);
            }
            		
			/*Cislo*/
			else if((input[i] >= '0' && input[i] <= '9') || input[i] == '.' || input[i] == 'e' || input[i] == 'E')
			{
				od = i;
				poc = 0;
				while((input[i] >= '0' && input[i] <= '9') || input[i] == '.' || input[i] == 'e' || input[i] == 'E')
				{
					poc++;
					i++;
				}
				
				#ifdef DBG
				printf("Prevadim retezec na cislo. %i znaku od %c.\n",poc,input[od]);
				#endif
				
				tmp = realStrncpy((input+od),poc);
				cislo = atof(tmp);
				
				#ifdef DBG
				printf("Nalezeno cislo %.3f\n",cislo);
				#endif
				
				root = vlozNaKonecD(root,cislo);
				
				continue;
			}
			
			/*Jiny znak nez promenna, bude potreba najit fci. Pokud bude nalezena pouze cast fce (napr si misto sin)
			 * fce vrati NULL.*/
			else if ((input[i] >= 'a') && (input[i] <= 'z'))
			{
				/*Kontrola delky vstupu*/
				k=0;
				while(k<10)
				{
					if((input[i+k] >= 'a') && (input[i+k]) <= 'z')
					{
						znak[k] = input[i+k];
					}
					else
					{
						break;
					}
					k++;
				}
				i += k;
				
				if(znak == NULL)
				{
					printf("Error when searching for function at %d. position.\n",i);	
					smaz(root);
					return NULL;
				}
				
				kodFce = najdiFci(znak);
				if(kodFce == 0)
				{
					printf("Error when searching for function at %d. position.\n",i);
					smaz(root);
					return NULL;
				}
				else
				{
					root = vlozNaKonecC(root, kodFce);
				}
				
				continue;
			}
			
			/*
			 * Pokud narazi na prazdny charakter, ukonci pruchod retezcem.
			 * Neni nutno inicializovat cele staticke pole vstupu, pouze
			 * staci pridat na konec znak \0. Pri nacitani vstupu ze statickeho
			 * pole se bez pouziti \0 objevuji artefakty.
			 */ 
			else if(input[i] == '\0')
			{
				printf("hotovo \n");
				return root;
			}
			
			i++;
	}
	
	#ifdef DBG
	printf("hotovo\n");
	#endif
	return root;
}

/*
Funkce jednoduchym algoritmem overi spravnost zadane postfixove notace.
Pokud je vse v poradku, vrati 0.
*/
int validateRPN(chrTkn *root)
{
	int cntr = 0;
	char znak = '\00';
	chrTkn *tmp = root;
	
	if(tmp == NULL)
	{
		return 1;
	}
	
	/*
	Za kazde cislo +1, za bin operator -2, za un operator a fci -1.
	Pokud cntr klesne pod 0 -> chyba. Pokud na konci cntr neni 1 -> chyba
	*/
	while (tmp != NULL)
	{
		if(tmp->jeCislo)
		{
			cntr++;
		}
		else
		{
			znak = tmp->cVal;
			if(znak == 'x')
			{
				cntr ++;
			}
			else if(znak == PLUS || znak == MINUS || znak == KRAT || znak == DELENO || znak == MOCN)
			{
				cntr -= 2; /*vyber 2 hodnot ze zasobniku*/
				cntr ++;   /*vlozeni vysledku na zasobnik*/
			}
			else if((znak >= ABS && znak <= TANH) || znak == UMIN)
			{
				cntr --; /*vyber jedne hodnoty ze zasobniku*/
				cntr ++; /*vlozeni vysledku na zasobnik*/
			}
			
			if(cntr <= 0)
			{
				return 1;
			}
		}
		
		tmp = tmp->dalsi;
	}
	
	if (cntr == 1)
	{
		return 0;
	}
	
	return 1;
}
