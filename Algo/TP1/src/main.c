#include "include.h" // Main include file

void clear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int cleanString(char* String){
    int i = 0;
    while (String[i] != '\0')
    {
        if (String[i] == '\n'){
            String[i] = '\0';
            return i - 1;
        }
        i++;
    }
    
}

int secureInt(char *Question, int Min){
    int retour = Min - 1;
    while (retour < Min){ // Saisie sécurisé
        system(CLEAR);
        printf("%s", Question);
        scanf("%d", &retour); clear();
    }
    return retour;
}

// Exercice 1
int OCCU(int n, double T[], double X, int I){
    if (I >= n)
        return 0;
    if (T[I] == X){
        return OCCU(n, T, X, I + 1) + 1;
    }else{
        return OCCU(n, T, X, I + 1);
    }
}

// Exercice 2
int NBM(char Chaine[], int I){
    if (Chaine[I] == '\0')
        return 0;
    if ((Chaine[I] >= 'A') && (Chaine[I] <= 'Z')){
        return NBM(Chaine, I + 1) + 1;
    }else{
        return NBM(Chaine, I + 1);
    }
}

// Exercice 3
char PALINDROME(int a, int b, char Chaine[]){
    if (a >= b)
        return 1;
    if (Chaine[a] != Chaine[b]){
        return 0;
    }else{
        return PALINDROME(a + 1, b - 1, Chaine);
    }
}

// Exercice 4
int DICHREC(int T[], int X, int inf, int sup){
    if (inf >= sup){
        if (T[inf] == X)
            return inf;
        return -1; // On a pas trouvé l'élément
    }
    int Moy = (inf + sup) / 2;
    if (X <= T[Moy]){
        return DICHREC(T, X, inf, Moy);
    }else{
        return DICHREC(T, X, Moy + 1, sup);
    }
}

// Exercice 5
int EGYPT(int a, int b){
    if (b == 0)
        return 0;
    if (b%2 != 0){
        return EGYPT(a , b - 1) + a;
    }else{
        return EGYPT(a<<1, b>>1);
    }
}

// Exercice 6
int DEPLACER(int X, int Y){
    printf("Disque déplace de la tige %d a la tige %d\n", X, Y);
}

// Exercice 6
void DRAW(int N, char A[], char B[], char C[]){
    int i;
    for (i = N - 1; i >= 0; i--){
        printf("%d | %d | %d\n", A[i], B[i], C[i]);
    }
}

// Exercice 6
// Legacy
void HANOI(int N, char A[], char B[], char C[], int Position, int Coups){ // version récuso-itérative
    char* Tabs[3];
    int i = 1, j, k;
    int Select, Sens;

    Tabs[0] = A;
    Tabs[1] = B;
    Tabs[2] = C;

    if (N%2 == 0){ // Selon si le nombre de disques est pair ou Impair, le sens de recherche s'inverse
        Sens = -1; // Pair
    }else{
        Sens = 1; // Impair
    }

    // On cherche si les deux autres tours sont des position valides
    for (i; i < 3; i++){        
        Select = Position - i * Sens; // Position de la supposé tour de destination
        if (Position > 2){ // On rectifie la position
            Position -= 3;
        }else if (Position < 0){
            Position += 3;
        }
        if (Tabs[Position][0] == 0) // Si on est sur une case vide alors il ny a pas de palet a bouger
            break;
        if (Select > 2){ // On rectifie aussi la selection
            Select -= 3;
        }else if (Select < 0){
            Select += 3;
        }
        // Recherche du palet en haut des deux tours
        for (j = 0; Tabs[Position][j] != 0 && j < N; j++); if (j != 0){j--;}
        for (k = 0; Tabs[Select][k] != 0 && k < N; k++); if (k != 0){k--;}
        // On test si on peut posser le palet sur la tour de destination
        if (Tabs[Position][j] < Tabs[Select][k] || Tabs[Select][k] == 0){
            if (Tabs[Select][k] != 0)
                k++;
            Tabs[Select][k] = Tabs[Position][j];
            Tabs[Position][j] = 0;
            DEPLACER(Position, Select); Coups++;
            DRAW(N, A, B, C);
            getchar();
            Position = Select;
            break;
        }
    }
    Position = Position + Sens; // Position du palet suivant a traiter

    if (Tabs[2][N - 1] != 1) // Condition d'arret, le traitement est fini si le disque 1 est au sommet (N - 1) de la tour 2
        HANOI(N, A, B, C, Position, Coups);
    else
        printf("Votre tour de Hanoi a ete resolue en %d coups !\n", Coups);
}

// Legacy
void HANOI2(int N, char A[], char B[], char C[], int Position, int Coups, int i){
    int Select, Sens;
    char* Tabs[3];
    int j, k;  

    Tabs[0] = A;
    Tabs[1] = B;
    Tabs[2] = C;

    if (N%2 == 0){ // Selon si le nombre de disques est pair ou Impair, le sens de recherche s'inverse
        Sens = -1; // Pair
    }else{
        Sens = 1; // Impair
    }

    // On cherche si les deux autres tours sont des position valides
    if (i < 3){
        Select = Position - i * Sens; // Position de la supposé tour de destination
        if (Position > 2){ // On rectifie la position
            Position -= 3;
        }else if (Position < 0){
            Position += 3;
        }
        if (Tabs[Position][0] != 0){ // Si on est sur une case vide alors il ny a pas de palet a bouger
            if (Select > 2){ // On rectifie aussi la selection
                Select -= 3;
            }else if (Select < 0){
                Select += 3;
            }
            // Recherche du palet en haut des deux tours
            for (j = 0; Tabs[Position][j] != 0 && j < N; j++); if (j != 0){j--;}
            for (k = 0; Tabs[Select][k] != 0 && k < N; k++); if (k != 0){k--;}
            // On test si on peut posser le palet sur la tour de destination
            if (Tabs[Position][j] < Tabs[Select][k] || Tabs[Select][k] == 0){
                if (Tabs[Select][k] != 0)
                    k++;
                Tabs[Select][k] = Tabs[Position][j];
                Tabs[Position][j] = 0;
                DEPLACER(Position, Select); Coups++;
                DRAW(N, A, B, C);
                getchar();
                Position = Select;
                i = 3;
            }
        }else{i = 3;}
        i++;
        HANOI2(N, A, B, C, Position, Coups, i); return;
    }
    i = 1;
    Position = Position + Sens; // Position du palet suivant a traiter

    if (Tabs[2][N - 1] != 1) // Condition d'arret, le traitement est fini si le disque 1 est au sommet (N - 1) de la tour 2
        HANOI2(N, A, B, C, Position, Coups, i);
    else
        printf("Votre tour de Hanoi a ete resolue en %d coups !\n", Coups);
}

void HANOI3(int N, char A, char B, char C){ // Version proprement récusive
    if (N != 0){
        // Condition
        HANOI3(N - 1, A, C, B);
        printf("N(%d) On déplace %c vers %c\n", N, A, C);
        HANOI3(N - 1, B, A, C);
    }
}

/*  BONUS
    Ecrivez un programme dans le langage C qui prend en entrée
    un horaire de départ d'un vol et un horaire de retour du même vol
    et qui retourne la durée du vol. On notera que la durée d'un vol
    ne peut dépasser les 24h
*/
time HORAIRE(time Depart, time Arrive){
    time Duree = {0};

    // Hours
    if (Arrive.Hours < Depart.Hours)
        Duree.Hours = 24;
    Duree.Hours += Arrive.Hours - Depart.Hours;

    // Minutes
    if (Arrive.Minutes < Depart.Minutes){
        Duree.Minutes = 60; Duree.Hours--;
    }
    Duree.Minutes += Arrive.Minutes - Depart.Minutes;

    // Seconds
    if (Arrive.Seconds < Depart.Seconds){
        Duree.Seconds = 60; Duree.Minutes--;
    }
    Duree.Seconds += Arrive.Seconds - Depart.Seconds;

    return Duree;
}


int main (int argc, char* argv[]){
    int ChoixExercice = 0;
    int TailleTableau = 0, TempValue = 0, TempValueB = 0, i;
    double FTempValue = 0.0;

    char String[50]; // Big Size for now

    int* DynTabEntier = NULL;
    char *TourA = NULL, *TourB = NULL, *TourC = NULL;
    double* DynTabReel = NULL;

    while (ChoixExercice < 1 || ChoixExercice > 7){ // Saisie sécurisé
        system(CLEAR);
        printf("Bienvenue dans le TP1 :\nALGORITHMIQUE ET PROGRAMMATION-INF2033\n\nVeuillez entrer le numero de l'exercice (1 - 7): ");
        scanf("%d", &ChoixExercice); clear();
    }
    printf("\n");

    time Depart = {-1, -1, -1};
    time Arrive = {-1, -1, -1};
    time Duree = {0};

    int AnotherTab[10] = {0};

    switch (ChoixExercice)
    {
    case 1:
        while (TailleTableau <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la taille du tableau a tester (1+): ");
            scanf("%d", &TailleTableau); clear();
        }
        DynTabReel = (double*)malloc(sizeof(double)*TailleTableau);
        for (i = 0; i < TailleTableau; i++){
            system(CLEAR);
            printf("Veuillez entrer la valeur N°%d/%d: ", i + 1, TailleTableau);
            while (scanf("%lf", &DynTabReel[i]) != 1){ // Saisie sécurisé      
                clear();
            }
        }
        system(CLEAR);
        printf("Veuillez entrer la valeur a chercher : ");
        while (scanf("%lf", &FTempValue) != 1){ // Saisie sécurisé      
            clear();
        }
        printf("\n%lf apparait dans le tableau %d fois\n", FTempValue, OCCU(TailleTableau, DynTabReel, FTempValue, 0));
        free(DynTabReel);
        break;
    case 2:
        system(CLEAR);
        printf("Veuillez entrer la chaine de caractère a tester : ");
        fgets(String, 50, stdin);
        cleanString(String);
        printf("Number of CAPS letters in %s = %d\n", String, NBM(String, 0));
        break;
    case 3:
        system(CLEAR);
        printf("Veuillez entrer la chaine de caractère a tester : ");
        fgets(String, 50, stdin);
        if (PALINDROME(0, cleanString(String), String)){
            printf("%s est un palindrome\n", String);
        }else{
            printf("%s n'est pas un palindrome\n", String);
        }
        break;
    case 4:
        system(CLEAR);
        for (i = 0; i < 10; i++){
            system(CLEAR);
            printf("Veuillez entrer la valeur N°%d/10 (Par ordre croissant): ", i + 1);
            while (scanf("%d", &AnotherTab[i]) != 1){ // Saisie sécurisé      
                clear();
            }
        }
        system(CLEAR);
        printf("Soit le tableau statique : \n");
        for (i = 0; i < 10; i++){
            printf("%d ", AnotherTab[i]);
        }
        printf("\n\nVeuillez entrer la valeur a rechercher dans le tableau statique : ");
        while (scanf("%d", &TempValue) != 1){ // Saisie sécurisé      
            clear();
        }
        printf("L'indice de %d dans le tableau statique est = %d\n", TempValue, DICHREC(AnotherTab, TempValue, 0, 9));
        sleep(3);

        while (TailleTableau <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la taille du tableau dynamique a tester (1+): ");
            scanf("%d", &TailleTableau); clear();
        }
        DynTabEntier = (int*)malloc(sizeof(int)*TailleTableau);
        for (i = 0; i < TailleTableau; i++){
            system(CLEAR);
            printf("Veuillez entrer la valeur N°%d/%d (Par ordre croissant): ", i + 1, TailleTableau);
            while (scanf("%d", &DynTabEntier[i]) != 1){ // Saisie sécurisé      
                clear();
            }
        }
        system(CLEAR);
        printf("Soit le tableau dynamique : \n");
        for (i = 0; i < TailleTableau; i++){
            printf("%d ", DynTabEntier[i]);
        }
        printf("\n\nVeuillez entrer la valeur a rechercher dans le tableau dynamique : ");
        while (scanf("%d", &TempValue) != 1){ // Saisie sécurisé      
            clear();
        }
        printf("L'indice de %d dans le tableau dynamique est = %d\n", TempValue, DICHREC(DynTabEntier, TempValue, 0, TailleTableau - 1));
        break;
    case 5:
        system(CLEAR);
        printf("Veuillez entrer la premiere valeur a multiplier : ");
        while (scanf("%d", &TempValue) != 1){ // Saisie sécurisé      
            clear();
        }
        system(CLEAR);
        printf("Veuillez entrer la seconde valeur a multiplier : ");
        while (scanf("%d", &TempValueB) != 1){ // Saisie sécurisé      
            clear();
        }
        printf("%d * %d = %d\n",TempValue, TempValueB, EGYPT(TempValue, TempValueB));
        break;
    case 6:
        system(CLEAR);
        while (TailleTableau <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la taille des tours de Hanoi a tester (1+): ");
            scanf("%d", &TailleTableau); clear();
        }
        //TourA = (char*)malloc(sizeof(char)*TailleTableau); for (i = 0; i < TailleTableau; i++){TourA[i] = TailleTableau - i;};
        //TourB = (char*)calloc(TailleTableau, sizeof(char));
        //TourC = (char*)calloc(TailleTableau, sizeof(char));
        //HANOI2(TailleTableau, TourA, TourB, TourC, 0, 0, 1);
        HANOI3(TailleTableau, '1', '2', '3');
        //free(TourA); free(TourB); free(TourC);
        break;
    case 7:
        Depart.Hours = secureInt("Heure de depart (0+): ", 0);
        Depart.Minutes = secureInt("Minutes de depart (0+): ", 0);
        Depart.Seconds = secureInt("Secondes de depart (0+): ", 0);

        Arrive.Hours = secureInt("Heure d'Arrive (0+): ", 0);
        Arrive.Minutes = secureInt("Minutes d'Arrive (0+): ", 0);
        Arrive.Seconds = secureInt("Secondes d'Arrive (0+): ", 0);

        Duree = HORAIRE(Depart, Arrive);
        printf("Durée : %dh%dm%ds\n", Duree.Hours, Duree.Minutes, Duree.Seconds);
        break;
    }
    

    return 0;
}