#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>

//a faire:
//inversion
//combinaision


class Transform
{
public:
    Transform(){
        s=QVector3D(1,1,1);
        r= QQuaternion();
        t = QVector3D();
    }
    Transform(QVector3D sc, QQuaternion ro, QVector3D tr){
        s = sc;
        r = ro;
        t = tr;
    };

    QMatrix4x4 doTransformation(){
         QMatrix4x4 a= QMatrix4x4 ();
         a = doTranslate(doRotate(doScale(a)));
         return a;
    }

    QMatrix4x4 doAnimation(Transform* anim, double deltaTime){
        Transform a =combine_with(*anim, deltaTime);
        this->setScale(a.s);
        this->setRotation(a.r);
        this->setTranslate(a.t);
        QMatrix4x4 res = this->doTransformation();
        return res;

    }


    void setRotation( QVector3D & v, float f){
        r = QQuaternion::fromAxisAndAngle(v,f);
    }
    void setRotation(float x,float y,float z, float f){
        r = QQuaternion::fromAxisAndAngle(QVector3D(x,y,z),f);
    }
    void setRotation(QQuaternion q){
        r = q;
    }

    void setScale( QVector3D v){
        s = v;
    }
    void setScale( float x, float y, float z){
        s = QVector3D(x,y,z);
    }

    void setTranslate( QVector3D v){
        t = v;
    }
    void setTranslate( float x, float y, float z){
        t = QVector3D(x,y,z);
    }
private:
   //QMatrix3x3 m; // rotation + skew + scale





   QVector3D s; //uniform scale
   QQuaternion r; // rotation
   QVector3D t; // translation




protected:

    //QVector4D apply( QVector4D p); //p is in affine coords
  //  QVector3D applyToPoint( QVector3D p);
//    QVector3D applyToVector( QVector3D v);
 //   QVector3D applyToVersor( QVector3D v);

   Transform combine_with( Transform & b,double deltaTime){
       Transform result;
       result.s = this->s *b.s; //(b.s*deltaTime) ;
       result.r = this->r*b.r;//(b.r*deltaTime);//QQuaternion::slerp(this->r,b.r,0.5);
       result.t = this->t + b.t*deltaTime;//(b.t*deltaTime);
       return result;
    }

//    Transform inverse();
 //   Transform interpolate_with( Transform &t, QVector3D k);

   //interpolation
    Transform mix_with(Transform b, float k){
       Transform result;
       result.s = this->s * k + b.s * (1-k);
      // result.r = this->r mix_with(b, k);
       result.r = QQuaternion::slerp(this->r,b.r,k);
       result.t = this->t * k + b.t * (1-k);
       return result;
    }



    QVector4D apply( QVector4D p);





    QMatrix4x4 doScale(QMatrix4x4 m){
         m.scale(s);
         return m;
    }
    QMatrix4x4 doRotate(QMatrix4x4 m){
         m.rotate(r);
         return m;
    }
    QMatrix4x4 doTranslate(QMatrix4x4 m){
         m.translate(t);
         return m;
    }



};
#endif // TRANSFORM_H


//gameobject : liste enfant, pointeur parent
