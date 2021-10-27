#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"
#include "geometryengine.h"
//#include "meshobject.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QVector>
#include <QOpenGLTexture>
class GameObject
{
public:
    GameObject()
    {
        t = Transform();
        parent = nullptr;
    }
    GameObject(Transform tt, GameObject par)
    {
        t = tt;
        parent = &par;
    }
    GameObject(Transform tt)
    {
        t = tt;
    }
    GameObject(Transform tt,Transform anim)
    {
        t = tt;
        animation = anim;
    }

    GameObject(Transform tt, GameObject par, QVector<GameObject*> enf)
    {
        t = tt;
        parent = &par;
        enfants = enf;
    }


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


   void addChild(GameObject * enfant){
  //     qDebug("miaou %i",enfants.size());
       //enfants.push_back(enfant);
       enfants.append(enfant);
       enfant->SetParent(this);

   }

// virtual ~GameObject();

   void SetParent(GameObject * pa){
       parent = pa;
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


#endif // GAMEOBJECT_H
