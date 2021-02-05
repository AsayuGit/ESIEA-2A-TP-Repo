#ifndef _CRYPTO_H
#define _CRYPTO_H

char CHARGER_CLE(char cle[26], char* nom_fic_cle);
char CHIFF_MONO_ALPHA(char cle[26], char* nom_fic_clair, char* nom_fic_chiff);
char DECHIFF_MONO_ALPHA(char cle[26], char* nom_fic_chiff, char* nom_fic_dechif);

#endif