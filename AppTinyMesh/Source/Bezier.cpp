#include "Bezier.h"

Vector Bezier::val(const double& u) const{
    Vector p(0);
    int n = controle.size();
    B ber;
    for(int i = 0; i<n; i++){
        p+=controle[i]*ber.val(n-1, i, u);
    }

    return p;
}

void Bezier::draw(QGraphicsScene& s, const QPen& p) const{

    for(size_t i = 0; i<controle.size(); i++){
        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(controle[i][0], controle[i][1], 4, 4);
        ellipse->setPen(p);
        s.addItem(ellipse);
    }

    for (size_t i = 0; i < 100-1; ++i) {
        // Dessiner des segments entre les points successifs
        Vector vi1 = val(static_cast<double>(i) / 100);    // Correct
        Vector vi2 = val(static_cast<double>(i + 1) / 100); // Correct

        s.addLine(vi1[0], vi1[1], vi2[0], vi2[1],QPen(Qt::blue, 4));
    }
}


Vector Bezier3D::Value(const double& u, const double& v) const{
    int n = ptsControles.size()- 1;
    int m = ptsControles[0].size() -1;
    Vector val(0);
    B ber;
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=m; j++){
            val+=ptsControles[i][j] * ber.val(n, i, u) * ber.val(m, j, v);
        }

    }

    return val;
}

Vector Bezier3D::Normal(const double& u, const double& v) const{
    int n = ptsControles.size() - 1;
    int m = ptsControles[0].size() - 1;
    Vector pU(0);
    B ber;
    for(int i = 0; i<=n-1; i++){
        for(int j = 0; j<=m; j++){
            pU+=n*(ptsControles[i+1][j]- ptsControles[i][j]) * ber.val(n-1, i, u) * ber.val(m, j, v);
        }

    }
    Vector pV(0);
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=m-1; j++){
            pV+=m*(ptsControles[i][j+1]- ptsControles[i][j]) * ber.val(n, i, u) * ber.val(m-1, j, v);
        }

    }


    return pU/pV;
}
