#include "trajectoireAstre.h"


FILE *readFile(char *filename){

    FILE *fichier = NULL;

    fichier = fopen(filename,"r"); 

    if(fichier == NULL){
        printf("Le fichier %s ne s'est PAS_MERCURE ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}


FILE *writeFile(char *filename){
    FILE *fichier = NULL;

    fichier = fopen(filename,"w+");

     if(fichier == NULL){
        printf("Le fichier %s ne s'est PAS_MERCURE ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}


void SaveData(Planet planet, char *methode, FILE* fichier){
   
    char guillemet = '"';

    fprintf(fichier, "{%c%s-%s%c : [", guillemet, planet.name, methode, guillemet);

    for(int i=0; i<NB_REPERE; i++) infoPoint(planet.trajectoire[i], fichier);
    fprintf(fichier, "}\n");

    fclose(fichier);
}