#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int DETERM_CLE_ISBN(unsigned int TAB[13]){
    return (10 - (((TAB[0] + TAB[2] + TAB[4] + TAB[6] + TAB[8] + TAB[10]) + 3 * (TAB[1] + TAB[3] + TAB[5] + TAB[7] + TAB[9] + TAB[11])) % 10)) % 10;
}

void VEIRF_CLE_ISBN(unsigned int TAB[13]){
    printf((DETERM_CLE_ISBN(TAB) == TAB[12]) ? "Numéro ISBN Valide !\n" : "ATTENTION Numéro ISBN Non-valide !\n");
}

unsigned int DETERM_CLE_INSEE(unsigned int TAB[15]){
    int i;
    unsigned int key;

    key = 0;
    for (i = 0; i < 13; i++){
        key = ((key * 10 + TAB[i]) % 97);
    }

    return 97 - key;
}

void VERIF_CLE_INSEE(unsigned int TAB[15]){
    printf((DETERM_CLE_INSEE(TAB) == (TAB[13] * 10 + TAB[14])) ? "Numéro INSEE Valide !\n" : "ATTENTION Numéro INSEE Non-valide !\n");
}

int main(int argc, char* argv[]){
    int i;
    unsigned int ISBN[13] = {0};
    unsigned int INSEE[15] = {0};

    printf("Veuillez saisir un numéro ISBN (Chiffre par chiffre) :\n");
    for (i = 0; i < 13; i++){
        scanf("%u", ISBN + i);
    }
    //printf("La cle est %u\n", DETERM_CLE_ISBN(ISBN));
    VEIRF_CLE_ISBN(ISBN);

    printf("Veuillez saisir un numéro INSEE (Chiffre par chiffre) :\n");
    for (i = 0; i < 15; i++){
        scanf("%u", INSEE + i);
    }
    //printf("La cle est %u\n", DETERM_CLE_INSEE(INSEE));
    VERIF_CLE_INSEE(INSEE);

    return EXIT_SUCCESS;
}