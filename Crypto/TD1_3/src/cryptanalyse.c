#include "cryptanalyse.h"

#include <stdio.h>
#include <stdlib.h>
#include "cesar.h"
#include <ctype.h>

char CALC_FREQ_LETTRES_ALPHA(float alpha[26], char* nom_fic){
    FILE* InputFp;
    char currentCharacter;
    int tAlpha, i;
    int nAlpha[26] = {0};
    
    InputFp = fopen(nom_fic, "r");
    if (!InputFp){
        printf("Error fichier introuvable\n");
        goto Error;
    }

    tAlpha = 0;
    while ((currentCharacter = fgetc(InputFp)) != EOF){
        if (isalpha(currentCharacter)){
            nAlpha[(tolower(currentCharacter) - 'a')]++;
            tAlpha++;
        }
    }

    for (i = 0; i < 26; i++){
        alpha[i] = (float)nAlpha[i] / (float)tAlpha;
    }

    return 1;

Error:

    if (InputFp)
        fclose(InputFp);

    return 0;
}

void AFFIC_PLUS_GRDE_FREQ(float alpha[26]){
    int i, c;
    float FrecMax;

    FrecMax = 0.0f;
    for (i = 0; i < 26; i++){
        if (alpha[i] > FrecMax){
            FrecMax = alpha[i];
            c = i;
        }
    }

    printf("Max frec reached by %c with %f\n", c + 'a', FrecMax);
}

int GET_KEY(float alpha[26]){
    int i, c;
    float FrecMax;

    FrecMax = 0.0f;
    for (i = 0; i < 26; i++){
        if (alpha[i] > FrecMax){
            FrecMax = alpha[i];
            c = i;
        }
    }

    return mod((c + 'a' - 'e'), 26);
}

void RECHERCHE_EXHAUSTIVE(char* fic_chiff, char* fic_dechiff){
    char i;
    for (i = 0; i < 26; i++){
        CESAR(i, fic_chiff, fic_dechiff, 0, "a");
    }
}