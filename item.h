#ifndef ITEM_H
#define ITEM_H


class Item
{
public:
    Item(const int& x, const int& y);
    int get_x();
    void set_x(const int& x);
    int get_y();
    void set_y(const int& y);
    friend bool operator == (const Item& item1, const Item& item2);
private:
    int m_x;
    int m_y;
};

#endif // ITEM_H
