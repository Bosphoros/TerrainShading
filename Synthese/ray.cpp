#include "ray.h"
#include <cmath>
#include <iostream>
#include <QTime>

Ray::Ray(const Vector3D &o, const Vector3D &d):origine(o),direction(d.normalized())
{
}

bool Ray::intersects(const Vector3D &a, const Vector3D &b, const Vector3D &c, Vector3D &out) const
{
    // Vecteurs du plan
    Vector3D u(a - c);
    Vector3D v(b - c);

    // Normale au plan
    Vector3D w =u^v;//Vector3D::crossProduct(u, v);

    // Produit scalaire, si 0 pas de solution ou une infinité
    double scalaire = direction*w;
    if(abs(scalaire) < 0.0001)
        return false;
    double delta = a*w;
    double t = (delta - origine*w)/scalaire;

    out = getPoint(t);
    return true;

}

int Ray::intersectsBox(const Vector3D &a, const Vector3D &b, Vector3D &in, Vector3D &out) const
{
    Vector3D ax(b.x(), a.y(), a.z()); // a décalé en x
    Vector3D az(a.x(), a.y(), b.z()); // a décalé en z
    Vector3D bx(a.x(), b.y(), b.z()); // b décalé en x
    Vector3D bz(b.x(), b.y(), a.z()); // b décalé en z
    if(origine.x() > a.x() && origine.x() < b.x() && origine.y() > a.y() && origine.y() < b.y() && origine.z() > a.z() && origine.z() < b.z())
    {
        in=origine;

        if(intersects(a, az, ax, out)){ // Intersection du plan a az ax
            if(out.x() >= a.x() && out.x() <= b.x() && out.z() >= a.z() && out.z() <= b.z()){ // In da box
                return 1;
            }
        }
        if(intersects(a, az, bx, out)) { // Intersection du plan a az bx
            if(out.y() >= a.y() && out.y() <= b.y() && out.z() >= a.z() && out.z() <= b.z()){ // In da box
                return 1;
            }
        }
        if(intersects(a, ax, bz, out)){ // Intersection du plan a ax bz
            if(out.x() >= a.x() && out.x() <= b.x() && out.y() >= a.y() && out.y() <= b.y()){ // In da box
                return 1;
            }
        }
        if(intersects(b, bx, bz, out)){ // Intersection du plan b bx bz
            if(out.x() >= a.x() && out.x() <= b.x() && out.z() >= a.z() && out.z() <= b.z()){ // In da box
                return 1;
            }
        }
        if(intersects(b, bx, az, out)){ // Intersection du plan b bx az
            if(out.x() >= a.x() && out.x() <= b.x() && out.y() >= a.y() && out.y() <= b.y()){ // In da box
                return 1;
            }
        }
        if(intersects(b, bz, ax, out)){ // Intersection du plan b bz ax
            if(out.y() >= a.y() && out.y() <= b.y() && out.z() >= a.z() && out.z() <= b.z()){ // In da box
                return 1;
            }
        }

    }
    else { // Origine hors de la boite
        int resu=0;

        Vector3D aaxaz;
        Vector3D aazbx;
        Vector3D aaxbz;
        Vector3D bbxbz;
        Vector3D bbxaz;
        Vector3D bbzax;

        bool ifaaxaz = intersects(a, ax, az, aaxaz);
        bool ifaazbx = intersects(a, az, bx, aazbx);
        bool ifaaxbz = intersects(a, ax, bz, aaxbz);
        bool ifbbxbz = intersects(b, bx, bz, bbxbz);
        bool ifbbxaz = intersects(b, bx, az, bbxaz);
        bool ifbbzax = intersects(b, bz, ax, bbzax);

        if(ifaaxaz&&resu<2){ // Intersection sur le plan a ax az et pas encore deux points d'entrée/sortie
            if(aaxaz.x() >= a.x() && aaxaz.x() <= b.x() && aaxaz.z() >= a.z() && aaxaz.z() <= b.z()){ // In da box
                if(resu==0){
                    in=aaxaz;
                    ++resu;
                }
                else{
                    if(resu==1&&aaxaz.distanceToPoint(in)>0.001){
                        out=aaxaz;
                        ++resu;
                    }
                }
            }
        }
        if(ifaazbx&&resu<2){ // Intersection sur le plan a az bx et pas encore deux points d'entrée/sortie
            if(aazbx.y() >= a.y() && aazbx.y() <= b.y() && aazbx.z() >= a.z() && aazbx.z() <= b.z()){ // In da box
                if(resu==0){
                    in=aazbx;
                    ++resu;
                }
                else{
                    if(resu==1&&aazbx.distanceToPoint(in)>0.001){
                        out=aazbx;
                        ++resu;
                    }
                }
            }
        }
        if(ifaaxbz&&resu<2){ // Intersection sur le plan a ax bz et pas encore deux points d'entrée/sortie
            if(aaxbz.x() >= a.x() && aaxbz.x() <= b.x() && aaxbz.y() >= a.y() && aaxbz.y() <= b.y()){ // In da box
                if(resu==0){
                    in=aaxbz;
                    ++resu;
                }
                else{
                    if(resu==1&&aaxbz.distanceToPoint(in)>0.001){
                        out=aaxbz;
                        ++resu;
                    }
                }
            }
        }
        if(ifbbxbz&&resu<2){ // Intersection sur le plan b bx bz et pas encore deux points d'entrée/sortie
            if(bbxbz.x() >= a.x() && bbxbz.x() <= b.x() && bbxbz.z() >= a.z() && bbxbz.z() <= b.z()){ // In da box
                if(resu==0){
                    in=bbxbz;
                    ++resu;
                }
                else{
                    if(resu==1&&bbxbz.distanceToPoint(in)>0.001){
                        out=bbxbz;
                        ++resu;
                    }
                }
            }
        }
        if(ifbbxaz&&resu<2){ // Intersection sur le plan b bx az et pas encore deux points d'entrée/sortie
            if(bbxaz.x() >= a.x() && bbxaz.x() <= b.x() && bbxaz.y() >= a.y() && bbxaz.y() <= b.y()){ // In da box
                if(resu==0){
                    in=bbxaz;
                    ++resu;
                }
                else{
                    if(resu==1&&bbxaz.distanceToPoint(in)>0.001){
                        out=bbxaz;
                        ++resu;
                    }
                }
            }
        }
        if(ifbbzax&&resu<2){ // Intersection sur le plan b bz ax et pas encore deux points d'entrée/sortie
            if(bbzax.y() >= a.y() && bbzax.y() <= b.y() && bbzax.z() >= a.z() && bbzax.z() <= b.z()){ // In da box
                if(resu==0){
                    in=bbzax;
                    ++resu;
                }
                else{
                    if(resu==1&&bbzax.distanceToPoint(in)>0.001){
                        out=bbzax;
                        ++resu;
                    }
                }
            }
        }

        if(resu < 2) // Passe hors de la boite ou sur une arrête
        {
            return 0;
        }

        if(origine.distanceToPointSquared(in) > origine.distanceToPointSquared(out)) // Inversion si les deux points trouvés ne l'ont pas été dans le bon ordre
        {
            Vector3D tmp = in;
            in = out;
            out = tmp;
        }

        return 2;

    }
}

