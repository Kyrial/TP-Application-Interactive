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



void Object::findCollision( Object* obj, QMatrix4x4 anim){
   // QMatrix4x4 m= chargeMatriceForShader(program, deltaTime,lastM);

    foreach (Object* go, enfants){
        if(go->geo->intersect(obj->geo)){
            go->findCollision(obj, anim);

            QVector3D direction =Transform::extracteTranslate(anim);
            direction = go->geo->gestionCollision(obj->geo, direction);
            obj->animation.setTranslate(direction);
          //  gestionCollision();
            break;

        }
    }
}


void Object::updateBB(){
    foreach (Object* go, enfants) {
        //  qDebug("foreach %i \n",enfants.size());
        go->updateBB();
        geo->ajustBB(go->geo);
    }
}

//void Object::setMonde(Object *o){
//    Monde=o;
//}
