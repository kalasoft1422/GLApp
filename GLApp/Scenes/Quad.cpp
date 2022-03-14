//
// Created by kalasoft on 3/13/22.
//

#include <Shader.h>
#include <KSLog.h>
#include "Quad.h"


static float verts[] = {-0.5,-0.5,
                         0.5,-0.5,
                         0.5,0.5,

                        -0.5,-0.5,
                         0.5,0.5,
                        -0.5,0.5
                      };

static float colors[] ={

        1.0,0.0,0.0,1.0,
        0.0,1.0,1.0,1.0,
        1.0,1.0,0.0,1.0,

        1.0,0.0,0.0,1.0,
        1.0,1.0,0.0,1.0,
        1.0,1.0,1.0,1.0
};

Quad::Quad()
{
    GLuint bufs[2];
   glGenBuffers(2,bufs);

   vbo = bufs[0],cbo = bufs[1];
   glBindBuffer(GL_ARRAY_BUFFER,vbo);
   glBufferData(GL_ARRAY_BUFFER,6*2*sizeof(float),verts,GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER,cbo);
   glBufferData(GL_ARRAY_BUFFER,6*4*sizeof(float ),colors,GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER,0);

   KSLog::info("Quad","uplod");
}

Quad::~Quad() {

    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&cbo);
}


void Quad::draw()
{
  glUseProgram(Shader::baseProg);
  drawVBO();
}

void Quad::drawVBO()
{

    //vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0, nullptr);

    //colors
    glBindBuffer(GL_ARRAY_BUFFER,cbo);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0, nullptr);


    glDrawArrays(GL_TRIANGLES,0,6);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Quad::drawVBOEBO()
{


}

void Quad::clearBackground() {

}


