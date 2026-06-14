#pragma once

#include "gfx/IImage.hpp"

namespace gfx::gl 
{

struct ImageGL : Image
{
    ImageGL(const ImageDesc& desc);
    ~ImageGL();

    void bind() override;
    
    void write(const uint8_t* data) override;
    void setImageFilter(ImageFilter filter) override;
private:
    uint32_t  tex;
    ImageDesc desc;

    friend class RenderPassGL;
};

}