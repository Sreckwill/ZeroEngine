#include "Textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Textures::Textures(const std::string& filepath) : textureID(0), width(0), height(0), numChannels(0) {
    //Gen and Bind the Texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture data
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numChannels, 0);
    //checking the data
    if (data) {
        GLenum format = (numChannels == 3) ? GL_RGB : GL_RGBA; // Assuming RGB or RGBA texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << filepath << std::endl;
    }
    //free the image
    stbi_image_free(data);
}

Textures::~Textures() {
    //Deleteing the Textur
    glDeleteTextures(1, &textureID);
}

void Textures::bind() const {
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Textures::unbind() const {
    //un bind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}
//glActiveTexture  that glActiveTexture 
// is typically used when you have multiple
//  texture units and need to specify which 
// texture unit to make active before binding a texture to it.
void Textures::ActiveTexure(GLenum Texture_no)
{
    glActiveTexture(Texture_no);
}

