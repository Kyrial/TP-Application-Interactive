#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
class Transform
{
public:
    Transform(){
        s=QVector3D();
        r= QQuaternion();
        t = QVector3D();
    }
    Transform(QVector3D sc, QQuaternion ro, QVector3D tr){
        s = sc;
        r = ro;
        t = tr;
    };

    /*QMatrix4x4 getMatrix(){

        return s*r*t;


    }*/




private:
   //QMatrix3x3 m; // rotation + skew + scale





   QVector3D s; //uniform scale
   QQuaternion r; // rotation
   QVector3D t; // translation




protected:

    //QVector4D apply( QVector4D p); //p is in affine coords
    QVector3D applyToPoint( QVector3D p);
    QVector3D applyToVector( QVector3D v);
    QVector3D applyToVersor( QVector3D v);

    Transform combine_with( Transform & t);
    Transform inverse();
    Transform interpolate_with( Transform &t, QVector3D k);

    Transform mix_with(Transform b, float k){
       Transform result;
       result.s = this->s * k + b.s * (1-k);
       //result.r = this->r . mix_with(b.r, k);
       result.r = this->r * b.r;
       result.t = this->t * k + b.t * (1-k);
       return result;
    }
    //echelle translation rotation


    QVector4D apply( QVector4D p);


    void setRotation( QVector3D & v, float f){
        r = QQuaternion::fromAxisAndAngle(v,f);
    }

    void setScale( QVector3D v){
        s = v;
    }
    void setTranslate( QVector3D v){
        t = v;
    }



};
#endif // TRANSFORM_H


//gameobject : liste enfant, pointeur parent
