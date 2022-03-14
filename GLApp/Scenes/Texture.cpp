//
// Created by kalasoft on 3/13/22.
//

#include <Shader.h>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"


//{ 0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};

static float textureCoods[] = { 0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f};


int32_t readAsset(void *asset, char *data, int size)
{
    return AAsset_read((AAsset *)asset,data,size);
}
int32_t assetEof(void *asset)
{
    if(AAsset_getRemainingLength64((AAsset *)asset) <=0)
        return 1;
    return 0;
}
void assetSkip(void *asset, int n) {
    AAsset_seek((AAsset *) asset, n, SEEK_CUR);
}


Texture::Texture()
{

    glGenBuffers(1,&uvbo);
    glBindBuffer(GL_ARRAY_BUFFER,uvbo);
    glBufferData(GL_ARRAY_BUFFER,6* 2*sizeof(float),textureCoods,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    KSLog::info("Texture","uvCheck");

}

Texture::Texture(AAsset *asset) : Texture()
{
    updateTexture(asset);
}
void Texture::draw()
{

    glUseProgram(Shader::texProg);

    //vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,cbo);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0, nullptr);


    //texCoords
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER,uvbo);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0, nullptr);


    glBindTexture(GL_TEXTURE_2D,tex);


    glDrawArrays(GL_TRIANGLES,0,6);


    glBindTexture(GL_TEXTURE_2D,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);



}


void Texture::clearBackground()
{


}

bool Texture::updateTexture(AAsset *asset) {



    if(asset)
    {
        KSLog::info("Texture","updating");

        //Decoding Image Asset
        stbi_io_callbacks assetIOCallbacks ={.read = readAsset,.skip=assetSkip,.eof = assetEof};
        stbi_info_from_callbacks(&assetIOCallbacks, asset, &width, &height, &channels);
        AAsset_seek(asset,0,SEEK_SET);
        stbi_uc *pixels = stbi_load_from_callbacks(&assetIOCallbacks, asset, &width, &height, &channels, 4);
        if(pixels == NULL)
        {
            KSLog::error("Texture:","Image Decode error");
            return false;
            //close fd;
        }
        //image decoded

        //Generate gl texture and upload pixel data to it.
        if(glIsTexture(tex))
        {
            glDeleteTextures(1,&tex);
        }
        glGenTextures(1,&tex);
        // glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        stbi_image_free(pixels);
        AAsset_close(asset);
        return true;
    }

    return false;
}
