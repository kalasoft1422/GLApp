//
// Created by kalasoft on 3/13/22.
//

#ifndef KALASOFT_QUAD_H
#define KALASOFT_QUAD_H


#include <View.h>
#include "GLContext.h"
class Quad : public View {

public:
    Quad();
    ~Quad();
    void draw() override;

    void clearBackground() override;

protected:
    GLuint vbo =0 ,cbo;
    void drawVBO();
    void drawVBOEBO();



};


#endif //KALASOFT_QUAD_H
