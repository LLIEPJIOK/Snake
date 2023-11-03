#include "item.h"

Item::Item(const int &x, const int &y)
{
    m_x = x;
    m_y = y;
}

int Item::get_x()
{
    return m_x;
}

void Item::set_x(const int &x)
{
    m_x = x;
}

int Item::get_y()
{
    return m_y;
}

void Item::set_y(const int &y)
{
    m_y = y;
}

bool operator == (const Item& item1, const Item& item2)
{
    return item1.m_x == item2.m_x && item1.m_y == item2.m_y;
}
