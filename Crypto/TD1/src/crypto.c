#include "crypto.h"

#include <stdio.h>
#include <ctype.h>

char CHARGER_CLE(char cle[26], char* nom_fic_cle){
    int i;
    FILE* fp;
    
    fp = fopen(nom_fic_cle, "r");
    if (fp){
        for (i = 0; i<26; i++){
            cle[i] = fgetc(fp);
        }
        return 1;
    }
    return 0;
}

char CHIFF_MONO_ALPHA(char cle[26], char* nom_fic_clair, char* nom_fic_chiff){
    FILE* clairFp;
    FILE* chiffFp;
    char currentCharacter;

    chiffFp = NULL;
    clairFp = fopen(nom_fic_clair, "r");
    if (!clairFp){
        printf("Error fichier clair introuvable\n");
        goto Error;
    }

    chiffFp = fopen(nom_fic_chiff, "w");

    while ((currentCharacter = fgetc(clairFp)) != EOF){
        if (isalpha(currentCharacter)){
            fprintf(chiffFp, "%c", isupper(currentCharacter) ? toupper(cle[currentCharacter - 'A']) : cle[currentCharacter - 'a'], currentCharacter);
        } else {
            fprintf(chiffFp, "%c", currentCharacter);
        }
    }

    fclose(clairFp);
    fclose(chiffFp);

    return 1;

Error:
    if (clairFp)
        fclose(clairFp);
    if (chiffFp)
        fclose(chiffFp);

    return 0;
}

char DECHIFF_MONO_ALPHA(char cle[26], char* nom_fic_chiff, char* nom_fic_dechif){
    FILE* chiffFp;
    FILE* dechiffFp;
    char currentCharacter;
    int highLow;
    int i;

    dechiffFp = NULL;
    chiffFp = fopen(nom_fic_chiff, "r");
    if (!chiffFp){
        printf("Error fichier chiff introuvable\n");
        goto Error;
    }

    dechiffFp = fopen(nom_fic_dechif, "w");

    while ((currentCharacter = fgetc(chiffFp)) != EOF){
        if (isalpha(currentCharacter)){
            if (highLow = isupper(currentCharacter)){
                currentCharacter = tolower(currentCharacter);
            }
            
            for (i = 0; i < 26; i++){
                if (cle[i] == currentCharacter){
                    fprintf(dechiffFp, "%c", highLow ? 'A' + i : 'a' + i);
                    break;
                }
            }
        } else {
            fprintf(dechiffFp, "%c", currentCharacter);
        }
    }

    fclose(chiffFp);
    fclose(dechiffFp);

    return 1;

Error:
    if (chiffFp)
        fclose(chiffFp);
    if (dechiffFp)
        fclose(dechiffFp);

    return 0;
}