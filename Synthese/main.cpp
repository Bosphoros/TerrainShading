#include "terrainimage.h"
#include <iostream>
#include "terraintest.h"
#include "ray.h"
#include <QTime>
#include "camera.h"
#include "terrainnoisesmultiples.h"
#include <vector>
#include "meshbuilder.h"
#include "matrix3.h"
#define M_PI 3.14159265358979323846

Terrain* generationImage(const QString& img){
    Vector2D a(0,0);
    Vector2D b(1000,1000);
    QImage im;
    im.load(img);
    return new TerrainImage(im,80,-120,a,b);
}

Terrain* generationProcedural(){
    Vector2D a(0,0);
    Vector2D b(1000,1000);
    return new TerrainTest(a,b);
}

void shoot(Terrain* const t, const QString& img){
    Vector3D o(-3400, -2200, 2800);
    float z=t->getHauteur(Vector2D(500,300))+40;
    //Vector3D o(500,300,z);
    Vector3D d(1,1,-1);


    Vector3D soleil(100000000,0,0);
    QMatrix3x3 mat1;
    mat1(0,0)=cos(-M_PI*3/4);
    mat1(0,1)=0;
    mat1(0,2)=sin(-M_PI*3/4);
    mat1(1,0)=0;
    mat1(1,1)=1;
    mat1(1,2)=0;
    mat1(2,0)=-sin(-M_PI*3/4);
    mat1(2,1)=0;
    mat1(2,2)=cos(-M_PI*3/4);
    soleil.rotate(mat1);

    Vector3D dirCam(500,500,z);
    Vector3D dist(o+d);
    Camera cam(o, dirCam, o.distanceToPoint(dist)*4);
    QImage result = cam.printScreen(t,soleil,192*10,108*10);
    result.save(img);
}

void shootMulti(Terrain* const t, const QString& img, int nbShoot){
    Vector3D o(-3400, -2200, 2800);

    Vector3D soleil(100000000,0,0);

    Vector3D dirCam(500,500,0);

    QMatrix3x3 mat;
        mat(0,0)=cos(2*M_PI/nbShoot);
        mat(0,1)=-sin(2*M_PI/nbShoot);
        mat(0,2)=0;
        mat(1,0)=sin(2*M_PI/nbShoot);
        mat(1,1)=cos(2*M_PI/nbShoot);
        mat(1,2)=0;
        mat(2,0)=0;
        mat(2,1)=0;
        mat(2,2)=1;

    QMatrix3x3 matcam;
        matcam(0,0)=cos(2*M_PI/nbShoot);
        matcam(0,1)=0;
        matcam(0,2)=sin(2*M_PI/nbShoot);
        matcam(1,0)=0;
        matcam(1,1)=1;
        matcam(1,2)=0;
        matcam(2,0)=-sin(2*M_PI/nbShoot);
        matcam(2,1)=0;
        matcam(2,2)=cos(2*M_PI/nbShoot);


    for(int i=0; i<nbShoot;++i){

        float z=t->getHauteur(Vector2D(500,300+i))+40;
        float z1=t->getHauteur(Vector2D(500,400))+5;
        o=Vector3D(500,300+i,z);

        dirCam=Vector3D (500,400,z1);

        Camera cam(o, dirCam, 6.92820);
        soleil.rotate(mat);
        //o.rotate(matcam);
        QImage result = cam.printScreen(t,soleil,192*2,108*2);
        QString nameImage =img;
        nameImage+=std::to_string(i).c_str();
        nameImage+=".png";
        result.save(nameImage);
        std::cerr<<"\r"<<100.0*(i+1)/nbShoot<<"%";
    }
}

void generateMesh(Terrain* const t,const QString& obj,int echantillion){

    MeshBuilder bu;
    QString nom="terrain";
    Mesh m =bu.terrain(*t,echantillion,nom);
    bu.saveMesh(obj,m);

}

int main(int argc, char *argv[])
{
    int arg=1;
    QTime time;//*/

    /*time.restart();
    QString img=argv[arg++];
    Terrain* t=generationImage(img);
    std::cout << "Terrain from image generated : " << time.restart() << "ms." << std::endl;//*/

    time.restart();
    Terrain* t=generationProcedural();
    std::cout << "Terrain generated : " << time.restart() << "ms." << std::endl;
     //*/


    /*time.restart();
    QString obj=argv[arg++];
    generateMesh(t,obj,300);
    std::cout << "Mesh generated : " << time.restart() << "ms." << std::endl;//*/

    time.restart();
    QString destination=argv[arg++];
    shoot(t,destination);
    std::cout << "Image generated from ray launching : " << time.restart() << "ms." << std::endl;//*/

    /*time.restart();
    QString destination=argv[arg++];

    shootMulti(t,destination,100);
    std::cout << "100 images generated from ray launching : " << time.restart() << "ms." << std::endl;//*/

    //delete t;

    /*QList<Vector3D> points = Vector3D::randSphere(1000);
        QList<Vector3D> points2 = Vector3D::scaleTranslate(points, Vector3D(3,4,-8), 2.6);
        QList<int> topo;
        QList<Vector3D> normales;
        Mesh m1(points, topo, normales, "ololo");
        Mesh m2(points2, topo, normales, "ololo2");

        MeshBuilder m;
        m.saveMesh("m1.obj", m1);
        m.saveMesh("m3.obj", m2);*/

    /*float tab[9] = {1,0,0,
                    0,1,0,
                    1,0,1};
    Matrix3 mat(tab);
    Matrix3 result = mat * mat;
    cout << result;
    */
   return 0;
}
