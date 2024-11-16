#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "glad/gl.h"

class Framebuffer {
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, width, height);
    }
    void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void bind_texture() { glBindTexture(GL_TEXTURE_2D, framebuffer_texture); }
    void unbind_texture() { glBindTexture(GL_TEXTURE_2D, 0); }
private:
    int width;
    int height;

    GLuint fbo;
    GLuint framebuffer_texture;
    GLuint rbo;
};

#endif
