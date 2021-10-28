#ifndef OBJECT_H
#define OBJECT_H
#include "transform.h"
#include "geometryengine.h"
//#include "meshobject.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QVector>
#include <QOpenGLTexture>

class Object
{
    ///ATTRIBUT
public:
    GeometryEngine *geo = new GeometryEngine();
protected:
    Transform t = Transform();
    Transform animation = Transform();
    QOpenGLTexture *texture;
    bool ifTexture =false;

    ///Constructeur
public:
    Object():t(Transform()){}
    Object(Transform tt):t(tt){}
    Object(Transform tt,Transform anim):t(tt),animation(anim){}


   ///Getter/Setter
    void updateMesh(GeometryEngine *ge){
        geo = ge;
    }
    void setTexture(QOpenGLTexture *txtr){
        if(txtr !=NULL){
            texture = txtr;
            ifTexture =true;
        }
        else{
            ifTexture =false;
        }}

 ///Methode
protected:
    void chargerTextureForShader(QOpenGLShaderProgram * program){
        if(ifTexture){
            texture->bind(4);
            program->setUniformValue("textureScene", 4);
        }
        //ifTexture.bind(5);
        program->setUniformValue("textureSample", ifTexture);
    }


    QMatrix4x4 chargeMatriceForShader(QOpenGLShaderProgram * program, double deltaTime){
        QMatrix4x4 a = t.doTransformation();
        program->setUniformValue("transform_Matrix", a);
        return a;
    }
    QMatrix4x4 chargeMatriceForShader(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
        QMatrix4x4 anim = t.doAnimation(&animation, deltaTime);
        program->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }


};


#endif // OBJECT_H
