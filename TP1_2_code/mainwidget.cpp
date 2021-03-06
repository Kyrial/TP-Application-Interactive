/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>
#include <iostream>
#include <math.h>
#include <QElapsedTimer>

int FPS = 20;
QElapsedTimer lastFrame;
double deltaTime = 1;
bool Tourne = true;

MainWidget::MainWidget(){}

MainWidget::MainWidget(int fps){
    FPS = fps;
}
void MainWidget::modifFPS(int x){
    FPS = x;
}

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0)
{
}


MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;

    delete textureGrass;
    delete textureRock;
    delete textureSnow;


    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]



QVector3D rotation_camera  = QVector3D(1.0f, 1.0f, 1.0f);
QVector3D camera_position = QVector3D(0.0f, 1.0f, 1.0f);
QVector3D camera_target = QVector3D(0.0f, -0.1f, -1.0f);
QVector3D camera_up = QVector3D(0.0f, 0.0f, 0.5f);


//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }

    if(Tourne){
       deltaTime = lastFrame.elapsed();
        camera_position = QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 2.0f), 0.03*(deltaTime)) * camera_position;
        update();
        lastFrame.start();
    }


}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
 //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    // Enable back face culling
  //  glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(FPS, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
//    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
//texture = new QOpenGLTexture(QImage(":/grass.png").mirrored());
    texture = new QOpenGLTexture(QImage(":/heightmap-1024x1024.png").mirrored());
   // texture = new QOpenGLTexture(QImage(":/Heightmap_Mountain.png").mirrored());
//texture = new QOpenGLTexture(QImage(":/Heightmap_Rocky.png").mirrored());
    textureGrass =new QOpenGLTexture(QImage(":/grass.png").mirrored());
    textureRock =new QOpenGLTexture(QImage(":/rock.png").mirrored());
    textureSnow =new QOpenGLTexture(QImage(":/snowrocks.png").mirrored());



    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);


    textureGrass->setMinificationFilter(QOpenGLTexture::Nearest);
    textureGrass->setMagnificationFilter(QOpenGLTexture::Linear);
    textureGrass->setWrapMode(QOpenGLTexture::Repeat);

    textureRock->setMinificationFilter(QOpenGLTexture::Nearest);
    textureRock->setMagnificationFilter(QOpenGLTexture::Linear);
    textureRock->setWrapMode(QOpenGLTexture::Repeat);

    textureSnow->setMinificationFilter(QOpenGLTexture::Nearest);
    textureSnow->setMagnificationFilter(QOpenGLTexture::Linear);
    textureSnow->setWrapMode(QOpenGLTexture::Repeat);

}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 2.0, zFar = 70.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]




void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind(0);
    textureGrass->bind(1);
    textureRock->bind(2);
    textureSnow->bind(3);
//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);



     QMatrix4x4 view;
     view.lookAt((camera_position), QVector3D(0, 0, 0), camera_up);



    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix",  projection *  matrix * view);
    // program.setUniformValue("mvp_matrix",  matrix * view * projection);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    program.setUniformValue("textureGrass", 1);
     program.setUniformValue("textureRock", 2);
      program.setUniformValue("textureSnow", 3);
    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
}


void MainWidget::keyPressEvent(QKeyEvent *event)
{
qDebug("touche appuy?? ");
    switch (event->key()) {
        case Qt::Key_Z: /* haut */
            projection.translate(0.0, 1.0, 0.0);
            break;
        case Qt::Key_Q: /* gauche */;
            projection.translate(-1.0, 0.0, 0.0);
            break;
        case Qt::Key_D: /*droite */
            projection.translate(1.0, 0.0, 0.0);
          break;
        case Qt::Key_S: /* bas */
            projection.translate(0.0, -1.0, 0.0);
            break;
        case Qt::Key_A: /* descendre */
            projection.translate(0.0, 0.0, 1.0);
            break;
        case Qt::Key_E: /* monter */
            projection.translate(0.0, 0.0, -1.0);
            break;
        case Qt::Key_C: /*  tourne terrain */
{

            lastFrame.start();
            Tourne = Tourne == true ? false: true;
        break;
    }

    }

    //projection.translate(0.0, 0.0, -1.0) ;
      update();

    // Save mouse press position
  //  mousePressPosition = QVector2D(e->localPos());
}



void MainWidget::cameraControle(){

       //QMatrix4x4 view = QMatrix4x4::lookAt(camera_position, camera_position + camera_target, camera_up);
       //float currentFrame = glfwGetTime();
    // float deltaTime = currentFrame - lastFrame;
     //   float lastFrame = currentFrame;
 //Camera zoom in and out
 /*   float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //camera_position += cameraSpeed * camera_target;
        camera_position += cameraSpeed * glm::vec3(0.0f, 0.0f, -1.0f);
        */}


