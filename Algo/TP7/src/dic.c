#include "dic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symlist {
    char* word;
    symlist* next;
};

struct dictionary {
    char* word;
    int nbOfSym;
    symlist* sym;
    dictionary* next;
};

void clear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

char* subStr(char* Src, int Start, int End){
    char* string;

    string = (char*)malloc(sizeof(char)*(End - Start + 1));
    memcpy(string, &Src[Start], End - Start);
    string[End - Start] = '\0';

    return string;
}

dictionary** DicAddEntry(dictionary** dic, char* word){
    while ((*dic) != NULL){ // Search for a free spot
        dic = &((*dic)->next);
    }
    (*dic) = (dictionary*)malloc(sizeof(dictionary));
    (*dic)->word = word;
    (*dic)->nbOfSym = 0;
    (*dic)->sym = NULL;
    (*dic)->next = NULL;

    return dic;
}

void DicAddSym(dictionary* dic, char* word){
    symlist** sym;

    sym = &(dic->sym);
    while ((*sym) != NULL){ // Search for a free spot
        sym = &((*sym)->next);
    }
    (*sym) = (symlist*)malloc(sizeof(symlist));
    (*sym)->word = word;
    (*sym)->next = NULL;

    dic->nbOfSym++;
}

char* ToDynStr(const char* TEXT){
    char* tempString;

    tempString = (char*)malloc(sizeof(char)*strlen(TEXT));
    strcpy(tempString, TEXT);

    return tempString;
}

void printDicWord(dictionary* entry){
    symlist* LocalSymList;
    
    printf("%s ", entry->word);
    if (entry->nbOfSym == 0){
        printf("( Aucun Synonyme )\n");
    } else {
        LocalSymList = entry->sym;

        printf("( ");
        while (LocalSymList){
            printf("%s ", LocalSymList->word);
            LocalSymList = LocalSymList->next;
        }
        printf(")\n");
    }
}

void listDic(dictionary* dic){
    system(CLEAR);
    if (dic == NULL){
        printf("Dictionaire vide\n");
    } else {
        do {
            printDicWord(dic);
            dic = dic->next;
        }while (dic != NULL);
    }
    printf("\nAppuyer sur une touche pour revenir a menu principal\n");
    getchar();
}

void AddWordToDictionary(dictionary** dic){
    char Buffer[100];
    int nbOfSyn;
    int i;

    dictionary** LastEntry;

    system(CLEAR);
    printf("Veuillez entrer le mot a ajouter : ");
    scanf("%s", Buffer);
    LastEntry = DicAddEntry(dic, ToDynStr(Buffer));

    system(CLEAR);
    printf("Veuillez entrer le nombre de synonymes : ");
    scanf("%d", &nbOfSyn);

    for (i = 0; i < nbOfSyn; i++){
        system(CLEAR);
        printf("Veuillez entrer le synonime #%d : ", i + 1);
        scanf("%s", Buffer);
        DicAddSym(*LastEntry, ToDynStr(Buffer));
    }
};

dictionary* Search(dictionary* dic, char* Buffer){
    while (dic){
        if (strcmp(dic->word, Buffer) == 0){
            return dic;
        }
        dic = dic->next;
    }
    return NULL;
}

void SearchWordInDic(dictionary* dic){
    char Buffer[100];
    dictionary* element;
    
    system(CLEAR);
    printf("Veuillez entrer le mot a rechercher : ");
    scanf("%s", Buffer);
    printf("\n");
    element = Search(dic, Buffer);
    if (element){
        printDicWord(element);
    }else{
        printf("Mot introuvable !\n");
    }
    clear();
    printf("\nAppuyer sur une touche pour revenir a menu principal\n");
    getchar();
}

void DeleteSymList(symlist** sym){
    if (*sym){
        DeleteSymList(&((*sym)->next));
        free((*sym)->word);
        free(*sym);
        (*sym) = NULL;
    }
}

void DeleteElement(dictionary** element){
    dictionary* NextElement;

    NextElement = (*element)->next;
    
    DeleteSymList(&((*element)->sym));
    free((*element)->word);
    free(*element);
    
    (*element) = NextElement;
}

void DeleteWordInDic(dictionary** dic){
    char Buffer[100];
    dictionary** element;
    
    system(CLEAR);
    printf("Veuillez entrer le mot a supprimer : ");
    scanf("%s", Buffer);

    element = dic;

    while (*element){
        if (strcmp((*element)->word, Buffer) == 0){
            break;
        }
        element = &((*element)->next);
    }

    if (*element){
        printf("\n%s supprime !\n\n", (*element)->word);
        DeleteElement(element);
    } else {
        printf("\n%s introuvable !\n\n", Buffer);
    }

    clear();
    printf("Appuyer sur une touche pour revenir a menu principal\n");
    getchar();
}

void FreeDic(dictionary** dic){
    while (*dic){
        FreeDic(&((*dic)->next));
        DeleteElement(dic);
    }
}

dictionary* loadDicFromFile(const char* filename){
    dictionary* dic;
    dictionary** LastEntry;
    FILE* filePointer;
    int fileSize;
    char* data;
    char* dataPointer;
    int Start, End;
    int i;
    int nbOfSym;

    // Allocate memory for the dictionary
    dic = malloc(sizeof(dictionary));
    if (!dic) {
        goto Error;
    }
    memset(&dic, 0, sizeof(dictionary));

    // Open the dictionary file
    filePointer = fopen(filename, "rb");
    if (!filePointer) {
        goto Error;
    }

    // Get the file size
    fseek(filePointer, 0, SEEK_END);
    fileSize = ftell(filePointer);
    rewind(filePointer);

    // Alocate memory to load the file into
    data = (char*)malloc(sizeof(char)*(fileSize + 1));
    data[fileSize] = '\0';

    // Load the file into memory
    if (fread(data, 1, fileSize, filePointer) != fileSize){
        goto Error;
    }

    dataPointer = data;
    
    // WORK
    
    while (dataPointer < (data + fileSize)){
        // Get Name
        End = (int)strcspn(dataPointer, " \n");
        LastEntry = DicAddEntry(&dic, subStr(dataPointer, 0, End));
        dataPointer += End + 1;

        // Get Nb of syn
        End = (int)strcspn(dataPointer, " \n");
        nbOfSym = atoi(subStr(dataPointer, 0, End));
        dataPointer += End + 1;

        // Boucle get syn
        for (i = 0; i < nbOfSym; i++){
            End = (int)strcspn(dataPointer, " \n");
            DicAddSym(*LastEntry, subStr(dataPointer, 0, End));
            dataPointer += End + 1;
        }
    }

    free(data);
    fclose(filePointer);

    return dic;

Error:
    if (filePointer){
        fclose(filePointer);
    }
    if (dic){
        FreeDic(&dic);
    }
    return NULL;
}

void saveDicToFile(dictionary* dic, char* filename){
    symlist* sym;
    FILE* filePointer;

    // Open the dictionary file
    filePointer = fopen(filename, "w");
    if (!filePointer) {
        goto Exit;
    }

    while (dic){
        fprintf(filePointer, "%s %d", dic->word, dic->nbOfSym);
        sym = dic->sym;
        while (sym){
            fprintf(filePointer, " %s", sym->word);
            sym = sym->next;
        }
        fprintf(filePointer, "\n");
        dic = dic->next;
    }

Exit:
    if (filePointer){
        fclose(filePointer);
    }
}