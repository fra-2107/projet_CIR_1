#include "trajectoireAstre.h"

FILE *readFile(char *filename){

    FILE *fichier = NULL;

    fichier = fopen(filename,"r"); 

    if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}

