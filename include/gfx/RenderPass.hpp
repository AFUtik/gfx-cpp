#pragma once

#include "Handle.hpp"
#include "IImage.hpp"

#include <vector>
#include <array>

namespace gfx 
{

struct Framebuffer;
struct RenderPipeline;

struct BindGroup;

enum AttachmentType
{
    ATTACHMENT_TYPE_COLOR,
    ATTACHMENT_TYPE_DEPTH
};

enum class LoadOp
{
    LOAD_OP,
    CLEAR_OP,
};

enum class StoreOp
{
    STORE_OP,
};

struct ColorAttachment
{
    AttachmentType type    = AttachmentType::ATTACHMENT_TYPE_COLOR;
    ImageFormat    format  = ImageFormat::RGBA8;
    LoadOp         loadOp  = LoadOp::LOAD_OP;
    StoreOp        storeOp = StoreOp::STORE_OP;
};

struct RenderPass
{
    virtual int checkCompatibilityWithFBO(Handle<Framebuffer>& framebuffer)      = 0;
    virtual int checkCompatibilityWithPipeline(Handle<RenderPipeline>& pipeline) {return 1;};

    virtual void setRenderPipeline(RenderPipeline* pipeline) = 0;
    virtual void setBindGroup     (BindGroup* group) = 0;

    virtual void begin(const Framebuffer* framebuffer) = 0;
    virtual void end  () = 0;
protected:
    std::array<float, 4> clearColor;
};

struct RenderPassDesc
{  
    std::vector<ColorAttachment> attachments;
    std::array<float, 4> clearColor;
};

}