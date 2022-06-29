#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");

    char methodeList[NB_METHODE][NB_CHAR_MAX] = {"Euler", "EulerAsy", "RK2"};
    int nb_point_trajectoire = NB_REPERE;
    int deltaT = DELTA_T;

    for(int k=0; k<NB_METHODE; k++){

        char path[TAILLE_MAX];
        sprintf(path, "../Data/%s.json", methodeList[k]);

        for(int i=0; i<NB_ASTRE; i++){

            planetList[i].trajectoire = malloc(nb_point_trajectoire * sizeof(Point));
            planetList[i].trajectoire[0] = firstPoint(planetList[i]);

            planetList[i] = CalculTrajectoire(methodeList[k], planetList[i], nb_point_trajectoire, deltaT);   
        }

        writeForMethode(planetList, methodeList[k], path);

        DeltaConservationEnergie(planetList, 0, nb_point_trajectoire-1, methodeList[k]);
    }    

    return 0;
}

