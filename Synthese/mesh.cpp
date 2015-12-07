#include "mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh &m):geom(m.geom),norm(m.norm),topo(m.topo),nom(m.nom)
{

}

Mesh::Mesh(const QList<Vector3D> &v, const QList<int> &t, const QList<Vector3D> &n, const QString &no):geom(v),topo(t),norm(n),nom(no)
{

}

void Mesh::translate(const Vector3D &t)
{
    QList<Vector3D>::iterator itv=geom.begin();
        for(;itv!=geom.end();++itv){
            (*itv)+=t;
        }
}

void Mesh::rotate(const QMatrix3x3 &mat)
{
    QList<Vector3D>::iterator itv=geom.begin();
        for(;itv!=geom.end();++itv){
            double x=(*itv).x()*mat(0,0)+(*itv).y()*mat(0,1)+(*itv).z()*mat(0,2);
            double y=(*itv).x()*mat(1,0)+(*itv).y()*mat(1,1)+(*itv).z()*mat(1,2);
            double z=(*itv).x()*mat(2,0)+(*itv).y()*mat(2,1)+(*itv).z()*mat(2,2);
            (*itv).setX(x);
            (*itv).setY(y);
            (*itv).setZ(z);
        }
}

void Mesh::homotecie(const Vector3D &c, double h)
{
    QList<Vector3D>::iterator itv=geom.begin();
        for(;itv!=geom.end();++itv){
            (*itv)=(((*itv)-c)*h)+c;
        }
}

void Mesh::merge(const Mesh &mesh)
{
    QList<int> posv;
        QList<int> posn;
        for(int i=0;i<mesh.geom.size();i++){
            int n=containsGeom(mesh.geom[i]);
            if(n==-1){
                n=geom.size();
                geom.append(mesh.geom[i]);
            }
            posv.append(n);
        }

        for(int i=0;i<mesh.norm.size();i++){
            int n=containsNorm(mesh.norm[i]);
            if(n==-1){
                n=norm.size();
                norm.append(mesh.norm[i]);
            }
            posn.append(n);
        }
        for(int i=0;i<mesh.topo.size();i+=3){
            topo.append(posv[mesh.topo[i]]);
            topo.append(0);
            topo.append(posn[mesh.topo[i+2]]);
        }
}

int Mesh::containsGeom(const Vector3D &g)
{
    return geom.indexOf(g);
}

int Mesh::containsNorm(const Vector3D &n)
{
    return norm.indexOf(n);
}

const QList<Vector3D> &Mesh::getGeom() const{
    return geom;
}

const QList<Vector3D> &Mesh::getNorm() const{
    return norm;
}

const QList<int> &Mesh::getTopo() const{
    return topo;
}

const QString &Mesh::getNom() const
{
    return nom;
}

Mesh::~Mesh()
{

}
