#include "include/sprite_asset.h"

rect::rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

sprite_asset::sprite_asset(const std::unique_ptr<gl_texture>& texture) : x(0), y(0)
{
    w = texture->get_width();
    h = texture->get_height();
}

sprite_asset::sprite_asset(const std::unique_ptr<gl_texture>& texture, float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

const std::vector<sprite_asset> sprite_asset::slice_size(float width, float height, glm::vec2 offset, glm::vec2 padding)
{
    unsigned int column = static_cast<unsigned int>(w / width);
    unsigned int row = static_cast<unsigned int>(h / height);

    std::vector<sprite_asset> sprites;
    int offset_x = 0, offset_y = 0;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < column; c++)
        {
            sprite_asset sprite(nullptr, offset_x, offset_y, width, height);
            sprites.push_back(sprite);
            offset_x += width;
        }
        offset_y += height;
    }

    return sprites;
}

const std::vector<sprite_asset> sprite_asset::slice_count(unsigned int column, unsigned int row, glm::vec2 offset, glm::vec2 padding)
{
    float width = w / column;
    float height = h / row;

    std::vector<sprite_asset> sprites;
    int offset_x = 0, offset_y = 0;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < column; c++)
        {
            sprite_asset sprite(nullptr, offset_x, offset_y, width, height);
            sprites.push_back(sprite);
            offset_x += width;
        }
        offset_y += height;
    }

    return sprites;
}

const rect sprite_asset::get_rect()
{
    rect rect(x, y, w, h);
    return rect;
}