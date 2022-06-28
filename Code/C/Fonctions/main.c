#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");
    
    
    DeltaConservationEnergie(planetList, 0, NB_REPERE-1, "Euler");
    DeltaConservationEnergie(planetList, 0, NB_REPERE-1, "EulerAsy");
    DeltaConservationEnergie(planetList, 0, NB_REPERE-1, "RK2");

    return 0;
}

