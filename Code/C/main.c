#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");
    // affichageInfoPlanets(planetList);    
    printf("planetes initialisée\n");

    // Planet Mercure = planetList[1];

    // for(int i=0; i<NB_REPERE; i++){
    //     printf("\n\t\t%s point[%d]:\n",Mercure.name, i);
    //     infoPoint(Mercure.trajectoire[i]);
    // }    

    // FILE *fichier = writeFile("Data/mercury-euler.json");
    // SaveData(planetList[1], "euler", fichier);

    return 0;
}

