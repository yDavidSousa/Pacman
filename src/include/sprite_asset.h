#ifndef PACMAN_SPRITE_ASSET_H
#define PACMAN_SPRITE_ASSET_H

#include <glm/glm.hpp>

struct sprite_asset
{
    float x, y;
    float w, h;

    sprite_asset();
    sprite_asset(float x, float y, float w, float h);
};

sprite_asset* sprite_slice_size(sprite_asset& sprite, float width, float height, glm::vec2 offset, glm::vec2 spacing);
sprite_asset* sprite_slice_count(sprite_asset& sprite, unsigned int column, unsigned int row, glm::vec2 offset, glm::vec2 spacing);

#endif