#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NB_CHAR_MAX 10

typedef struct Vector{
    double x;
    double y;
    double z;
} Vector;

typedef struct Point{
    Vector position;
    Vector vitesse;
    int temps;
} Point;

typedef struct Trajectoire{
    Point *liste;
} Trajectoire;

typedef struct Planet{
    char name[NB_CHAR_MAX];
    double masse;
    Trajectoire trajectoire;
    double perihelie;   //distance min séparant un astre du Soleil
} Planet;

/* VECTEURS */
void affichageVect(Vector vect);

//Opération sur les vecteurs
Vector additionVect(Vector a, Vector b);
Vector soustractionVect(Vector a, Vector b);
Vector scalaireVect(double k, Vector vect);
double normeVect(Vector vect);
void vectorTest();