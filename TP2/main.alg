// Exercice 1
procedure HORAIRE(d DH, DM, DS, AH, AM, AS: entiers; r H, M, S: entiers)
    {...}

    DEPART

    // Seconds
    Si (AS < DS) alors
        SA := SA + 60
        MA := MA - 1
    Fin si

    // Minutes
    Si (AM < DM) alors
        MA := MA + 60
        HA := HA - 1
    Fin si

    // Hours
    Si (AH < DH) alors
        HA := HA + 24
    fin si

    H := AH - DH
    M := AM - DM
    S := AS - DS
fin

// Exercice 2
procedure Split(d N: entier; d T:tableau [1.....N] de reels; r nbp, nbn: entiers; r TP :tableau [1.....nbp] de type reels; r TN:tableau [1.....nbn] de type reels)
    {...}
    
    VAR i: entiers

    DEBUT

    nbp := nbn := 0
    pour i allant de 1 a N faire
        si (T[i] < 0.0) alors
            nbn := nbn + 1
            TN[nbn] := T[i]
        sinon
            nbp := nbp + 1
            TP[nbp] := T[i]
        fin si
    fin pour
fin

Soit la fonction rand(d a, b: entier) retournant un entier compris entre a et b

// Exercice 3
procedure chargement_aleatoire(d nb:entier; dr T:tableau [1.....nb] d'entiers)
    {...}

    VAR i: entier

    DEBUT
    pour i allant de 1 a nb faire
        T[i] := rand(1, 99)
    fin pour
fin

// Exercice 3
procedure tabmax_place(d n:entier; d T:tableau[1.....n] d'entiers; r max, place: entiers)
    {...}

    VAR i: entier

    DEBUT

    max := T[1]
    place := 1
    pour i allant de 2 a n faire
        si (T[i] > max) alors
            max := T[i]
            place := i
        fin si
    fin pour
fin