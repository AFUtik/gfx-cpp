#pragma once

#include "IBuffer.hpp"

namespace gfx::gl
{

class BufferGL : public Buffer
{
public:
    BufferGL(const BufferDesc& desc);
    ~BufferGL();

    void write(const void* data, uint64_t size, uint64_t offset) override;
    void* map()   override;
    void  unmap() override;

    uint64_t getSize() const override {return size;};
private:
    uint32_t buffer = 0;
    uint64_t target = 0;
    uint64_t size   = 0;
};

}