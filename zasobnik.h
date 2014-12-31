#ifndef ZASOBNIK_H
#define ZASOBNIK_H

void push(int *sp, char stck[], char znak);
char pop(int *sp, char stck[]);
char show(int *sp, char stck[]);
void pushd(int *sp, double stck[], double cislo);
double popd(int *sp, double stck[]);
double showd(int *sp, double stck[]);

/*Flagy podteceni zasobniku*/
extern UFc,UFd;

#endif
