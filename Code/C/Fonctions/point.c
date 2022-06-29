#include "trajectoireAstre.h"

Point firstPoint(Planet planet){
    /*
        Initialise le premier point de la trajectoire d'une planète:
            - temps à 0
            - position obtenue par la distance périhélie sur l'axe X
            - vitesse obtenue par la vitesse au périhélie sur l'axe Y
    */

    planet.trajectoire[0].temps = 0;

    planet.trajectoire[0].position.x = planet.perihelie;
    planet.trajectoire[0].position.y = 0;

    planet.trajectoire[0].vitesse.x = 0;
    planet.trajectoire[0].vitesse.y = vitessePerihelie(planet);

    return planet.trajectoire[0];
}

double vitessePerihelie(Planet planet){
    /*
        Renvoi la vitesse au périhélie d'une planète en fonction de son 
        excentricité et de son demi grand axe
    */

    return sqrt((G*MASSE_SOLEIL*(1+planet.excentricite))/(planet.demi_grand_axe*(1-planet.excentricite)));;
}


Planet resetZ(Planet planet){
    /*
        Permet de corriger certains bugs en assignant la valeur 0 à la coordonnée en Z
    */

    for(int i=0; i<NB_REPERE+1; i++){
        planet.trajectoire[i].temps = i;
        planet.trajectoire[i].position.z = 0;
        planet.trajectoire[i].vitesse.z = 0;
        planet.trajectoire[i].acceleration.z = 0;
    }

    return planet;
}

float realTime(double tmp){
    /*
        Renvoie le temps réel en jours en fonction de la 
        valeur du deltaT
    */

    float day = (tmp * DELTA_T) / (24 * 3600);

    return day;
}


void affichageInfoPoint(Point point){
    /*
        Affiche les informations d'un point:
            - position
            - vitesse
            - accélération
    */

    float day = realTime(point.temps);
    printf("\nInformation du point[%d] au bout du %.2f jours:\n",point.temps, day);
    printf("position:\t[%e\t%e\t%e]\n",point.position.x, point.position.y, point.position.z);
    printf("vitesse:\t[%e\t%e\t%e]\n",point.vitesse.x, point.vitesse.y, point.vitesse.z);
    printf("accélération:\t[%e\t%e\t%e]\n\n",point.acceleration.x, point.acceleration.y, point.acceleration.z);
}


Planet MethodEuler(Planet planet, int nbPoint, int deltaTemps){
    /*
        Méthode de calcul permettant de trouver apromaxivement les solutions d'une
        équation différentielle en se basant sur un système de résolution par récurrence  
    */

    for (int i = 1; i < nbPoint; i++){

        planet.trajectoire[i].acceleration = scalaireVect(- (G * MASSE_SOLEIL) / pow(normeVect(planet.trajectoire[i-1].position),3), planet.trajectoire[i-1].position);

        planet.trajectoire[i].position.x = planet.trajectoire[i-1].position.x + planet.trajectoire[i-1].vitesse.x * deltaTemps;
        planet.trajectoire[i].position.y = planet.trajectoire[i-1].position.y + planet.trajectoire[i-1].vitesse.y * deltaTemps;

        planet.trajectoire[i].vitesse.x = planet.trajectoire[i-1].vitesse.x + planet.trajectoire[i].acceleration.x * deltaTemps;
        planet.trajectoire[i].vitesse.y = planet.trajectoire[i-1].vitesse.y + planet.trajectoire[i].acceleration.y * deltaTemps;

        planet.trajectoire[i].temps = i;
    }

    return planet;
}

Planet MethodeEulerAsymetrique(Planet planet, int nbPoint, int deltaTemps){
    /*
        Méthode de calcul permettant de trouver appromaxivement les solutions d'une
        équation différentielle en se basant sur un système de résolution par récurrence
        Méthode plus fiable que Euler  
    */

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
    /*
        Méthode d'analyse numérique permettant de trouver approximativement des solutions 
        d'équations différentielles. C'est la méthode la plus précise des 3 et ne dépend pas de l'accélération
        d'un point.
        On peut augment la précision de RK en augmentant de l'ordre 2 à 4.
    */

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


Planet CalculTrajectoire( char *choice, Planet planet, int nbPoint, int deltaTemps){
    /*
        Calcul la trajectoire d'une planète en fonction de la méthode choisie
    */

    if(!strcmp(choice,"Euler")) planet = MethodEuler(planet, nbPoint, deltaTemps);
    else if(!strcmp(choice,"EulerAsy")) planet = MethodeEulerAsymetrique(planet, nbPoint, deltaTemps);
    else if(!strcmp(choice,"RK2")) planet = MethodeRungeKutta(planet, nbPoint, deltaTemps);
    else{
        printf("Nom de méthode incorrect !\nVeuillez renseigner l'une des méthodes suivantes:\n\t1- Euler\n\t2- EulerAsy\n\t3- RK2\n\n");
        exit(EXIT_FAILURE);
    }

    planet = resetZ(planet);

    return planet;
}