#include "object.h"

bool Object::animate = false;
//Object::Object()
//{
//}
void  Object::updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
    chargerTextureForShader(program);
    geo->drawCubeGeometry(program);
    foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
        go->updateScene(program,deltaTime, m);
    }
}



void Object::findCollision(QOpenGLShaderProgram * program, Object* obj){

    foreach (Object* go, enfants){
        if(go->geo->intersect(obj->geo))
                  {}
    }
}
