#ifndef _DIC_H
#define _DIC_H

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct symlist symlist;
typedef struct dictionary dictionary;

void clear();
dictionary* loadDicFromFile(const char* filename);
void listDic(dictionary* dic);
void AddWordToDictionary(dictionary** dic);
char* ToDynStr(const char* TEXT);
void SearchWordInDic(dictionary* dic);
void DeleteWordInDic(dictionary** dic);
void FreeDic(dictionary** dic);
void saveDicToFile(dictionary* dic, char* filename);

#endif