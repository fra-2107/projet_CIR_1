#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NB_CHAR_MAX 10
#define NB_ASTRE 8
#define TAILLE_MAX 100
#define G 6.67408e-11
#define NB_REPERE 600000+1 //3653
#define DELTA_T 8640
#define MASSE_SOLEIL 1.989100e+30
#define NB_METHODE 3

typedef struct Vector{
    double x;
    double y;
    double z;
} Vector;

typedef struct Point{
    Vector position;
    Vector vitesse;
    Vector acceleration;
    int temps;
} Point;

typedef struct Planet{
    char name[NB_CHAR_MAX];
    double masse;
    Point *trajectoire;
    double perihelie;   //distance min séparant un astre du Soleil
    double excentricite;
    double demi_grand_axe;

} Planet;


/* VECTEURS */
void affichageVect(Vector vect);
//Opération sur les vecteurs
Vector additionVect(Vector a, Vector b);
Vector soustractionVect(Vector a, Vector b);
Vector scalaireVect(double k, Vector vect);
Vector divisionVect(double k, Vector vect);
double normeVect(Vector vect);
void vectorTest();


/* PLANETS */
Planet *InitPlanet(char *filename);
Planet *recupInfo(FILE *fichier, char *filename, Planet *planetList);
//Affichage
void affichageInfoPlanets(Planet *planetList);
void InfoPlanet(Planet planet);
void affichageTrajectoirePlanet(Planet planet);
//Conservation de l'énergie
void DeltaConservationEnergie(Planet *planetList, int tmp1, int tmp2, char *methode);
double EnergieTotale(Planet *planetList, int temps);
double EnergiePotentielTotale(Planet *planetList, int temps);
double EnergieCinetiqueTotale(Planet *planetList, int temps);


/* FILES */
FILE *readFile(char *filename);
FILE *writeFile(char *filename);
void SaveData(Planet planet, char *methode, FILE* fichier);
void WriteInfoPoint(Point point, FILE *fichier);
FILE *addToFile(char *filename);
void writeForMethode(Planet *planetList, char *methode, char *title);


/* POINTS */
Point firstPoint(Planet planet);
Planet resetZ(Planet planet);
//Calcul
double vitessePerihelie(Planet planet);
float realTime(double tmp);
//Affichage
void affichageInfoPoint(Point point);
//METHODE DE RESOLUTION
Planet MethodEuler(Planet planet, int nbPoint, int deltaTemps);
Planet MethodeEulerAsymetrique(Planet planet, int nbPoint, int deltaTemps);
Planet MethodeRungeKutta(Planet planet, int nbPoint, int deltaTemps);
Planet CalculTrajectoire( char *choice, Planet planet, int nbPoint, int deltaTemps);