#ifndef MOBILEOBJ_H
#define MOBILEOBJ_H

#include <QVector3D>
#include "transform.h"
#include "geometryengine.h"
#include "object.h"
class MobileObj  : public Object
{
public:

    MobileObj():Object(){}


    MobileObj(Transform tt):Object(tt){}
    MobileObj(Transform tt,Transform anim):Object(tt,anim){}


    float facteurGravite =300;
    float facteurCynetique = 25;


    void addGravite(double deltaTime){
        Transform G = Transform();


        //l'objet subit la gravité
        G.setTranslate(0,0,-(pow(1.1,(deltaTime/facteurGravite)))/10);
        animation = animation.combine_with(G, deltaTime);
        //l'objet est freiner
        animation.setTranslate(pow(0.9,deltaTime/facteurCynetique));

    }


    void  updateScene(QOpenGLShaderProgram * program, double deltaTime){
        if(animate)
            addGravite( deltaTime);
        QMatrix4x4 m= chargeMatriceForShader(program, deltaTime);

        Object::updateScene(program);
        //  qDebug("boucle ");
    }

};

#endif // MOBILEOBJ_H
