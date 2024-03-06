#include "include/sprite_asset.h"

sprite_asset::sprite_asset()
{}

sprite_asset::sprite_asset(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
{}

sprite_asset* sprite_slice_size(sprite_asset& sprite, float width, float height, glm::vec2 offset, glm::vec2 spacing)
{
    unsigned int column = static_cast<unsigned int>(sprite.w / width);
    unsigned int row = static_cast<unsigned int>(sprite.h / height);

    sprite_asset* sprites = new sprite_asset[row * column];
    float x = offset.x, y = offset.y;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < column; c++)
        {
            unsigned int i = (row * sprite.w) + column;
            sprite_asset sprite(x, y, width, height);
            sprites[i] = sprite;

            x = (x + width) + spacing.x;
        }

        y = (y + height) + spacing.y;
    }

    return sprites;
}

sprite_asset* sprite_slice_count(sprite_asset& sprite, unsigned int column, unsigned int row, glm::vec2 offset, glm::vec2 spacing)
{
    float width = sprite.w / column;
    float height = sprite.h / row;

    sprite_asset* sprites = new sprite_asset[row * column];
    float x = offset.x, y = offset.y;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < column; c++)
        {
            unsigned int i = (row * sprite.w) + column;
            sprite_asset sprite(x, y, width, height);
            sprites[i] = sprite;

            x = (x + width) + spacing.x;
        }

        y = (y + height) + spacing.y;
    }

    return sprites;
}