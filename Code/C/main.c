#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("infoAstre.txt");
    affichageInfoPlanets(planetList);    

    // printf("PREMIER POINT\n");
    // Point point1 = firstPoint(planetList[1]); 
    

    return 0;
}