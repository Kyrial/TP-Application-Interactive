#ifndef MOBILEOBJ_H
#define MOBILEOBJ_H

#include <QVector3D>
#include <geometryengine.h>
class mobileObj
{
public:
    mobileObj();

    Transform t;
    QVector3D coord = QVector3D();

    GeometryEngine *geo = new GeometryEngine();


};

#endif // MOBILEOBJ_H
