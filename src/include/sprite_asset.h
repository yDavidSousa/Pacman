#ifndef PACMAN_SPRITE_ASSET_H
#define PACMAN_SPRITE_ASSET_H

#include "gl_texture.h"

#include <glm/glm.hpp>
#include <vector>

struct sprite_asset
{
    float x, y, w, h;
    float* tex_coords;

    sprite_asset();
    sprite_asset(float x, float y, float w, float h);
};

std::vector<sprite_asset> sprite_slice_size(const gl_texture* texture, float width, float height, glm::vec2 offset, glm::vec2 spacing);
std::vector<sprite_asset> sprite_slice_count(const gl_texture* texture, unsigned int column, unsigned int row, glm::vec2 offset, glm::vec2 spacing);

#endif