#include "vigenere.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <unistd.h>

int mod(int a, int base){    
  return (a < 0 ? ((a % base) + base) % base : a % base);
}

int DETERM_LONG_TEXTE(char* nom_fic){
    FILE* filePointer;
    char currentCharacter;
    int textLen;

    filePointer = fopen(nom_fic, "r");
    if (!filePointer){
        printf("Error, couldn't oppen file\n>%s<\n", nom_fic);
        return 0;
    }

    textLen = 0;
    while ((currentCharacter = fgetc(filePointer)) != EOF){
        if (isalpha(currentCharacter)){
            textLen++;
        }
    }

    fclose(filePointer);
    return textLen;
}

char CHARGER_CLE(int T, char cle[], char* nom_fic_cle){
    FILE* filePointer;
    char currentCharacter;
    int i;

    filePointer = fopen(nom_fic_cle, "r");
    if (!filePointer){
        printf("Error, couldn't oppen file\n>%s<\n", nom_fic_cle);
        return EXIT_FAILURE;
    }

    i = 0;
    while (((currentCharacter = fgetc(filePointer)) != EOF) && (i < T)){
        if (isalpha(currentCharacter)){
            cle[i] = currentCharacter;
            i++;
        }
    }

    fclose(filePointer);
    return EXIT_SUCCESS;
}

char VIGENERE(int T, char cle[], char* nom_fic_input, char* nom_fic_output, char MODE){
    FILE* InputPointer;
    FILE* OutputPointer;
    char currentCharacter;
    int KeyPointer;
    char offset;

    OutputPointer = NULL;
    InputPointer = fopen(nom_fic_input, "r");
    if (!InputPointer){
        printf("Error, couldn't oppen file\n>%s<\n", nom_fic_input);
        goto Error;
    }

    OutputPointer = fopen(nom_fic_output, "w");
    if (!OutputPointer){
        printf("Error, couldn't create file\n>%s<\n", nom_fic_output);
        goto Error;
    }

    KeyPointer = 0;
    switch (MODE)
    {
    case 0: // Chiff
        while ((currentCharacter = fgetc(InputPointer)) != EOF){
            if (isalpha(currentCharacter)){
                offset = islower(currentCharacter) ? 'a' : 'A';
                fprintf(OutputPointer, "%c", (((tolower(cle[KeyPointer]) - 'a') + (currentCharacter - offset)) % 26) + offset);
                KeyPointer = (KeyPointer + 1) % T;
            }
        }
        break;

    case 1: // Dechiff
        while ((currentCharacter = fgetc(InputPointer)) != EOF){
            if (isalpha(currentCharacter)){
                offset = islower(currentCharacter) ? 'a' : 'A';
                fprintf(OutputPointer, "%c", mod(((currentCharacter - offset) - (tolower(cle[KeyPointer]) - 'a')), 26) + offset);
                KeyPointer = (KeyPointer + 1) % T;
            }
        }
        break;
    
    default:
        goto Error;
        break;
    }

    fclose(InputPointer);
    fclose(OutputPointer);

    return EXIT_SUCCESS;

Error:

    if (InputPointer)
        fclose(InputPointer);

    if (OutputPointer)
        fclose(OutputPointer);
    return EXIT_FAILURE;
}

char CHIFF_VIGENERE(int T, char cle[], char* nom_fic_clair, char* nom_fic_chiff){
    return VIGENERE(T, cle, nom_fic_clair, nom_fic_chiff, 0);
}

char DECHIFF_VIGENERE(int T, char cle[], char* nom_fic_chiff, char* nom_fic_dechiff){
    return VIGENERE(T, cle, nom_fic_chiff, nom_fic_dechiff, 1);
}

char RECHERCHE_CLE(char* nom_fic_clair, char* nom_fic_chiff, char* nom_fic_cle_rep){
    FILE* clairPointer;
    FILE* chiffPointer;
    FILE* OutputPointer;
    char clairCharacter, chiffCharacter;
    char offset;

    chiffPointer = NULL;
    OutputPointer = NULL;
    
    clairPointer = fopen(nom_fic_clair, "r");
    if (!clairPointer){
        printf("Error, couldn't oppen file\n>%s<\n", nom_fic_clair);
        goto Error;
    }

    chiffPointer = fopen(nom_fic_chiff, "r");
    if (!chiffPointer){
        printf("Error, couldn't oppen file\n>%s<\n", nom_fic_chiff);
        goto Error;
    }

    OutputPointer = fopen(nom_fic_cle_rep, "w");
    if (!OutputPointer){
        printf("Error, couldn't create file\n>%s<\n", nom_fic_cle_rep);
        goto Error;
    }

    while ((clairCharacter = fgetc(clairPointer)) != EOF){
        if (isalpha(clairCharacter)){
            offset = islower(clairCharacter) ? 'a' : 'A';
            if ((chiffCharacter = fgetc(chiffPointer)) != EOF){
                fprintf(OutputPointer, "%c", mod(((chiffCharacter - offset) - (clairCharacter - offset)), 26) + offset);
            }
        }
    }

    fclose(clairPointer);
    fclose(chiffPointer);
    fclose(OutputPointer);

    return EXIT_SUCCESS;

Error:

    if (clairPointer)
        fclose(clairPointer);

    if (chiffPointer)
        fclose(chiffPointer);

    if (OutputPointer)
        fclose(OutputPointer);
    return EXIT_FAILURE;
}

void AddLetterToKey(Key_t** TargetKey, char Letter){
    if (TargetKey){
        while (*TargetKey){
            TargetKey = &((*TargetKey)->next);
        }
        (*TargetKey) = (Key_t*)malloc(sizeof(Key_t));
        (*TargetKey)->Letter = Letter;
        (*TargetKey)->next = NULL;
    }
}

void FreeKey(Key_t* TargetKey){
    if (TargetKey){
        FreeKey(TargetKey->next);
        free(TargetKey);
    }
}

char EXTRACTION_CLE(char* nom_fic_cle_rep){
    FILE* filePointer;
    Key_t* OriginalKey;
    Key_t* OriginalKeyPointer;
    char currentCharacter;
    char* ExtractedKey;
    int ExtractedKeySize;
    int i, j;

    ExtractedKeySize = DETERM_LONG_TEXTE(nom_fic_cle_rep);
    ExtractedKey = (char*)malloc(sizeof(char)*(ExtractedKeySize+1));

    filePointer = fopen(nom_fic_cle_rep, "r");
    if (!filePointer){
        return EXIT_FAILURE;
    }

    fgets(ExtractedKey, ExtractedKeySize + 1, filePointer);
    OriginalKey = NULL;
    AddLetterToKey(&OriginalKey, ExtractedKey[0]);
    OriginalKeyPointer = OriginalKey;
    for (i = 1; i < ExtractedKeySize; i++){
        if (ExtractedKey[i] == OriginalKeyPointer->Letter){
            OriginalKeyPointer = OriginalKeyPointer->next;
            if (!OriginalKeyPointer)
                OriginalKeyPointer = OriginalKey;
        } else {
            OriginalKeyPointer = OriginalKey;
            for (j = 0; j <= i; j++){
                if (!OriginalKeyPointer){
                    AddLetterToKey(&OriginalKey, ExtractedKey[j]);
                } else if (ExtractedKey[j] == OriginalKeyPointer->Letter){
                    OriginalKeyPointer = OriginalKeyPointer->next;
                }
            }
            OriginalKeyPointer = OriginalKey;
            i = -1;
        }
    }

    OriginalKeyPointer = OriginalKey;
    printf("The Original key was : ");
    while (OriginalKeyPointer){
        printf("%c", OriginalKeyPointer->Letter);
        OriginalKeyPointer = OriginalKeyPointer->next;
    }printf("\n");

    FreeKey(OriginalKey);

    return EXIT_SUCCESS;
}