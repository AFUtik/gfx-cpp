#pragma once

#include "Handle.hpp"
#include "pch.hpp"

namespace gfx 
{

struct BindGroupLayout;
struct Buffer;
struct Image;
struct Sampler;

struct CommandBuffer_T;
using CommandBuffer = CommandBuffer_T*;

struct BindGroupEntry
{
    uint32_t             binding  = 0;
    Handle<unknown_type> resource = {};
};

struct BindGroup
{
    Handle<BindGroupLayout>     layout;
    std::vector<BindGroupEntry> entries;

    virtual void setBuffer(uint32_t binding, Handle<Buffer>& buffer) = 0;
    virtual void setImage (uint32_t binding, Handle<Image>& image) = 0;
    virtual void write() = 0;
};

}
