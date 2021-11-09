#include "object.h"

bool Object::animate = false;

//Object::Object()
//{
//}
void  Object::updateScene(QOpenGLShaderProgram * program, double deltaTime, QMatrix4x4 m){
    geo->updateBB(m);
    chargerTextureForShader(program);
    geo->drawCubeGeometry(program);
    foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
        go->updateScene(program,deltaTime, m);
    }
}

Object* Object::getRacine(){
    if(parent !=nullptr)
        return parent->getRacine();
    else
        return this;
}



void Object::findCollision( Object* obj, QMatrix4x4 anim){
   // QMatrix4x4 m= chargeMatriceForShader(program, deltaTime,lastM);

    foreach (Object* go, enfants){
        if(go->geo->intersect(obj->geo)){
            go->findCollision(obj, anim);
        }
    }
    if(enfants.size()==0 && this->geo->intersect(obj->geo)){
            qDebug("COOOOOOOOOLLLLLLLLLLLIIIIIIIIIIIIISSSSSSSIIIIIIIIIIIOOOOOOOOONNNNNNNNNN");
            QVector3D direction =Transform::extracteTranslate(anim);
            direction = this->geo->gestionCollision(obj->geo, direction);
            obj->animation.setTranslate(direction);
          //  gestionCollision();


    }
}


void Object::updateBB(){
    foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
        go->updateBB();
        geo->ajustBB(go->geo);
    }
}


