#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "mathematics.h"
#include "implicits.h"
#include "CP.h"

const int binomial[5][5] = {{1, 0,0,0,0},
                           {1,1,0,0,0},
                           {1,2,1,0,0},
                           {1,3,3,1,0},
                           {1,4,6,4,1}};

class B{
protected:
public:
    B(){}
    double val(const int& m, const int& i,const double& x){
        return binomial[m][i] * pow(x,i)* pow(1-x, m-i);
    }
};

class Bezier : CP{
protected:
    std::vector<Vector> controle; //Permet de stocker les points de contrôle.
public:
    Bezier(const std::vector<Vector>& points) : controle(points){}
    virtual Vector val(const double& u) const;
    void draw(QGraphicsScene& s, const QPen & = QPen()) const;

};

class Bezier3D: public SurfaceParam{
protected:
    std::vector<std::vector<Vector>> ptsControles;
public:
    Bezier3D(const std::vector<std::vector<Vector>>& pts) : ptsControles(pts) {}
    Vector Normal(const double& u, const double& v) const;
    Vector Value(const double& u, const double& v) const;
};

#endif // BEZIER_H
