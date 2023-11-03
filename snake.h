#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include "item.h"

enum snake_direction
{
    up,
    left,
    down,
    right
};

class Snake
{
public:
    Snake();
    int size();
    QList<Item*>* get_snake_body();
    const snake_direction& get_snake_direction();
    void set_snake_direction(const snake_direction& snake_dir);
private:
    QList<Item*> m_snake_body;
    int m_snake_begin_size;
    snake_direction m_snake_direction;
};

#endif // SNAKE_H
