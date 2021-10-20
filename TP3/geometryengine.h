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

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QVector2D>
#include <QVector3D>

#include "BasicIO.h"
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class GeometryEngine : protected QOpenGLFunctions_3_1
{
public:
    GeometryEngine();
    //GeometryEngine(std::string filename){
    /*   std::vector<VertexData>  vertice;
       OFFIO::open( filename, vertice);


       // Transfer vertex data to VBO 0
       arrayBuf.bind();
       arrayBuf.allocate(vertice, vertice.size()+sizeof(QVector3D));

       // Transfer index data to VBO 1
      // indexBuf.bind();
      // indexBuf.allocate(indices,  ((indexCount)* sizeof(GLushort)));*/
   // }

    int test(QOpenGLShaderProgram *program){
                qDebug("test %i", 55);
            //std::cout << indexBuf << " , meow " <<   std::endl;
            return 5;
    }

    virtual ~GeometryEngine();

    void initMesh(std::string filename);
    void drawCubeGeometry(QOpenGLShaderProgram *program);
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    void initCubeGeometry();
    void initPlanegeometry();
private:

    //void initPlanegeometry();
    void subdivisePlan(int x, int y,  VertexData vertices[], GLushort indices[],float Xmin,float Ymin,float Xmax,float Ymax);//,std::string nameWeightMap );

};

#endif // GEOMETRYENGINE_H
