#include "CP.h"

void SurfaceParam::Polygonize(int n, int m, Mesh& g) const{

    std::vector<Vector> vertices;
    vertices.reserve(n*m);
    std::vector<Vector> normals;
    normals.reserve(n*m);
    std::vector<int> faces;
    faces.reserve(n*m); //todo revoir quelle taille allouer
    for(int i =0; i<n; i++){
        for(int j = 0; j<m; j++){
            double u = static_cast<double>(i)/static_cast<double>(n-1);
            double v = static_cast<double>(j)/static_cast<double>(m-1);
            vertices.push_back(Value(u, v));
        }
    }
    for(int i =0; i<n; i++){
        for(int j = 0; j<m; j++){
            double u = static_cast<double>(i)/static_cast<double>(n-1);
            double v = static_cast<double>(j)/static_cast<double>(m-1);
            normals.push_back(Normal(u,v));
        }
    }
    for(int i =0; i<n-1; i++){
        for(int j = 0; j<m-1; j++){
            faces.push_back(i*n+j);
            faces.push_back((i+1)*n+j);
            faces.push_back((i+1)*n+j+1);

            faces.push_back(i*n+j);
            faces.push_back((i+1)*n+j+1);
            faces.push_back(i*n+j+1);
        }
    }

    std::vector<int> normal = faces;
    g = Mesh(vertices, normals, faces, normal);
}
