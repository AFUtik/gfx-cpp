#pragma once

#include "PipelineState.hpp"

namespace gfx 
{

struct Pipeline;

struct PipelineDesc
{
    inline PipelineDesc& addShader(Handle<Shader>& shader)
    {
        shaders.push_back(shader);
        return *this;
    }

    inline PipelineDesc& setShaderResourceSignature(Handle<ShaderResourceSignature>& signature)
    {
        resourceSignature = signature;
        return *this;
    }

    inline PipelineDesc& setPipelineState(Handle<PipelineState>& state)
    {
        pipelineState = state;
        return *this;
    }
    
    virtual Handle<Pipeline> build() = 0;
protected:
    Handle<ShaderResourceSignature> resourceSignature;
    Handle<PipelineState>           pipelineState;

    std::vector<Handle<Shader>>     shaders;
};

}