#include "trajectoireAstre.h"

Point firstPoint(Planet planet){

    planet.trajectoire[0].temps = 0;

    planet.trajectoire[0].position.x = planet.perihelie;
    planet.trajectoire[0].position.y = 0;

    planet.trajectoire[0].vitesse.x = 0;
    planet.trajectoire[0].vitesse.y = vitessePerihelie(planet);

    return planet.trajectoire[0];
}

double vitessePerihelie(Planet planet){
    // double Vperihelie = sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));
    return sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));;
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

    // printf("debut methode EULER\n");

    for (int i = 1; i < nbPoint; i++){

        planet.trajectoire[i].acceleration = scalaireVect(- (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[i-1].position),3), planet.trajectoire[i-1].position);
        // printf("acceleration ok\n");

        planet.trajectoire[i].position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i-1].vitesse.x * deltaTemps;
        planet.trajectoire[i].position.y = planet.trajectoire[i-1].position.y + planet.trajectoire[i-1].vitesse.y * deltaTemps;
        // printf("position ok\n");

        planet.trajectoire[i].vitesse.x = planet.trajectoire[i-1].vitesse.x + planet.trajectoire[i].acceleration.x * deltaTemps;
        planet.trajectoire[i].vitesse.y = planet.trajectoire[i-1].vitesse.y + planet.trajectoire[i].acceleration.y * deltaTemps;
        // printf("vitesse ok\n");

        planet.trajectoire[i].temps = i;
    }
    // printf("fin methode EULER\n");
    return planet;
}

Planet MethodeEulerAsymetrique(Planet planet, int nbPoint, int deltaTemps){

    for (int i = 1; i < nbPoint; i++){

        planet.trajectoire[i].position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i-1].vitesse.x * deltaTemps;
        planet.trajectoire[i].position.y = planet.trajectoire[i-1].position.y + planet.trajectoire[i-1].vitesse.y * deltaTemps;

        planet.trajectoire[i].acceleration = scalaireVect(- (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[i].position),3), planet.trajectoire[i].position);

        planet.trajectoire[i].vitesse.x = planet.trajectoire[i-1].vitesse.x + planet.trajectoire[i].acceleration.x * deltaTemps;
        planet.trajectoire[i].vitesse.y = planet.trajectoire[i-1].vitesse.y + planet.trajectoire[i].acceleration.y * deltaTemps;

        planet.trajectoire[i].temps = i;
    }

    return planet;
}

Planet MethodeRungeKutta(Planet planet, int nbPoint, int deltaTemps){

        for(int i=1; i<nbPoint; i++){
            Point k1;
            k1.position = scalaireVect(deltaTemps, planet.trajectoire[i-1].vitesse);
            k1.vitesse = scalaireVect(- deltaTemps * ((G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[i-1].position),3)), planet.trajectoire[i-1].position);

            Point k2;
            k2.position = scalaireVect( deltaTemps, (additionVect(planet.trajectoire[i-1].vitesse, divisionVect(2, k1.vitesse))));
            k2.vitesse = scalaireVect( -deltaTemps*((G*MASSE_SOLEIL)/pow(normeVect(additionVect(planet.trajectoire[i-1].position, divisionVect(2, k1.position))), 3)), additionVect(planet.trajectoire[i-1].position, divisionVect(2, k1.position)));

            planet.trajectoire[i].position = additionVect(planet.trajectoire[i-1].position, k2.position);
            planet.trajectoire[i].vitesse = additionVect(planet.trajectoire[i-1].vitesse, k2.vitesse);
        }

    return planet;
}


Planet resetZ(Planet planet){

    for(int i=0; i<NB_REPERE; i++){
        planet.trajectoire[i].temps = i;
        planet.trajectoire[i].position.z = 0;
        planet.trajectoire[i].vitesse.z = 0;
        // planet.trajectoire[i].acceleration.x = 0;
        // planet.trajectoire[i].acceleration.y = 0;
        // planet.trajectoire[i].acceleration.z = 0;
    }

    return planet;
}