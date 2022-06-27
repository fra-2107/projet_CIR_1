#include "trajectoireAstre.h"

Point firstPoint(Planet planet){
    // printf("Debut first point\n");
    planet.trajectoire[0].temps = 0;
    // printf("1\n");
    planet.trajectoire[0].position.x = planet.perihelie;
    planet.trajectoire[0].position.y = 0;
    // planet.trajectoire[0].position.z = 0;
    // printf("2\n");
    planet.trajectoire[0].vitesse.x = 0;
    // printf("2.2\n");
    // printf("test: %f\n",planet.trajectoire[0].vitesse.y);
    planet.trajectoire[0].vitesse.y = vitessePerihelie(planet);


    // planet.trajectoire[0].vitesse.y = sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));
    // planet.trajectoire[0].vitesse.z = 0;
    // printf("3\n");
    return planet.trajectoire[0];
}

double vitessePerihelie(Planet planet){
    // printf("Début calcul vitesse\n");
    double Vperihelie = sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));
    // printf("vitesse perihelie calculé\n");
    return Vperihelie;
    // return 1.0;
}


void affichageInfoPoint(Point point){
    printf("\nInformation du point au temps [%d]:\n",point.temps);
    printf("position:\t[%e\t%e\t%e]\n",point.position.x, point.position.y, point.position.z);
    printf("vitesse:\t[%e\t%e\t%e]\n",point.vitesse.x, point.vitesse.y, point.vitesse.z);
    printf("accélération:\t[%e\t%e\t%e]\n\n",point.acceleration.x, point.acceleration.y, point.acceleration.z);
}


void infoPoint(Point point, FILE *fichier){
    if(point.temps == NB_REPERE-1) fprintf(fichier, "[[%e, %e, %e],[%e, %e, %e], %d]]\n", point.position.x, point.position.y, point.position.z, point.vitesse.x, point.vitesse.y, point.vitesse.z, point.temps);
    else fprintf(fichier, "[[%e, %e, %e],[%e, %e, %e], %d],\n", point.position.x, point.position.y, point.position.z, point.vitesse.x, point.vitesse.y, point.vitesse.z, point.temps);
}


Vector calculAcceleration(Planet planet, int indice){
    
    Vector acceleration = scalaireVect(- (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[indice].position),3), planet.trajectoire[indice].position);

    return acceleration;
}


Planet MethodEuler(Planet planet, int nbPoint, int deltaTemps){
    int tmp = 1;

    // printf("%s nb points: %d\n",planet.name, nbPoint);
    for (int i = 1; i < nbPoint; i++){
        // printf("indice: %d\n",i);   

        // point.acceleration = calculAcceleration(planet, i-1);
        planet.trajectoire[i].acceleration = scalaireVect(- (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[i-1].position),3), planet.trajectoire[i-1].position);

        planet.trajectoire[i].position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i-1].vitesse.x * deltaTemps;
        planet.trajectoire[i].position.y = planet.trajectoire[i-1].position.y + planet.trajectoire[i-1].vitesse.y * deltaTemps;
        // point.position.z = 0;
        planet.trajectoire[i].vitesse.x = planet.trajectoire[i-1].vitesse.x + planet.trajectoire[i].acceleration.x * deltaTemps;
        planet.trajectoire[i].vitesse.y = planet.trajectoire[i-1].vitesse.y + planet.trajectoire[i].acceleration.y * deltaTemps;
        // point.vitesse.z = 0;

        planet.trajectoire[i].temps = tmp;

        // planet.trajectoire[i] = point;
        // affichageInfoPoint(planet.trajectoire[i]);
        tmp++;
    }
    // printf("Trajectoire établit\n\n");
    return planet;
}

Planet resetZ(Planet planet){

    for(int i=0; i<NB_REPERE; i++){
        planet.trajectoire[i].temps = i;
        planet.trajectoire[i].position.z = 0;
        planet.trajectoire[i].vitesse.z = 0;
        planet.trajectoire[i].acceleration.x = 0;
        planet.trajectoire[i].acceleration.y = 0;
        planet.trajectoire[i].acceleration.z = 0;

        // affichageInfoPoint(planet.trajectoire[i]);
    }

    return planet;
}