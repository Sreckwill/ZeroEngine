#pragma once
#include<GL/glew.h>
#include<iostream>
#include <string>

class Textures {
private:
    //texture renderID;
    unsigned int textureID;
    //texture width, height and numChannels
    int width, height, numChannels;

public:
    ////constructor for Assiging the Texture
    Textures(const std::string& filepath);
    //destructor for Deleting the Texture
    ~Textures();
    //Bind the Texture
    void bind() const;
    //Un Bind the Texture
    void unbind() const;
    //Active Texture
    void ActiveTexure(GLenum Texture_no);
 
};

