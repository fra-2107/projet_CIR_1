#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("infoAstre.txt");
    // affichageInfoPlanets(planetList);    

    // infoPoint(planetList[1].trajectoire[1]);

    // Vector acc = calculAcceleration(planetList[1], 0);

    Planet Mercure = planetList[1];


    for(int i=0; i<NB_REPERE; i++){
        printf("\n\t\t%s point[%d]:\n",Mercure.name, i);
        infoPoint(Mercure.trajectoire[i]);
    }

    return 0;
}