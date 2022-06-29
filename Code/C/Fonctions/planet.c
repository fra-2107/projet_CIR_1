#include "trajectoireAstre.h"


Planet *InitPlanet(char *filename){
    /*
        Initialisation des planètes en récupérant les informations
        de chaque planètes depuis un fichier
    */

    Planet *planetList = malloc(NB_ASTRE * sizeof(Planet));

    FILE *fichier = readFile(filename);
    planetList = recupInfo(fichier, filename, planetList);
    fclose(fichier);

    return planetList;  
}


Planet *recupInfo(FILE *fichier, char *filename, Planet *planetList){
    /*
        Récupère les informartions de chaque planètes champ par champ
        afin de les stocker dans la structure Planet
    */

    //Pour gérer différents champs dans le fichier on utilise un caractère pour les séparer
    char *separateur = ":";

    char ligne[TAILLE_MAX] = "";
    int planetID = 0;

    //On récupère ligne à ligne les informations de chaque client
    while(fgets(ligne, TAILLE_MAX, fichier)){
        Planet planet;

        char *champ = strtok(ligne, separateur);

        int num_champ = 1;

        //On parcours les champs un à un
        while (champ != NULL){
        
            //Selon le numéro de champ on le récupère dans notre liste client avec le numéro du client
            switch(num_champ){
                    case 1:
                        strcpy(planet.name,champ);
                        break;
                    case 2:
                        planet.masse = atof(champ);
                        break;
                    case 3:
                        planet.perihelie = atof(champ);
                        break;
                    case 4:
                        planet.demi_grand_axe = atof(champ);
                        break;
                    case 5:
                        planet.excentricite = atof(champ);
                        break;
                    default:
                        break;
            }

            //Permet de passer au champ suivant
            champ = strtok(NULL, separateur);
            num_champ++;
        }
        planetList[planetID] = planet;
        planetID++;
    }

    return planetList;
}


void affichageTrajectoirePlanet(Planet planet){
    /*
        Affiche la trajectoire d'une planète en affichant les informations de 
        points:
            - position
            - vitesse
    */

    printf("%s\n", planet.name);

    for(int i=0; i<NB_REPERE; i++){
        printf("[%d]:\nposition: [%e, %e, %e]\nvitesse: [%e, %e, %e]\n\n", i, planet.trajectoire[i].position.x, planet.trajectoire[i].position.y, planet.trajectoire[i].position.z, planet.trajectoire[i].vitesse.x, planet.trajectoire[i].vitesse.y, planet.trajectoire[i].vitesse.z);
    }
}


void InfoPlanet(Planet planet){
    /*
        Affiche les informations d'une planète:
            - nom           - demi grand axe
            - masse         - excentricité
            - périhélie
    */

    printf("NAME\t\t     MASSE\t\t   PERIHELIE\t\t1/2 GRAND AXE\t\tEXCENTRICITE\n");
    printf("%s\t\t%e kg\t\t%e m\t\t%e m\t\t%e\n",planet.name, planet.masse, planet.perihelie, planet.demi_grand_axe, planet.excentricite);
}


void affichageInfoPlanets(Planet *planetList){
    /*
        Afficher les informations de chaque planètes
    */

    printf("\n\t\t\t\tInformation sur les astres\n\n");
    printf("NAME\t\t     MASSE\t\t   PERIHELIE\t\t1/2 GRAND AXE\t\tEXCENTRICITE\t       PERIODICITE\n");
    for(int i=0; i<NB_ASTRE; i++){
        printf("%s\t\t%e kg\t\t%e m\t\t%e m\t\t%e\n",planetList[i].name, planetList[i].masse, planetList[i].perihelie, planetList[i].demi_grand_axe, planetList[i].excentricite);
    }
}


void DeltaConservationEnergie(Planet *planetList, int tmp1, int tmp2, char *methode){
    /*
        Renvoie la différence de conservation d'énergie du sytème entre deux temps
    */

    //On met à jour la trajectoire de chaque planète en fonction de la méthode choisie
    for(int i=1; i<NB_ASTRE; i++){

        if(!strcmp(methode,"Euler")) planetList[i] = MethodEuler(planetList[i], NB_REPERE, DELTA_T);
        else if(!strcmp(methode,"EulerAsy")) planetList[i] = MethodeEulerAsymetrique(planetList[i], NB_REPERE, DELTA_T);
        else if(!strcmp(methode,"RK2")) planetList[i] = MethodeRungeKutta(planetList[i], NB_REPERE, DELTA_T);
        else{
            printf("Nom de méthode incorrect !\nVeuillez renseigner l'une des méthodes suivantes:\n\t1- Euler\n\t2- EulerAsy\n\t3- RK2\n\n");
            exit(EXIT_FAILURE);
        }
    }
    
    double E1 = EnergieTotale(planetList, tmp1);
    double E2 = EnergieTotale(planetList, tmp2);

    double delta = E1 - E2;
    float pourcentage = (delta * 100) / E1;

    printf("L'énergie totale du système a diminué de %.4f%% entre le jour %.1f et le jour %.1f avec la méthode %s\n", pourcentage, realTime(tmp1), realTime(tmp2), methode);
}


double EnergieTotale(Planet *planetList, int temps){
    /*
        Renvoie l'énergie totale obtenue avec la somme de l'énergie potentiel et de l'énergie cinétique
    */

    double E = EnergiePotentielTotale(planetList, temps) + EnergieCinetiqueTotale(planetList,temps);

    return E;
}


double EnergiePotentielTotale(Planet *planetList, int temps){
    /*
        Renvoie l'énergie potentiel totale du système à un temps choisis
    */

    double Ep = 0;

    for(int i=0; i<NB_ASTRE; i++){
        Ep += ((G * MASSE_SOLEIL * planetList[i].masse) / pow((normeVect(planetList[i].trajectoire[temps].position)), 2));
    }
    Ep *= 0.5;

    return Ep;
}


double EnergieCinetiqueTotale(Planet *planetList, int temps){
    /*
        Renvoie l'énergie cinétique totale du système à un temps choisis
    */

    double Ec = 0;

    for(int i=0; i<NB_ASTRE; i++){
        Ec += planetList[i].masse  * (pow(normeVect(planetList[i].trajectoire[temps].vitesse), 2));
    }
    Ec *= 0.5;

    return Ec;
}