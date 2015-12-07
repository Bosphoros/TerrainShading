#include "terrainimage.h"
#include <QColor>
#include <iostream>
#include <cmath>


TerrainImage::TerrainImage(const QImage& i, double bl, double no, const Vector2D& a, const Vector2D& b):Terrain(a,b), blanc(bl), noir(no)
{

    h=i.height();
    w=i.width();
    mat.resize(h*w);
    for(int j=0;j<h;j++){
        for(int k=0;k<w;k++){
            QRgb p=i.pixel(k,h-j-1);
            quint8 c=(quint8)qGray(p);
            mat[k+w*j] = c;
        }
    }

}

double TerrainImage::getHauteur(const Vector2D &p) const
{
    Vector2D pTmp=p-a;
    pTmp.setX(pTmp.x()/(b.x()-a.x()));
    pTmp.setY(pTmp.y()/(b.y()-a.y()));
    double u=pTmp.x();
    double v=pTmp.y();
    double rx = (u*(w-1));
    double ry=(v*(h-1));
    int i =(int) rx;
    rx-=i;
    int j = (int) ry;
    ry -= j;

    if(i<0||j<0||i>w-1||j>h-1){
        return 0;
    }

    double z=(1-rx)*(1-ry)*((double)mat[j*w+i])+
                rx*(1-ry)*((double)mat[j*w+i+1])+
                (1-rx)*ry*((double)mat[(j+1)*w+i])+
                rx*ry*((double)mat[(j+1)*w+i+1]);

    return noir +(z*(blanc-noir)/255.0);
}



double TerrainImage::getPenteMax() const
{

    double pasx=(b.x()-a.x())/w;
    double pasy=(b.y()-a.y())/h;
    double max=0;
    for(int i=0;i<h-1;i++){
        for(int j=0;j<w-1;j++){
            double tmp=abs((int)(mat[i*w+j])-(int)(mat[(i+1)*w+j]))/pasy;
            if(max<tmp){
                max=tmp;
            }
            tmp=abs((int)(mat[i*w+j])-(int)(mat[i*w+j+1]))/pasx;
            if(max<tmp){
                max=tmp;
            }
        }
    }
    return max;
}
