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

#include "geometryengine.h"

#include <iostream>

#include <QVector2D>
#include <QVector3D>



//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
 //   initCubeGeometry();

//    initPlanegeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void GeometryEngine::initMesh(std::string filename){
       std::vector<QVector3D>  vertex;
       std::vector< std::vector<unsigned int> >  faces;

       OFFIO::open(filename, vertex, faces, true);


       unsigned int vertexNumber = vertex.size();
       VertexData vertices[vertexNumber];
       unsigned int indexCount = faces.size()*3;
       GLushort indices[indexCount];


       for(int i=0; i<vertexNumber;i++) {
           //vertices[i]= {vertex[i], QVector2D(i/(float)vertexNumber, i/(float)vertexNumber)};
           vertices[i]= {vertex[i], QVector2D(vertex[i][0]+vertex[i][1], vertex[i][0]+vertex[i][2])};
       }

       for(int i=0; i<indexCount;i+=3) {
           indices[i]= faces[i/3][0];
           indices[i+1]= faces[i/3][1];
           indices[i+2]= faces[i/3][2];
       }

       qDebug("vertexNumber :%i, et indexCount = %i \n ",vertexNumber, indexCount );

       // Transfer vertex data to VBO 0
       arrayBuf.bind();
       arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

       // Transfer index data to VBO 1
       indexBuf.bind();
       indexBuf.allocate(indices,  ((indexCount)* sizeof(GLushort)));
       triangle_strip = true;
}

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    // Hence 4 vertices per face and 6 faces vertices = 24 vertices
    unsigned int vertexNumber = 24 ;
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };


    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    unsigned int indexCount = 34; //Careful update indicesNumber when creating new geometry
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
    std::cout << indexBuf.size() << " index count " << indexCount <<"sizeof" <<  sizeof(GLushort) << std::endl;
//! [1]
}

void GeometryEngine::subdivisePlan(int x, int y, VertexData vertices[],GLushort indices[], float Xmin=-1,float Ymin=-1,float Xmax=1,float Ymax=1)//, std::string  nameWeightMap = "")
{

    float intervalX_Texture=2/(float)(x-1);
    float intervalY_Texture=2/(float)(y-1);

   float intervalX=(Xmax-Xmin)/(float)(x-1);
   float intervalY=(Ymax-Ymin)/(float)(y-1);
   for(int i=0; i<x; i++){
        for(int j=0;j<y; j++){
         //   qDebug("%f %f",Xmin+intervalX*i, Ymin+intervalY*j);
          //  vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j, static_cast<float> (rand()) / static_cast<float> (RAND_MAX) ), QVector2D((intervalX_Texture*i)/2, (intervalY_Texture*j)/2)};
            vertices[i*y+j]= {QVector3D(Xmin+intervalX*i, Ymin+intervalY*j,0.0f ), QVector2D((intervalX_Texture*i)/2, (intervalY_Texture*j)/2)};

       }
   }
   int count =0;
   for(int i=0; i<x-1; i++){
        for(int j=0;j<y; j++){
            //count+=2;
      //      qDebug("indices %i, %i",2*i+i*(y*2)+j*2,2*i+i*(y*2)+j*2+1 );
             //   indices[2*i+i*(y*2)+j*2] = i*y+j;
            //    indices[2*i+i*(y*2)+j*2+1] = (i+1)*y+j;
                indices[count++] = i*y+j;
                indices[count++] = (i+1)*y+j;
            }
        if(i!=x-2){
            //count +=2;
     //   qDebug("indices degenerer %i, %i",2*i+i*(y*2)+y*2,2*i+i*(y*2)+y*2+1 );
        //    indices[2*i+i*(y*2)+y*2]=(i+1)*y+y-1;
        //    indices[2*i+i*(y*2)+y*2+1]=(i+1)*y;
            indices[count++]=(i+1)*y+y-1;
            indices[count++]=(i+1)*y;
    }
}
   indices[count]=indices[count-1];
}

void GeometryEngine::initPlanegeometry()
{

    int x=80;
    int y=80;
    unsigned int vertexNumber = x*y ;
    VertexData vertices[x*y];
    unsigned int indexCount = x*y+y*(x-2)+2*(x-2)+2;
    GLushort indices[x*y+y*(x-2)+2*(x-2)+2];
    subdivisePlan(x,  y,  vertices,  indices,-2,-2,2,2);

   // qDebug("taille index %i",indexCount);
//qDebug("taille index tab %i",x*y+y*(x-2)+2*(x-2)+2);




//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  ((indexCount)* sizeof(GLushort)));
  //  std::cout << indexBuf.size() << " index count " << indexCount <<"sizeof" <<  sizeof(GLushort) << std::endl;
//! [1]
}





//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
 //   std::cout << indexBuf.size() << " , meow " <<   std::endl;
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    int size = (int)indexBuf.size();
  // std::cout << indexBuf.size() << " , meow " <<  size << std::endl;
    if(triangle_strip)
        glDrawElements(GL_TRIANGLE_STRIP, size/2, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
    else
        glDrawElements(GL_TRIANGLES, size/2, GL_UNSIGNED_SHORT, 0);
}
//! [2]
