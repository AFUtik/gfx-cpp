#include "gfx/backend/opengl/Image.hpp"

#include <glad/glad.h>

namespace gfx::gl 
{

ImageGL::ImageGL(const ImageDesc& desc)
    : desc(desc)
{
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        desc.width,
        desc.height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    GLenum filter = (desc.filter == ImageFilter::NEAREST)
        ? GL_NEAREST
        : GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

ImageGL::~ImageGL()
{
    if(tex) glDeleteTextures(1, &tex);
}

void ImageGL::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
}
    
void ImageGL::write(const uint8_t* data)
{
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0, 0,
        desc.width,
        desc.height,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );
}

void ImageGL::setImageFilter(ImageFilter filter_) 
{
    glBindTexture(GL_TEXTURE_2D, tex);

    GLenum filter;
    if(filter_ == ImageFilter::LINEAR)
    {
        filter = GL_LINEAR;
    }
    else if(filter_ == ImageFilter::NEAREST)
    {
        filter = GL_NEAREST;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

}