#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("infoAstre.txt");
    // affichageInfoPlanets(planetList);    

    // Planet Mercure = planetList[1];

    // for(int i=0; i<NB_REPERE; i++){
    //     printf("\n\t\t%s point[%d]:\n",Mercure.name, i);
    //     infoPoint(Mercure.trajectoire[i]);
    // }

    FILE *fichier = writeFile("mercury-euler.json");
    SaveData(planetList[1], "euler", fichier);

    return 0;
}

