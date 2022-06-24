#include "trajectoireAstre.h"

Point firstPoint(Planet planet){

    planet.trajectoire[0].temps = 0;

    planet.trajectoire[0].position.x = planet.perihelie;
    planet.trajectoire[0].position.y = 0;
    planet.trajectoire[0].position.z = 0;

    planet.trajectoire[0].vitesse.x = 0;
    planet.trajectoire[0].vitesse.y = vitessePerihelie(planet);
    planet.trajectoire[0].vitesse.z = 0;

    // Vector acceleration = calculAcceleration(planet, 0);

    // planet.trajectoire[0].acceleration.x = acceleration.x;
    // planet.trajectoire[0].acceleration.y = acceleration.y;
    // planet.trajectoire[0].acceleration.z = acceleration.z;

    // printf("norme vecteur accélération: %e m/s\n",normeVect(acceleration));

    // infoPoint(planet.trajectoire[0]);

    return planet.trajectoire[0];
}

double vitessePerihelie(Planet planet){
    double Vperihelie = sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));

    return Vperihelie;
}

void infoPoint(Point point){
    printf("\nInformation du point au temps [%d]:\n",point.temps);
    printf("position:\t[%e\t%e\t%e]\n",point.position.x, point.position.y, point.position.z);
    printf("vitesse:\t[%e\t%e\t%e]\n",point.vitesse.x, point.vitesse.y, point.vitesse.z);
    printf("accélération:\t[%e\t%e\t%e]\n\n",point.acceleration.x, point.acceleration.y, point.acceleration.z);
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

    printf("%s:\n", planet.name);

    for (int i = 1; i < NB_REPERE; i+= PAS){
        // printf("%d\n",i);   

        Point point = planet.trajectoire[i];

        // printf("\nPoint i: %d\nPos x: %e, y: %e, z: %e\nVitesse x: %e, y: %e, z: %e\n", i-1,  planet.trajectoire[i-1].position.x, planet.trajectoire[i-1].position.y, planet.trajectoire[i-1].position.z, planet.trajectoire[i-1].vitesse.x, planet.trajectoire[i-1].vitesse.y, planet.trajectoire[i-1].vitesse.z);
        //1) Calcul de l'accélération
        //2) Calcul de la position au point i
        //3) Calcul de la vitesse au point i
        
        // double a =  (- G * MASSE_SOLEIL) / (pow(vectorNorm(planete->trajectoire.file[i-1].r),3));
        // double ax = a * (planete->trajectoire.file[i-1].r.x / vectorNorm(planete->trajectoire.file[i-1].r));
        // double ay = a * (planete->trajectoire.file[i-1].r.y / vectorNorm(planete->trajectoire.file[i-1].r));
        // printf("Acc: %e, accx: %e, accy: %e\n",a,ax,ay);

        Vector acceleration = calculAcceleration(planet, i-1);
        point.acceleration = acceleration;

        point.position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i-1].vitesse.x * PAS;
        point.position.y = planet.trajectoire[i-1].position.y + planet.trajectoire[i-1].vitesse.y * PAS;
        point.position.z = planet.trajectoire[i-1].position.z + planet.trajectoire[i-1].vitesse.z * PAS;
        // Vector pos = vectorInit(x, y, 0);

        point.vitesse.x = planet.trajectoire[i-1].vitesse.x + acceleration.x * PAS;
        point.vitesse.y = planet.trajectoire[i-1].vitesse.y + acceleration.y * PAS;
        point.vitesse.z = planet.trajectoire[i-1].vitesse.z + acceleration.z * PAS;
        // Vector vit = vectorInit(vx, vy, 0);

        // Point newPoint = pointInit(pos,vit,i);
        // planete->trajectoire.file[i] = newPoint;
        point.temps = i;

        planet.trajectoire[i] = point;
    }
    printf("Trajectoire établit\n\n");
    return planet;
}