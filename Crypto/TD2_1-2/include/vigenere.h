#ifndef _VIGENERE_H
#define _VIGENERE_H

typedef struct Key {
    char Letter;
    struct Key* next;
} Key_t;

int mod(int a, int base);
int DETERM_LONG_TEXTE(char* nom_fic);
char CHARGER_CLE(int T, char cle[], char* nom_fic_cle);
char VIGENERE(int T, char cle[], char* nom_fic_input, char* nom_fic_output, char MODE);
char CHIFF_VIGENERE(int T, char cle[], char* nom_fic_clair, char* nom_fic_chiff);
char DECHIFF_VIGENERE(int T, char cle[], char* nom_fic_chiff, char* nom_fic_dechiff);
char RECHERCHE_CLE(char* nom_fic_clair, char* nom_fic_chiff, char* nom_fic_cle_rep);
char EXTRACTION_CLE(char* nom_fic_cle_rep);

#endif