#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("infoAstre.txt");

    affichageInfoPlanets(planetList);    

    return 0;
}