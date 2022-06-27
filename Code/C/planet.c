#include "trajectoireAstre.h"


Planet *InitPlanet(char *filename){

    // printf("Début initilisation\n");

    Planet *planetList = malloc(NB_ASTRE * sizeof(Planet));
    // printf("1\n");

    FILE *fichier = readFile(filename);
    // printf("2\n");
    planetList = recupInfo(fichier, filename, planetList);
    // affichageInfoPlanets(planetList);
    // printf("Donnée global récupérés\n");
    fclose(fichier);

    for(int i=0; i<NB_ASTRE; i++){

        char title[40]; 
        sprintf(title, "../Data/%s.json", planetList[i].name);
;
        planetList[i].trajectoire[0] = firstPoint(planetList[i]);

        planetList[i] = MethodEuler(planetList[i], NB_REPERE , PAS_MERCURE);
        planetList[i] = resetZ(planetList[i]);        

        FILE *fichier = writeFile(title);
        fprintf(fichier, "{");
        SaveData(planetList[i], "euler", fichier);
        fprintf(fichier, ",\n");
        fclose(fichier);

        planetList[i] = MethodeEulerAsymetrique(planetList[i], NB_REPERE , PAS_MERCURE);
        planetList[i] = resetZ(planetList[i]);   
        
        fichier = addToFile(title);
        SaveData(planetList[i], "eulerAsy", fichier);
        fprintf(fichier, "}\n");
        fclose(fichier);
    }

    return planetList;  
}





Planet *recupInfo(FILE *fichier, char *filename, Planet *planetList){

    // printf("Début recup\n");
    //Pour gérer différents champs dans le fichier on utilise un caractère pour les séparer
    char *separateur = ":";

    char ligne[TAILLE_MAX] = "";
    int planetID = 0;

    //On récupère ligne à ligne les informations de chaque client
    while(fgets(ligne, TAILLE_MAX, fichier)){
        Planet planet;

        char *champ = strtok(ligne, separateur);

        int num_champ = 1;
        // printf("tour %d\n", planetID);
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
                    case 6:
                        planet.periodicite = atof(champ);
                        break;
                    default:
                        break;
            }
            // printf("champ: %s\n",champ);

            //Permet de PAS_MERCUREser au champ suivant
            champ = strtok(NULL, separateur);
            num_champ++;
        }
        planetList[planetID] = planet;
        planetID++;
    }
    // printf("fin recup\n");
    return planetList;
}


void affichageTrajectoirePlanet(Planet planet){

    printf("%s\n", planet.name);
    for(int i=0; i<NB_REPERE; i++){
        printf("[%d]:\nposition: [%e, %e, %e]\nvitesse: [%e, %e, %e]\n\n", i, planet.trajectoire[i].position.x, planet.trajectoire[i].position.y, planet.trajectoire[i].position.z, planet.trajectoire[i].vitesse.x, planet.trajectoire[i].vitesse.y, planet.trajectoire[i].vitesse.z);
    }
}


void InfoPlanet(Planet planet){
    printf("NAME\t\t     MASSE\t\t   PERIHELIE\t\t1/2 GRAND AXE\t\tEXCENTRICITE\n");
    printf("%s\t\t%e kg\t\t%e m\t\t%e m\t\t%e\n",planet.name, planet.masse, planet.perihelie, planet.demi_grand_axe, planet.excentricite);
}


void affichageInfoPlanets(Planet *planetList){
    printf("\n\t\t\t\tInformation sur les astres\n\n");
    printf("NAME\t\t     MASSE\t\t   PERIHELIE\t\t1/2 GRAND AXE\t\tEXCENTRICITE\t       PERIODICITE\n");
    for(int i=0; i<NB_ASTRE; i++){
        printf("%s\t\t%e kg\t\t%e m\t\t%e m\t\t%e\t\t%.2f j\n",planetList[i].name, planetList[i].masse, planetList[i].perihelie, planetList[i].demi_grand_axe, planetList[i].excentricite, planetList[i].periodicite);
    }
}