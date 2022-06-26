#include "trajectoireAstre.h"

int main(){

    // vectorTest();
    Planet *planetList = InitPlanet("Data/infoAstre.json");
<<<<<<< HEAD
    printf("Planete initialisé dans 'Data/'\n");
=======
>>>>>>> TEST
    // affichageInfoPlanets(planetList);    
    printf("planetes initialisée\n");

    // affichageTrajectoirePlanet(planetList[0]);

    // planetList[0] = resetZ(planetList[0]);

<<<<<<< HEAD
    // FILE *fichier = writeFile("mercury-euler.json");
    // SaveData(planetList[1], "euler", fichier);

    
=======
    // printf("coord acc en z de mercure:\n");
    // affichageInfoPoint(planetList[0].trajectoire[0]);

    // affichageVect(planetList[0].trajectoire[0].acceleration);

    // affichageInfoPoint(planetList[0].trajectoire[1]);
>>>>>>> TEST

    return 0;
}

