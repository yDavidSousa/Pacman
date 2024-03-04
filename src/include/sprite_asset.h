#ifndef PACMAN_SPRITE_ASSET_H
#define PACMAN_SPRITE_ASSET_H

#include "gl_texture.h"
#include <glm/glm.hpp>
#include <vector>

struct rect
{
    float x, y;
    float w, h;

    rect(float x, float y, float w, float h);
};

struct sprite_asset
{
    float x, y;
    float w, h;

    sprite_asset(const std::unique_ptr<gl_texture>& texture);
    sprite_asset(const std::unique_ptr<gl_texture>& texture, float x, float y, float w, float h);

    const rect get_rect();

    const std::vector<sprite_asset> slice_size(float width, float height, glm::vec2 offset, glm::vec2 padding);
    const std::vector<sprite_asset> slice_count(unsigned int column, unsigned int row, glm::vec2 offset, glm::vec2 padding);
};

#endif