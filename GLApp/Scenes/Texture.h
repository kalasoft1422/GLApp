//
// Created by kalasoft on 3/13/22.
//

#ifndef KALASOFT_TEXTURE_H
#define KALASOFT_TEXTURE_H


#include <View.h>
#include <cstdio>
#include "Quad.h"

class Texture  : public Quad{
public:
    Texture();
    Texture(AAsset *asset);
    void clearBackground() override;

    void draw() override;

protected:
    GLuint tex = 0,pbo = 0,uvbo = 0;
    int width = 1,height = 1,channels = 1;
    bool updateTexture(AAsset *asset);

};


#endif //KALASOFT_TEXTURE_H
