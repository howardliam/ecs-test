#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/gl.h"

class Texture {
public:
    Texture(const char *path);
    ~Texture();

    void bind() { glBindTexture(GL_TEXTURE_2D, handle); }
    void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
private:
    GLuint handle;
};

#endif
