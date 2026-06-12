#pragma once

#include "PipelineState.hpp"

namespace gfx 
{

struct Pipeline;

struct PipelineDescriptor
{
    inline PipelineDescriptor& addShader(Handle<Shader>& shader)
    {
        shaders.push_back(shader);
        return *this;
    }

    inline PipelineDescriptor& setShaderResourceSignature(Handle<ShaderResourceSignature>& signature)
    {
        resourceSignature = signature;
        return *this;
    }

    inline PipelineDescriptor& setPipelineState(Handle<PipelineState>& state)
    {
        pipelineState = state;
        return *this;
    }
    
    virtual Handle<Pipeline> Build() = 0;
protected:
    Handle<ShaderResourceSignature> resourceSignature;
    Handle<PipelineState>           pipelineState;
    
    std::vector<Handle<Shader>>     shaders;
};

}