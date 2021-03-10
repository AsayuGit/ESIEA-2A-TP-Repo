#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <math.h>

char CHIFF_VERNAM_1(char* nom_fic_clair, char* nom_fic_chiff, char* nom_fic_cle){
    FILE* clairFP;
    FILE* chiffFP;
    FILE* cleFP;

    unsigned int currentOctet;
    unsigned char currentKey;
    
    char* returnFilename; // Nom du fichier a afficher en cas d'erreur

    chiffFP = cleFP = NULL;
    clairFP = fopen(nom_fic_clair, "rb");
    if (!clairFP){
        returnFilename = nom_fic_clair;
        goto Error;
    }
    
    chiffFP = fopen(nom_fic_chiff, "wb");
    if (!chiffFP){
        returnFilename = nom_fic_chiff;
        goto Error;
    }
    
    cleFP = fopen(nom_fic_cle, "wb");
    if (!cleFP){
        returnFilename = nom_fic_cle;
        goto Error;
    }

    while ((currentOctet = fgetc(clairFP)) != EOF){
        currentKey = (unsigned char)rand()%256;
        printf("%2.x | %2.x | ", currentOctet, currentKey);
        currentOctet = currentOctet ^ currentKey;
        printf("%x\n", currentOctet);
        fputc(currentKey, cleFP);
        fputc(currentOctet, chiffFP);
    }

    fclose(clairFP);
    fclose(chiffFP);
    fclose(cleFP);

    return EXIT_SUCCESS;

Error:
    printf("Couldn't oppen file : %s\n", returnFilename);

    if (clairFP)
        fclose(clairFP);
    if (chiffFP)
        fclose(chiffFP);
    if (cleFP)
        fclose(cleFP);

    return EXIT_FAILURE;
}

char DECHIFF_VERNAM_1(char* nom_fic_chiff, char* nom_fic_clair, char* nom_fic_cle){
    FILE* clairFP;
    FILE* chiffFP;
    FILE* cleFP;

    unsigned int currentOctet;
    unsigned char currentKey;
    
    char* returnFilename; // Nom du fichier a afficher en cas d'erreur

    clairFP = cleFP = NULL;
    chiffFP = fopen(nom_fic_chiff, "rb");
    if (!chiffFP){
        returnFilename = nom_fic_chiff;
        goto Error;
    }
    
    cleFP = fopen(nom_fic_cle, "rb");
    if (!cleFP){
        returnFilename = nom_fic_cle;
        goto Error;
    }

    clairFP = fopen(nom_fic_clair, "wb");
    if (!clairFP){
        returnFilename = nom_fic_clair;
        goto Error;
    }

    while ((currentOctet = fgetc(chiffFP)) != EOF){
        currentKey = fgetc(cleFP);
        printf("%2.x | %2.x | ", currentOctet, currentKey);
        currentOctet = currentOctet ^ currentKey;
        printf("%x\n", currentOctet);
        
        fputc(currentOctet, clairFP);
    }

    fclose(clairFP);
    fclose(chiffFP);
    fclose(cleFP);

    return EXIT_SUCCESS;

Error:
    printf("Couldn't oppen file : %s\n", returnFilename);

    if (clairFP)
        fclose(clairFP);
    if (chiffFP)
        fclose(chiffFP);
    if (cleFP)
        fclose(cleFP);

    return EXIT_FAILURE;
}

char CHIFF_VERNAM_2(char* nom_fic_clair, char* nom_fic_chiff, double Seed){
    FILE* clairFP;
    FILE* chiffFP;

    unsigned int currentOctet;
    unsigned char currentKey;
    unsigned long long int Val;
    
    char* returnFilename; // Nom du fichier a afficher en cas d'erreur

    chiffFP = NULL;
    clairFP = fopen(nom_fic_clair, "rb");
    if (!clairFP){
        returnFilename = nom_fic_clair;
        goto Error;
    }
    
    chiffFP = fopen(nom_fic_chiff, "wb");
    if (!chiffFP){
        returnFilename = nom_fic_chiff;
        goto Error;
    }

    while ((currentOctet = fgetc(clairFP)) != EOF){
        Seed = 3.9999*Seed*(1.0-Seed);
        Val = (unsigned long long int)(Seed*pow(10, 15));
        currentKey = (unsigned char)(Val%256);
        printf("%2.x | %2.x | ", currentOctet, currentKey);
        currentOctet = currentOctet ^ currentKey;
        printf("%x\n", currentOctet);
        fputc(currentOctet, chiffFP);
    }

    fclose(clairFP);
    fclose(chiffFP);

    return EXIT_SUCCESS;

Error:
    printf("Couldn't oppen file : %s\n", returnFilename);

    if (clairFP)
        fclose(clairFP);
    if (chiffFP)
        fclose(chiffFP);

    return EXIT_FAILURE;
}

char DECHIFF_VERNAM_2(char* nom_fic_chiff, char* nom_fic_clair, double Seed){
    return CHIFF_VERNAM_2(nom_fic_chiff, nom_fic_clair, Seed);
}

int main(int argc, char* argv[]){
    int ReturnValue;
    srand(time(NULL));

    if (argc >= 5){
        if (strcmp(argv[1], "-chiff") == 0){
            ReturnValue = CHIFF_VERNAM_1(argv[2], argv[3], argv[4]);
        } else if (strcmp(argv[1], "-dechiff") == 0){
            ReturnValue = DECHIFF_VERNAM_1(argv[2], argv[3], argv[4]);
        } else if (strcmp(argv[1], "-chiff2") == 0){
            ReturnValue = CHIFF_VERNAM_2(argv[2], argv[3], atof(argv[4]));
        } else if (strcmp(argv[1], "-dechiff2") == 0){
            ReturnValue = DECHIFF_VERNAM_2(argv[2], argv[3], atof(argv[4]));
        }
        printf(ReturnValue == EXIT_SUCCESS ? "Success !\n" : "Failure !\n");
    }else{
        printf("Utilisation : prog <MODE> <FILE IN> <FILE OUT> <KEY>\n");
    }

    return EXIT_SUCCESS;
}