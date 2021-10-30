#include "cameraobject.h"

CameraObject::CameraObject()
{

}

void  CameraObject::updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
    QVector3D q = m*QVector3D(0, 0, 0);
    QVector3D qq = m*camera_position;
    QMatrix4x4 view;
 view.lookAt((m*camera_position), QVector3D(0, 0, 0), camera_up);
    view.lookAt((m*camera_position),m*QVector3D(0, 0, 0), camera_up);
    //camera_position + camera_target


    // Set modelview-projection matrix
    program->setUniformValue("camera_matrix", view);
}

