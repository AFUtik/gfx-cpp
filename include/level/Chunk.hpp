#pragma once

#include "Block.hpp"
#include "pch.hpp"

constexpr uint64_t SECTION_HEIGHT = 16;

constexpr uint64_t CHUNK_WIDTH    = 16;
constexpr uint64_t CHUNK_DEPTH    = 16;
constexpr uint64_t CHUNK_HEIGHT   = 256;

constexpr uint64_t SECTION_COUNT  = CHUNK_HEIGHT / SECTION_HEIGHT; 
constexpr uint64_t SECTION_VOLUME = CHUNK_WIDTH * CHUNK_DEPTH * SECTION_HEIGHT;
constexpr uint64_t CHUNK_VOLUME   = CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT;

struct Section
{
private:
    Block blocks[SECTION_VOLUME];

    friend struct Chunk;
};

struct Chunk 
{
    static constexpr uint32_t blockIndex(uint32_t x, uint32_t y, uint32_t z)
    {
        return (y << 8) | (z << 4) | x;
    }

    inline Section& getSection(int32_t y)
    {
        return sections[y / SECTION_HEIGHT];
    }

    inline Block getBlock(uint32_t x, uint32_t y, uint32_t z)
    {
        auto& section = sections[y >> 4];
        return section.blocks[blockIndex(x, y & 0xF, z)];
    }

    void setBlock(uint32_t x, uint32_t y, uint32_t z, Block block)
    {
        getBlock(x, y, z) = block;
    }
private:
    std::array<Section, SECTION_COUNT>  sections;
    std::array<std::weak_ptr<Chunk>, 6> neighbours; // 0: west, 1: east, 2: north, 3: south, 4: up, 5: down //
};
