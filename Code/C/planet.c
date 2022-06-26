#include "trajectoireAstre.h"


Planet *InitPlanet(char *filename){

    Planet *planetList = malloc(NB_ASTRE * sizeof(Planet));

    FILE *fichier = readFile(filename);
    planetList = recupInfo(fichier, filename,planetList);
    fclose(fichier);

    for(int i=0; i<NB_ASTRE; i++){
        planetList[i].trajectoire[0] = firstPoint(planetList[i]);
        // printf("%s:\n", planetList[i].name);
        // infoPoint(planetList[i].trajectoire[0]);

        planetList[i] = MethodEuler(planetList[i]);

        char title[40];
        sprintf(title, "Data/%s-euler.json", planetList[i].name);
        // puts(title);

        // printf("titre: %s\n", title);

        FILE *fichier = writeFile(title);
        SaveData(planetList[1], "euler", fichier);
    }

    return planetList;  
}


Planet *recupInfo(FILE *fichier, char *filename, Planet *planetList){

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
                    case 4:
                        planet.demi_grand_axe = atof(champ);
                        break;
                    case 5:
                        planet.excentricite = atof(champ);
                        break;
                    default:
                        break;
            }
            // printf("champ: %s\n",champ);

            //Permet de passer au champ suivant
            champ = strtok(NULL, separateur);
            num_champ++;
        }
        planetList[planetID] = planet;
        planetID++;
    }
    return planetList;
}

void InfoPlanet(Planet planet){
    printf("NAME\t\t     MASSE\t\t   PERIHELIE\t\t1/2 GRAND AXE\t\tEXCENTRICITE\n");
    printf("%s\t\t%e kg\t\t%e m\t\t%e m\t\t%e\n",planet.name, planet.masse, planet.perihelie, planet.demi_grand_axe, planet.excentricite);
}


void affichageInfoPlanets(Planet *planetList){
    printf("\n\t\t\t\tInformation sur les astres\n\n");
    printf("NAME\t\t     MASSE\t\t   PERIHELIE\t\t1/2 GRAND AXE\t\tEXCENTRICITE\n");
    for(int i=0; i<NB_ASTRE; i++){
        printf("%s\t\t%e kg\t\t%e m\t\t%e m\t\t%e\n",planetList[i].name, planetList[i].masse, planetList[i].perihelie, planetList[i].demi_grand_axe, planetList[i].excentricite);
    }
}