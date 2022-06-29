#include "trajectoireAstre.h"


FILE *readFile(char *filename){
    /*
        Ouvre et retourne un fichier en mode lecture
    */

    FILE *fichier = NULL;

    fichier = fopen(filename,"r"); 

    if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}


FILE *writeFile(char *filename){
    /*
        Ouvre et retourne un fichier en mode écriture
        Si le fichier existe déjà il sera écrasé 
        Sinon il sera créé
    */

    FILE *fichier = NULL;

    fichier = fopen(filename,"w+");

     if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}


FILE *addToFile(char *filename){
    /*
        Ouvre et retourne un fichier en mode écriture
        Ajoute des caractères dans le fichier sans modifier contenu initial
    */

    FILE *fichier = NULL;

    fichier = fopen(filename,"a+");

     if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    return fichier;
}

void WriteInfoPoint(Point point, FILE *fichier){
    /*
        Ecrit les informations d'un point dans le fichier
    */

    if(point.temps == NB_REPERE-1) fprintf(fichier, "[[%e, %e, %e],[%e, %e, %e], %d]]\n", point.position.x, point.position.y, point.position.z, point.vitesse.x, point.vitesse.y, point.vitesse.z, point.temps);
    else fprintf(fichier, "[[%e, %e, %e],[%e, %e, %e], %d],\n", point.position.x, point.position.y, point.position.z, point.vitesse.x, point.vitesse.y, point.vitesse.z, point.temps);
}


void SaveData(Planet planet, char *methode, FILE* fichier){
    /*
        Ecrit dans le fichier les valeurs de la trajectoire 
        point par point
    */
   
    char guillemet = '"';

    fprintf(fichier, "%c%s-%s%c : [", guillemet, planet.name, methode, guillemet);

    for(int i=0; i<NB_REPERE; i++) WriteInfoPoint(planet.trajectoire[i], fichier);
}


void writeForMethode(Planet *planetList, char *methode, char *filename){
    /*
        Ecrit un même fichier la trajectoire de plusieurs planètes 
        avec la même méthode
    */

    FILE *fichier = writeFile(filename);

    fprintf(fichier, "{");

    for(int i=0; i<NB_ASTRE; i++){

        if(i == NB_ASTRE-1){
            SaveData(planetList[i], methode, fichier);
            fprintf(fichier, "}\n");
        }else{
            SaveData(planetList[i], methode, fichier);
            fprintf(fichier, ",\n");
        } 
    }

    fclose(fichier);
}