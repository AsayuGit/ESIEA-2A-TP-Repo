#ifndef _CESAR_H
#define _CESAR_H

char CESAR (int k, char* nom_fic_input, char* nom_fic_output, char MODE, char* WriteMode);
char CHIFF_CESAR (int k, char* nom_fic_clair, char* nom_fic_chiff);
char DECHIFF_CESAR (int k, char* nom_fic_chiff, char* nom_fic_dechiff);
int mod(int a, int base);

#endif