#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NB_CHAR_MAX 10
#define NB_ASTRE 8
#define TAILLE_MAX 100
#define G 6.67408e-11
<<<<<<< HEAD
#define NB_REPERE 1000000
=======
#define NB_REPERE 36500
>>>>>>> TEST
#define PAS_MERCURE 8640
#define MASSE_SOLEIL 1.989100e+30

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
    double periodicite;
    int nb_point;
    int deltaT;
} Planet;


/* VECTEURS */
void affichageVect(Vector vect);

//Opération sur les vecteurs
Vector additionVect(Vector a, Vector b);
Vector soustractionVect(Vector a, Vector b);
Vector scalaireVect(double k, Vector vect);
double normeVect(Vector vect);
void vectorTest();


/* PLANETS */
Planet *InitPlanet(char *filename);
Planet *recupInfo(FILE *fichier, char *filename, Planet *planetList);
void affichageInfoPlanets(Planet *planetList);
void InfoPlanet(Planet planet);
void affichageTrajectoirePlanet(Planet planet);
Planet resetZ(Planet planet);


/* FILES */
FILE *readFile(char *filename);
FILE *writeFile(char *filename);
// void SaveData(Planet planet, char *methode, FILE* fichier);
void SaveData(Planet planet, char *methode, FILE* fichier);
FILE *addToFile(char *filename);


/* POINTS */
Point firstPoint(Planet planet);
double vitessePerihelie(Planet planet);
void affichageInfoPoint(Point point);
void infoPoint(Point point, FILE *fichier);
Planet Euler(Planet planet);
Vector calculAcceleration(Planet planet, int indice);
Planet MethodEuler(Planet planet, int nbPoint, int deltaTemps);
Planet MethodeEulerAsymetrique(Planet planet, int nbPoint, int deltaTemps);