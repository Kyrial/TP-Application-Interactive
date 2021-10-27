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
public:
    Object();



void  updateScene(QOpenGLShaderProgram * program, double deltaTime){
    QMatrix4x4 m= chargeMatriceForShader(program, deltaTime);

    chargerTextureForShader(program);

    geo->drawCubeGeometry(program);
  //  qDebug("boucle ");
        foreach (GameObject* go, enfants) {
     //   qDebug("foreach %i \n",enfants.size());
        go->updateScene(program,deltaTime, m);
    }
 }
void  updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 lastM){
    QMatrix4x4 m= chargeMatriceForShader(program, deltaTime,lastM);

    chargerTextureForShader(program);

    geo->drawCubeGeometry(program);
//     qDebug("boucle ");
        foreach (GameObject* go, enfants) {
      //  qDebug("foreach %i \n",enfants.size());
        go->updateScene(program,deltaTime, m);
    }
 }


//  int a(){return 5;}

void updateMesh(GeometryEngine *ge){
    geo = ge;
}


GeometryEngine *geo = new GeometryEngine();
private:

//Transform t_globale = Transform();

Transform t = Transform();
QVector< GameObject*> enfants= QVector<GameObject*>();
GameObject *parent;
Transform animation = Transform();
QOpenGLTexture *texture;
bool ifTexture =false;


public:

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
//QMatrix4x4 a = t.doTransformation();
QMatrix4x4 anim = t.doAnimation(&animation, deltaTime);

program->setUniformValue("transform_Matrix", m*anim);
return m*anim;
}






void setTexture(QOpenGLTexture *txtr){
if(txtr !=NULL){
texture = txtr;
ifTexture =true;
}
else{
     ifTexture =false;
}}




};


#endif // OBJECT_H
