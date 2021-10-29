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
    static bool  animate;
protected:
    Transform t = Transform();
    Transform animation = Transform();
    QOpenGLTexture *texture;
    bool ifTexture =false;
  //  QVector< Object*> enfants= QVector<Object*>();
  //  Object *parent;

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

    QMatrix4x4 calculMatrice(QOpenGLShaderProgram * program, double deltaTime){
        QMatrix4x4 a;
        if(animate)
             a = t.doAnimation(&animation, deltaTime);
        else
             a = t.doTransformation();
        return a;
}
    QMatrix4x4 ApplyMatriceForShader(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){

        QMatrix4x4 anim= calculMatrice(program,  deltaTime);

        program->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }


    QMatrix4x4 chargeMatriceForShader(QOpenGLShaderProgram * program, double deltaTime){

        QMatrix4x4 a =  calculMatrice(program,  deltaTime);

        program->setUniformValue("transform_Matrix", a);
        return a;
    }

    QMatrix4x4 chargeMatriceForShader(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){

        QMatrix4x4 anim= calculMatrice(program,  deltaTime);

        program->setUniformValue("transform_Matrix", m*anim);
        return m*anim;
    }


    void  updateScene(QOpenGLShaderProgram * program){
        chargerTextureForShader(program);
        geo->drawCubeGeometry(program);
        //foreach (GameObject* go, enfants) {
            //   qDebug("foreach %i \n",enfants.size());
      //      go->updateScene(program,deltaTime, m);
    }



};


#endif // OBJECT_H
