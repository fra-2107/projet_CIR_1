#include "trajectoireAstre.h"

Point firstPoint(Planet planet){

    planet.trajectoire[0].temps = 0;

    planet.trajectoire[0].position.x = planet.perihelie;
    planet.trajectoire[0].position.y = 0;
    planet.trajectoire[0].position.z = 0;

    planet.trajectoire[0].vitesse.x = 0;
    planet.trajectoire[0].vitesse.y = vitessePerihelie(planet);
    planet.trajectoire[0].vitesse.z = 0;

    // infoPoint(planet.trajectoire[0]);

    return planet.trajectoire[0];
}

double vitessePerihelie(Planet planet){
    double Vperihelie = sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));
    // printf("vitesse perihelie de %s: %e m/s\n",planet.name, vitessePerihelie(planet));

    return Vperihelie;
}

void infoPoint(Point point){
    printf("Information du point au temps [%d]:\n",point.temps);
    printf("position: [%e\t%e\t%e]\n",point.position.x, point.position.y, point.position.z);
    printf("vitesse: [%e\t%e\t%e]\n\n",point.vitesse.x, point.vitesse.y, point.vitesse.z);
}