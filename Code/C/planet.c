#include "trajectoireAstre.h"

Planet *InitPlanet(char *filename){
    Planet *planetList = malloc(NB_ASTRE * sizeof(Planet));

    planetList = recupInfo(filename,planetList);
    // for(int i=0; i<NB_ASTRE; i++){
    //     planetList[i] = recupInfo(filename);
    // }

    return planetList;  
}

Planet *recupInfo(char *filename, Planet *planetList){

    FILE *fichier = NULL;
    
    fichier = fopen(filename,"r"); 

    if(fichier == NULL){
        printf("Le fichier %s ne s'est pas ouvert\n",filename);
        exit(-1);
    }

    //Pour gérer différents champs dans le fichier on utilise un caractère pour les séparer
    char *separateur = ":";
    
    char ligne[TAILLE_MAX] = "";
    int planetID = 0;

    //On récupère ligne à ligne les informations de chaque client
    while(fgets(ligne, TAILLE_MAX, fichier)){
        Planet planet;

        char *champ = strtok(ligne, separateur);

        int num_champ = 1;

        //On parcours les champs un à un
        while (champ != NULL){
        
            //Selon le numéro de champ on le récupère dans notre liste client avec le numéro du client
            switch(num_champ){
                    case 1:
                        strcpy(planet.name,champ);
                        break;
                    case 2:
                        planet.masse = atof(champ);
                        break;
                    case 3:
                        planet.perihelie = atof(champ);
                        break;
                    default:
                        break;
            }
            printf("champ: %s\n",champ);

            //Permet de passer au champ suivant
            champ = strtok(NULL, separateur);
            num_champ++;
        }
        planetList[planetID] = planet;
        planetID++;

    }
    return planetList;
}

void affichageInfoPlanets(Planet *planetList){
    printf("Information sur les astres\n\n");
    printf("NAME\t\t     MASSE\t\t   PERIHELIE\n");
    for(int i=0; i<NB_ASTRE; i++){
        printf("%s\t\t%e kg\t\t%e km\n",planetList[i].name, planetList[i].masse, planetList[i].perihelie);
    }
}