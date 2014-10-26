/*
 * Knihovna obsahuje implementaci shunting yard algoritmu, ktery slouzi 
 * k prevodu z infixove notace do postfix notace.
 */
#include "shuntyard.h"

/*
 * Funkce vlozi znak na vrchol zasobniku.
 */
 void push(int *sp, char stck[], char znak)
 {
	 stck[*sp] = znak;
	 (*sp)++;
 }
 
/*
 * Funkce vybere znak z vrcholu zasobniku.
 */
 char pop(int *sp, char stck[])
 {
	  /*SP ukazuje na prvni volnou pozici, pokud SP == 0, zasobnik je prazdny*/
	  if(*sp <= 0)
	  {
		  return '\00';
	  }
	  else
	  {
		  (*sp)--;
		  return stck[*sp];
	  }
 }
  
/*
 * Funkce ukaze znak na vrcholu zasobniku.
 */
 char show(int *sp, char stck[])
 {
	   if(*sp <=0 )
	   {
		   return '\00';
	   }
	   else
	   {
		   return stck[*sp-1];
	   }
 }

/*
 * Funkce zjisti, zda je zadany znak matematicky operator.
 */
 int isOperator(char op)
 {
	 switch(op)
	 {
		 case '+':
		 case '-':
		 case '*':
		 case '/':
		 case '^': return 1;
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
	 
	 switch (op)
	 {
		 case '+':
		 case '-': return 1;
		 case '*':
		 case '/': return 2;
		 case '^': return 3;
			 
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
		 case '+':
		 case '-':
		 case '*':
		 case '/': return 1;
		 
		 default: return 0;
			 
	 } 
 }
 
 /*
  * Funkce provede algoritmus shunting yard nad vstupem, ktery obsahuje
  * matematicky vyraz. Vrati matematicky vyraz v postfix notaci.
  * 
  * CHYBY:
  * 1: Neuzavreny vyraz.
  */
 int shuntingYard(char input[], char postbuff[], int inLen)
 {
	 char stack[255];
	 char op1,op2;
	 /*
	  * i = ukazatel do pole vstupu
	  * cur = ukazatel do pole postbuff (=vystup)
	  * sp = stack pointer, ukazuje na prvni volnou pozici
	  */
	  int i=0, cur=0 ,sp=0;
	  for (i = 0; i < 255; i++)
	  {
		  stack[i] = '\0';
	  }
	  
	  i=0;
	  while (input[i] != '\0')
	  {
		  /*
		   * Promenna
		   */
		   if(input[i] == 'x')
		   {
			   /*printf("Nalezena promenna: %c. Vkladam do vystupu na pozici: %d.\n",input[i],cur);*/
			   postbuff[cur++] = input[i];
		   }
		   
		   /*
		    * Cislo
		    */
		    if ((input[i] >= '0') && (input[i] <= '9'))
			{
				/*printf("Nalezeno cislo: %c. Vkladam do vystupu na pozici: %d.\n",input[i],cur);*/
				postbuff[cur++] = input[i];
			}
			
			/*
		    * Operator.
		    */
			if(isOperator(input[i]))
			{
				  op1 = input[i];
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
							  postbuff[cur++] = pop(&sp,stack);
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
							  postbuff[cur++] = pop(&sp,stack);
						  }
						  else
						  {
							  break;
						  }
					  }
				  }
				  
				  /*printf("Vkladam operator %c do zasobniku na pozici %d\n",op1,sp);*/
				  push(&sp,stack,op1);
			}
			
			
		    /*
		     * Zavorky.
		     */
		    if(input[i] == '(')
		    {
				/*printf("Nalezena leva zavorka. Vkladam na zasobnik na pozici %d.\n",sp);*/
				push(&sp,stack,'(');
			}
			if(input[i] == ')')
			{
				/*
				 * Dokud na vrcholu zasobniku neni leva zavorka, davej znaky na vystup.
				 * Levou zavorku na vystup nedavej, pouze vyjmi ze  zasobniku.
				 */
				 while(show(&sp,stack) != '(')
				 {
					 /*printf("Vkladam znak %c do vystupu na pozici %d.\n",show(&sp,stack),cur);*/
					 postbuff[cur++] = pop(&sp,stack);
					 
					 /*Neuzavreny vyraz*/
					 if(sp == 0)
					 {
						 return 1;
					 }
				 }
				 /*vyjmuti leve zavorky ze zasobniku*/
				 pop(&sp,stack);
			}
			
			i++;
   }
   /*
    * Zpracovany operatory ze vstupu, vyprazdnit zasobnik na vystup
    */
    while(sp)
    {
		/*printf("%d : %s\n",sp,stack);*/
		if(show(&sp,stack) == '(')
		{
			return 1;
		}
        postbuff[cur++] = pop(&sp,stack);
    }
	  
	  
	  return 0;
 }
