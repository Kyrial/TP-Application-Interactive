#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"
#include "geometryengine.h"
//#include "meshobject.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QVector>
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
  /*  GameObject(Transform tt, GameObject par, meshObject geo)
    {
        t = tt;
        parent = &par;
        obj = geo;
    }*/
/*
    GameObject(Transform tt, meshObject geo)
    {
        t = tt;
        parent = nullptr;
        obj = geo;
    }
*/
    GameObject(Transform tt, GameObject par, QVector<GameObject*> enf)
    {
        t = tt;
        parent = &par;
        enfants = enf;
    }


    void  updateScene(QOpenGLShaderProgram * program){
        qDebug("update %i",enfants.size());
        chargeMatriceForShader(program);
        qDebug("dessine ");
        geo->drawCubeGeometry(program);
        qDebug("boucle ");


       foreach (GameObject* go, enfants) {
         qDebug("foreach %i",enfants.size());
        //std::cout<<go->a()<<std::endl;

        qDebug("dessine1 %p %p", program, go->geo);
          //   go->geo->drawCubeGeometry(program);
        qDebug("dessine2 ");
        go->updateScene(program);

        }
     }


    int a(){return 5;}




GeometryEngine *geo = new GeometryEngine();
private:

//Transform t_globale = Transform();
   // Transform t_locale = Transform();
    Transform t = Transform();
    QVector< GameObject*> enfants= QVector<GameObject*>();
    GameObject *parent;
   // meshObject obj;



public:

   void chargeMatriceForShader(QOpenGLShaderProgram * program){

    QMatrix4x4 a= QMatrix4x4 ();
    a.scale(0.5, 0.5, 0.5);
    program->setUniformValue("transform_Matrix", a);
   }


   void addChild(GameObject * enfant){
       qDebug("miaou %i",enfants.size());
       //enfants.push_back(enfant);
       enfants.append(enfant);

   }

// virtual ~GameObject();


};




#endif // GAMEOBJECT_H
