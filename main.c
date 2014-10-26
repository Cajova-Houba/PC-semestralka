#include <stdio.h>
#include <string.h>
#include "shuntyard.h"

/*========
 * -CHYBY-
 * =======
 * shuntyard.c:
 * 1: Neuzavreny vyraz.
 */

int main(int argc, char *argv[])
{
	int len = 50,i,chyba;
	char vstup[len], vystup[len];
	strcpy(vstup, "(5+(5-(5+(5-2^2)-3*2)+5)-2*5)\0");
	strcpy(vstup,argv[1]);
	for (i = 0; i < len; i++)
	{
		vystup[i] = '\0';
	}
	
	chyba = shuntingYard(vstup,vystup,len);
	if (chyba == 1)
	{
		printf("Chyba, zadan neuzavreny vyraz: %s.\n",vstup);
		return 0;
	}
	
	printf("vstup: %s\nvystup: %s\n",vstup,vystup);
	return 0;
}
