#ifndef _CRYPTANALYSE_H
#define _CRYPTANALYSE_H

char CALC_FREQ_LETTRES_ALPHA(float alpha[26], char* nom_fic);
void AFFIC_PLUS_GRDE_FREQ(float alpha[26]);
int GET_KEY(float alpha[26]);
void RECHERCHE_EXHAUSTIVE(char* fic_chiff, char* fic_dechiff);

#endif