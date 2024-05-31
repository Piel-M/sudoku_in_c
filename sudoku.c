#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE 9

typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille g) {
    // Code pour charger la grille
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}

void afficherGrille(tGrille grille) {
    printf("     1  2  3   4  5  6   7  8  9  \n");
    printf("   +---------+---------+---------+\n");
    for (int i=0; i<TAILLE; i++){
        printf("%d  |", i+1);
        for (int l=0; l<TAILLE; l++){ //print d'une ligne
            if (l==3 || l==6){
                printf("|");
            }
            if (grille[i][l]==0){
                printf(" . ");
            } else {
                printf(" %d ", grille[i][l]);
            }
        }
        printf("|\n");
        if(i==2 || i==5 || i==8){
            printf("   +---------+---------+---------+\n");
        }
    }
}

void saisir(int *valeur) {
    char input[10];
    int num;
    bool validInput = false;

    do {
        scanf("%s", input);
        if (sscanf(input, "%d", &num) == 1 && num >= 1 && num <= 9) {
            *valeur = num;
            validInput = true;
        } else {
            printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 9 : ");
        }
    } while (!validInput);
}


//Vérifie si la grille est pleine
bool grillePleine(tGrille grille){
    bool plein=true;
    for (int i=0; i<TAILLE; i++){
        for (int l=0; l<TAILLE; l++){
            if (grille[i][l]==0){
                plein=false;
            }
        }
    }
    return plein;
}

//fonction qui vérifie si la valeur est possible dans la case tel que la ligne, la colonne et le carré ne contiennent pas déjà cette valeur
bool possible(tGrille grille, int ligne, int colonne, int valeur){
    bool possible=true;
    //vérification de la ligne
    for (int i=0; i<TAILLE; i++){
        if (grille[ligne][i]==valeur){
            possible=false;
        }
    }
    //vérification de la colonne
    for (int i=0; i<TAILLE; i++){
        if (grille[i][colonne]==valeur){
            possible=false;
        }
    }
    //vérification du carré
    int ligneCarre = ligne/3;
    int colonneCarre = colonne/3;
    for (int i=0; i<3; i++){
        for (int l=0; l<3; l++){
            if (grille[ligneCarre*3+i][colonneCarre*3+l]==valeur){
                possible=false;
            }
        }
    }
    return possible;
}


int main(){
    tGrille grille;
    int numLigne, numColonne, valeur;
    chargerGrille(grille);
    while (!grillePleine(grille)){
        afficherGrille(grille);
        printf("Indice de la ligne ? \n");
        saisir(&numLigne);
        printf("Indice de la colonne ? \n");
        saisir(&numColonne);
        if (grille[numLigne-1][numColonne-1]!=0){
            printf("Cette case est déjà remplie, vous ne pouvez pas la modifier.\n");
        } else {
            printf("Valeur à mettre dans la case ? \n");
            saisir(&valeur);
            if (possible(grille, numLigne-1, numColonne-1, valeur)){
                grille[numLigne-1][numColonne-1]=valeur;
                afficherGrille(grille);
            } else {
                printf("Cette valeur n'est pas possible dans cette case.\n");
            }
        }
    }
    printf("Bravo, vous avez gagné !\n");
    return EXIT_SUCCESS;
}