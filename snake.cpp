#include "snake.h"

Snake::Snake()
{
    m_snake_begin_size = 4;
    for (int i = 0; i < m_snake_begin_size; ++i)
        m_snake_body.insert(0, new Item(i, 0));
    m_snake_direction = snake_direction::right;
}

int Snake::size()
{
    return m_snake_body.size();
}

QList<Item *> *Snake::get_snake_body()
{
    return &m_snake_body;
}

const snake_direction &Snake::get_snake_direction()
{
    return m_snake_direction;
}

void Snake::set_snake_direction(const snake_direction &snake_dir)
{
    m_snake_direction = snake_dir;
}
