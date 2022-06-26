#include "trajectoireAstre.h"

Point firstPoint(Planet planet){

    printf("first 1\n");
    planet.trajectoire[0].temps = 0;

    planet.trajectoire[0].position.x = planet.perihelie;
    planet.trajectoire[0].position.y = 0;
    planet.trajectoire[0].position.z = 0;
    printf("first 2\n");

    planet.trajectoire[0].vitesse.x = 0;
    printf("first 2.2\n");
    planet.trajectoire[0].vitesse.y = vitessePerihelie(planet);
    printf("first 2.3\n");
    planet.trajectoire[0].vitesse.z = 0;
    printf("first finis\n");

    // Vector acceleration = calculAcceleration(planet, 0);

    // planet.trajectoire[0].acceleration.x = acceleration.x;
    // planet.trajectoire[0].acceleration.y = acceleration.y;
    // planet.trajectoire[0].acceleration.z = acceleration.z;

    // printf("norme vecteur accélération: %e m/s\n",normeVect(acceleration));

    // infoPoint(planet.trajectoire[0]);

    return planet.trajectoire[0];
}

double vitessePerihelie(Planet planet){
    printf("debut calcul vitesse\n");
    double Vperihelie = sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));
    printf("vitesse calculé\n");
    return Vperihelie;
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


Planet Euler(Planet planet){
    int t = PAS;

    for(int i=1; i<NB_REPERE; i++){
        planet.trajectoire[i].position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i].vitesse.x * t;
        planet.trajectoire[i].vitesse.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i].acceleration.x * t; 

        t += PAS;
    }
    return planet;
}

Vector calculAcceleration(Planet planet, int indice){
    // double acceleration = - (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[indice].position),3);
    
    Vector acceleration = scalaireVect(- (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[indice].position),3), planet.trajectoire[indice].position);

    // printf("Vect acceleration [%d]:\n",indice);
    // affichageVect(acceleration);

    Point point = planet.trajectoire[indice];

    acceleration.x = (point.position.x / normeVect(point.position)) * normeVect(acceleration);
    acceleration.y = (point.position.y / normeVect(point.position)) * normeVect(acceleration);    
    acceleration.z = (point.position.z / normeVect(point.position)) * normeVect(acceleration);

    // printf("Ax: %e\n",acceleration.x);
    // printf("Ay: %e\n",acceleration.y);
    // printf("Az: %e\n",acceleration.z);

    return acceleration;
}


Planet MethodEuler(Planet planet){

    // printf("%s:\n",planet.name);
    // printf("Point 0: \nPos x: %e, y: %e, z: %e\nVitesse x: %e, y: %e, z: %e\n", planet.trajectoire[0].position.x, planet.trajectoire[0].position.y, planet.trajectoire[0].position.z, planet.trajectoire[0].vitesse.x, planet.trajectoire[0].vitesse.y, planet.trajectoire[0].vitesse.z);
    //On effectue une boucle pour chaque points de la planète

    // printf("%s:\t", planet.name);

    for (int i = 1; i < NB_REPERE; i+= PAS){
        // printf("%d\n",i);   

        Point point = planet.trajectoire[i];

        point.acceleration = calculAcceleration(planet, i-1);

        point.position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i-1].vitesse.x * PAS;
        point.position.y = planet.trajectoire[i-1].position.y + planet.trajectoire[i-1].vitesse.y * PAS;
        point.position.z = planet.trajectoire[i-1].position.z + planet.trajectoire[i-1].vitesse.z * PAS;

        point.vitesse.x = planet.trajectoire[i-1].vitesse.x + point.acceleration.x * PAS;
        point.vitesse.y = planet.trajectoire[i-1].vitesse.y + point.acceleration.y * PAS;
        point.vitesse.z = planet.trajectoire[i-1].vitesse.z + point.acceleration.z * PAS;

        point.temps = i;
        planet.trajectoire[i] = point;
    }
    // printf("Trajectoire établit\n\n");
    return planet;
}