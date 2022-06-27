#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");
    // affichageInfoPlanets(planetList);    
    printf("planetes initialisée\n");

    // affichageTrajectoirePlanet(planetList[0]);

    // planetList[0] = resetZ(planetList[0]);

    // printf("coord acc en z de mercure:\n");
    // affichageInfoPoint(planetList[0].trajectoire[0]);

    // affichageVect(planetList[0].trajectoire[0].acceleration);

    // affichageInfoPoint(planetList[0].trajectoire[1]);

    return 0;
}

