#include "trajectoireAstre.h"

void affichageVect(Vector vect){
    
    printf("| %e |\n", vect.x);
    printf("| %e |\n", vect.y);
    printf("| %e |\n\n", vect.z);
}

Vector additionVect(Vector a, Vector b){
    Vector newVect = {a.x + b.x, a.y + b.y, a.z + b.z};
    return newVect;
}

Vector soustractionVect(Vector a, Vector b){
    Vector newVect = {a.x - b.x, a.y - b.y, a.z - b.z};
    return newVect;
}

Vector scalaireVect(double k, Vector vect){
    Vector newVect = {k*vect.x, k*vect.y, k*vect.z};
    return newVect;
}

double normeVect(Vector vect){
    return sqrt(vect.x*vect.x + vect.y*vect.y + vect.z*vect.z);
}

void vectorTest(){
    Vector a = {5,-2,0};
    Vector b = {4,5,0};
    double k = 5;

    printf("vect a:\n");
    affichageVect(a);
    printf("vect b:\n");
    affichageVect(b);

    printf("a + b:\n");
    affichageVect(additionVect(a,b));
    printf("a - b:\n");
    affichageVect(soustractionVect(a,b));
    printf("%f scalaire de a:\n",k);
    affichageVect(scalaireVect(k,a));
    printf("||a||:\t%f\n",normeVect(a));
    printf("||b||:\t%f\n",normeVect(b));
}