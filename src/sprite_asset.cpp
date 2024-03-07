#include "include/sprite_asset.h"

sprite_asset::sprite_asset() : x(0), y(0), w(0), h(0)
{}

sprite_asset::sprite_asset(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
{}

std::vector<sprite_asset> sprite_slice_size(sprite_asset& sprite, float width, float height, glm::vec2 offset, glm::vec2 spacing)
{
    unsigned int column = static_cast<unsigned int>((sprite.w - (offset.x * 2) - (column - 1 * spacing.x)) / width);
    unsigned int row = static_cast<unsigned int>((sprite.h - (offset.y * 2) - (row - 1 * spacing.y)) / height);

    std::vector<sprite_asset> result;
    float y = offset.y;
    for (int r = 0; r < row; r++)
    {
        float x = offset.x;
        for (int c = 0; c < column; c++)
        {
            sprite_asset ss(x, y, width, height);
            result.push_back(ss);

            x = (x + width) + spacing.x;
        }

        y = (y + height) + spacing.y;
    }

    return result;
}

std::vector<sprite_asset> sprite_slice_count(sprite_asset& sprite, unsigned int column, unsigned int row, glm::vec2 offset, glm::vec2 spacing)
{
    float width = (sprite.w - (offset.x * 2) - (column - 1 * spacing.x)) / column;
    float height = (sprite.h - (offset.y * 2) - (row - 1 * spacing.y)) / row;

    std::vector<sprite_asset> result;
    float y = offset.y;
    for (int r = 0; r < row; r++)
    {
        float x = offset.x;
        for (int c = 0; c < column; c++)
        {
            sprite_asset ss(x, y, width, height);
            result.push_back(ss);

            x = (x + width) + spacing.x;
        }

        y = (y + height) + spacing.y;
    }

    return result;
}