#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cesar.h"
#include "cryptanalyse.h"

int main(int argc, char* argv[]){
    int key;
    int i;
    float alpha[26] = {0};
    
    if (argc >= 4){
        if (strcmp(argv[1], "-frec") == 0){
            CALC_FREQ_LETTRES_ALPHA(alpha, argv[2]);
            AFFIC_PLUS_GRDE_FREQ(alpha);
            DECHIFF_CESAR(GET_KEY(alpha), argv[2], argv[3]);
        } else if (strcmp(argv[1], "-brutforce") == 0){
            RECHERCHE_EXHAUSTIVE(argv[2], argv[3]);
        }
    }else{
        printf("Utilisation : prog <MODE> <FILE IN> <FILE OUT>\n");
    }

    return 0;
}