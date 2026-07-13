#pragma once

#include "common/Vector.hpp"
#include "Chunk.hpp"

struct Level 
{
    void loadChunk(vec3i32 pos);
private:
    std::unordered_map<vec3i32, std::shared_ptr<Chunk>> chunks;
};
