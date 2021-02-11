#include "cesar.h"

#include <stdio.h>
#include <ctype.h>

int mod(int a, int base){    
  return (a < 0 ? ((a % base) + base) % base : a % base);
}

char CESAR (int k, char* nom_fic_input, char* nom_fic_output, char MODE, char* WriteMode){
    FILE* InputFp;
    FILE* OutputFp;
    char currentCharacter;

    OutputFp = NULL;
    InputFp = fopen(nom_fic_input, "r");
    if (!InputFp){
        printf("Error fichier introuvable\n");
        goto Error;
    }

    OutputFp = fopen(nom_fic_output, WriteMode);

    if (WriteMode[0] == 'a'){
        fprintf(OutputFp, "Key is : %d\n", k);
    }
        
    switch (MODE)
    {
    case 0: // Dechif
        while ((currentCharacter = fgetc(InputFp)) != EOF){
            if (isalpha(currentCharacter)){
                fprintf(OutputFp, "%c", islower(currentCharacter) ? mod((currentCharacter - 'a' - k), 26) + 'a' : mod((currentCharacter - 'A' - k), 26) + 'A');
            } else {
                fprintf(OutputFp, "%c", currentCharacter);
            }
        }
        break;
    
    case 1: // Chiff
        while ((currentCharacter = fgetc(InputFp)) != EOF){
            if (isalpha(currentCharacter)){
                fprintf(OutputFp, "%c", islower(currentCharacter) ? ((currentCharacter - 'a' + k) % 26) + 'a' : ((currentCharacter - 'A' + k) % 26) + 'A');
            } else {
                fprintf(OutputFp, "%c", currentCharacter);
            }
        }
        break;
    
    case 2: // Dechiff ASCII
        while ((currentCharacter = fgetc(InputFp)) != EOF){
            fprintf(OutputFp, "%c", mod((currentCharacter - k), 128));
        }
        break;

    
    case 3: // Chiff ASCII
        while ((currentCharacter = fgetc(InputFp)) != EOF){
            fprintf(OutputFp, "%c", (currentCharacter + k) % 128);
        }
        break;

    default:
        goto Error;
        break;
    }

    if (WriteMode[0] == 'a'){
        fprintf(OutputFp, "\n");
    }

    fclose(InputFp);
    fclose(OutputFp);

    return 1;

Error:

    if (OutputFp)
        fclose(OutputFp);

    if (InputFp)
        fclose(InputFp);

    return 0;
}

char CHIFF_CESAR (int k, char* nom_fic_clair, char* nom_fic_chiff){
    return CESAR(k, nom_fic_clair, nom_fic_chiff, 1, "w");
}

char DECHIFF_CESAR (int k, char* nom_fic_chiff, char* nom_fic_dechiff){
    return CESAR(k, nom_fic_chiff, nom_fic_dechiff, 0, "w");
}