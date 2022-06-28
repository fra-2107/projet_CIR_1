#include "trajectoireAstre.h"

void affichageVect(Vector vect){
    /*
        Permet d'afficher les coordonnées d'un vecteur
    */
    
    printf("| %e |\n", vect.x);
    printf("| %e |\n", vect.y);
    printf("| %e |\n\n", vect.z);
}

Vector additionVect(Vector a, Vector b){
    /*
        Retourne la somme de deux vecteurs
    */

    Vector newVect = {a.x + b.x, a.y + b.y, a.z + b.z};
    return newVect;
}

Vector soustractionVect(Vector a, Vector b){
    /*
        Retourne la soustraction de deux vecteurs
    */

    Vector newVect = {a.x - b.x, a.y - b.y, a.z - b.z};
    return newVect;
}

Vector scalaireVect(double k, Vector vect){
    /*
        Retourne le scalaire d'un nombre et d'un vecteur
    */

    Vector newVect = {k*vect.x, k*vect.y, k*vect.z};
    return newVect;
}

Vector divisionVect(double k, Vector vect){
    /*
        Retourne la division d'un vecteur par un nombre
    */

    Vector newVect = {vect.x/k, vect.y/k, vect.z/k};
    return newVect;
}

double normeVect(Vector vect){
    /*
        Retourne la norme d'un vecteur
    */

    return sqrt(vect.x*vect.x + vect.y*vect.y + vect.z*vect.z);
}

void vectorTest(){
    /*
        Test les différentes opérations d'un vecteur
    */

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