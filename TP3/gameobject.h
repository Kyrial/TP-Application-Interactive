#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"

#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
class GameObject
{
public:
    GameObject();


    Transform t = Transform();


    //vector enfant
    //parent gameObject
};

#endif // GAMEOBJECT_H
