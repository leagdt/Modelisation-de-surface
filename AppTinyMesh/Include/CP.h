#ifndef CP_H
#define CP_H
#include <vector>
#include <iostream>

#include "mathematics.h"
#include "mesh.h"

// classe qui définit une courbe parametrée
class CP{
protected:

public:
    // Retourne la valeur en u
    virtual Vector val(const double& u) const{ return Vector(0); }
    // Retourne la tangente en u de la courbe
    virtual Vector T(const double& u, const double& epsilon = 0.01) const{
        return (val(u+epsilon)-val(u-epsilon))/(2*epsilon);
    }
    // Retourne la vitesse de la courbe en u
    virtual double vitesse(const double& u) const{return Norm(T(u)); }
    // retourne le résultat de la double dérivée
    virtual Vector doubleDerivee(const double& u, const double& epsilon = 0.01){
        return (val(u-epsilon)+val(u+epsilon)-2*val(u))/(epsilon*epsilon);
    }
    // Retourne le vecteur normal à la courbe
    virtual Vector normal(const double& u){
        return Normalized(T(u))/Normalized(T(u).Orthogonal());
    }

};

class SurfaceParam{
protected:

public:
    SurfaceParam(){}

    virtual Vector Value(const double&, const double&) const = 0;
    virtual Vector Normal(const double&, const double&) const = 0;
    virtual void Polygonize(int, int, Mesh&) const;
};

#endif // CP_H
