//
// Created by kalasoft on 3/13/22.
//

#include <KSLog.h>
#include <Shader.h>
#include <cassert>
#include <GLApp/Scenes/Quad.h>
#include <GLApp/Scenes/Texture.h>
#include "GLApplication.h"

void GLApplication::onCreate()
{
    KSApplication::onCreate();
    KSLog::info("GLApp","oncreate");

    IKSStream *f = openAsset("Shaders/base/f.glsl");
    IKSStream *v = openAsset("Shaders/base/v.glsl");


    Shader::baseProg = Shader::createProgram(v,f);
    Shader::texProg = Shader::createProgram(openAsset("Shaders/Texture/v.glsl"),openAsset("Shaders/Texture/f.glsl"));

    assert(Shader::baseProg != 0);

    View *content = new Texture(getAsset("textures/nature.jpeg"));

    setContentView(content);

}

