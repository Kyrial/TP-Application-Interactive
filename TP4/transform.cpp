#include "transform.h"




QMatrix4x4 Transform::inverse(QMatrix4x4 const m){
    QMatrix4x4 inv = m;
    return inv.inverted();
}

/*
QVector3D Transform::applyToPoint(QVector3D p){
    return m * p + t;
}
QVector3D Transform::applyToVector(QVector3D p){
 //   return m * p;
}

QVector3D Transform::applyToVersor(QVector3D v){
}

*/


