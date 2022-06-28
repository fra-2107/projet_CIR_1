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


FILE *writeFile(char *filename){
    FILE *fichier = NULL;

    fichier = fopen(filename,"w+");

     if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}


FILE *addToFile(char *filename){
    FILE *fichier = NULL;

    fichier = fopen(filename,"a+");

     if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}


void SaveData(Planet planet, char *methode, FILE* fichier){
   
    char guillemet = '"';

    fprintf(fichier, "%c%s-%s%c : [", guillemet, planet.name, methode, guillemet);
    // printf("debut save %s\n",planet.name);
    for(int i=0; i<NB_REPERE; i++){
        // printf("i: %d\n", i );
        infoPoint(planet.trajectoire[i], fichier);
        
    }
    // printf("%s save\n",planet.name);
    // fprintf(fichier, "}\n");

}

void writeForMethode(Planet *planetList, char *methode, char *filename){

    FILE *fichier = writeFile(filename);

    fprintf(fichier, "{");

    for(int i=0; i<NB_ASTRE; i++){
        // printf("i: %d\n",i);
        // planetList[i] = ChooseMethode( methode, planetList[i], NB_REPERE, PAS_MERCURE);
        // printf("trajectoire etablie pour %s\n", planetList[i].name);
        if(i == NB_ASTRE-1){
            SaveData(planetList[i], methode, fichier);
            fprintf(fichier, "}\n");
        }else{
            SaveData(planetList[i], methode, fichier);
            fprintf(fichier, ",\n");
        } 
        // printf("%s save\n", planetList[i].name);
    }

    fclose(fichier);
}