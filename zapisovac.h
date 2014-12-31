#ifndef ZAPISOVAC_H
#define ZAPISOVAC_H

/*
fname - jmeno vystupnihou souboru
values - pole hodnot fce x=[i,0] f(x)=[i,1]
val_len - delka pole hodnot fce
limits - omezeni definicniho oboru, oboru hodnot [D_min,D_max,H_min,H_max] 
*/
void zapisDoSouboru(char *fname, double values[][2], int val_len, double limits[]);

#endif