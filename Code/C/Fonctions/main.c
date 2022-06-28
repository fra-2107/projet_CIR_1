#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");

    char methodeList[3][10] = {"Euler", "EulerAsy", "RK2"};

    for(int k=0; k<3; k++){

        char path[30];
        sprintf(path, "../Data/%s.json", methodeList[k]);

        for(int i=0; i<NB_ASTRE; i++){

            planetList[i].trajectoire = malloc(NB_REPERE * sizeof(Point));
            planetList[i].trajectoire[0] = firstPoint(planetList[i]);

            planetList[i] = ChooseMethode(methodeList[k], planetList[i], NB_REPERE, PAS_MERCURE);   
        }

        writeForMethode(planetList, methodeList[k], path);

        DeltaConservationEnergie(planetList, 0, NB_REPERE-1, methodeList[k]);
    }    

    return 0;
}

