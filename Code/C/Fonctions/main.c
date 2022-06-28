#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");
    printf("planetes initialisée\n");
    
    for(int i=0; i<NB_ASTRE; i++) verifConservationEnergie(planetList[i]);
    // affichageInfoPlanets(planetList);  
    // affichageTrajectoirePlanet(planetList[0]);

    return 0;
}

