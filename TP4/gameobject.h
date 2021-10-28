#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "transform.h"
#include "geometryengine.h"
#include "object.h"
//#include "meshobject.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QVector>
#include <QOpenGLTexture>
class GameObject : public Object
{
    ///ATTRIBUT
private:
    QVector< GameObject*> enfants= QVector<GameObject*>();
    GameObject *parent;



    ///Constructeur
public:
    GameObject():Object(),parent(nullptr){}
    GameObject(Transform tt, GameObject par):Object(tt){
        parent = &par;
    }

    GameObject(Transform tt):Object(tt){}
    GameObject(Transform tt,Transform anim):Object(tt,anim){}

    GameObject(Transform tt, GameObject par, QVector<GameObject*> enf)
        :Object(tt),enfants(enf){
        parent = &par;
    }




public:
///Getter/Setter
    void addChild(GameObject * enfant){
        enfants.append(enfant);
        enfant->SetParent(this);
    }

    void SetParent(GameObject * pa){
        parent = pa;
    }




    ///Methode


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


};


#endif // GAMEOBJECT_H
