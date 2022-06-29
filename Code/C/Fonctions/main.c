#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");

    char methodeList[NB_METHODE][NB_CHAR_MAX] = {"Euler", "EulerAsy", "RK2"};
    // int nb_point_trajectoire = NB_REPERE;

    for(int k=0; k<NB_METHODE; k++){

        char path[TAILLE_MAX];
        sprintf(path, "../Data/%s.json", methodeList[k]);

        for(int i=0; i<NB_ASTRE; i++){

            planetList[i].trajectoire = malloc(NB_REPERE * sizeof(Point));
            planetList[i].trajectoire[0] = firstPoint(planetList[i]);

            planetList[i] = CalculTrajectoire(methodeList[k], planetList[i], NB_REPERE, DELTA_T);   
        }

        writeForMethode(planetList, methodeList[k], path);

        DeltaConservationEnergie(planetList, 0, NB_REPERE-1, methodeList[k]);
    }    

    // affichageInfoPoint(planetList[2].trajectoire[99]);
    // printf("%d: %f\n", NB_REPERE-1, realTime(NB_REPERE-1));

    return 0;
}

