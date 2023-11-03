#include "field.h"


Field::Field()
{
    setFixedSize(300, 300);
    setFocusPolicy(Qt::StrongFocus);
    m_item_size = 10;
    m_field_size = width() / m_item_size;
    start_new_game();
}

void Field::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBrush field_brush(QColor(139, 144, 163));
    QBrush snake_brush(QColor(140, 206, 147));
    QBrush food_brush(QColor(247, 103, 123));
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (m_is_game_over)
    {
        painter.setPen(QColor(250, 250, 250));
        painter.setFont(QFont("Arial", 15, QFont::Bold));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter,
                         "ИГРА ПРОИГРАНА\nСчёт: " + QString::number(m_score));
        return;
    }
    //drawing field
    painter.setBrush(field_brush);
    painter.setPen(QColor(50, 50, 50));
    painter.drawRect(0, 0, width() - 1, height() - 1);
    //drawing snake
    painter.setBrush(snake_brush);
    painter.setPen(QColor(0, 0, 0));
    for (int i = 0; i < m_snake->size(); ++i)
    {
        painter.drawEllipse(m_snake->get_snake_body()->at(i)->get_x() * m_item_size,
                            m_snake->get_snake_body()->at(i)->get_y() * m_item_size,
                            m_item_size, m_item_size);
    }
    //drawing food
    painter.setBrush(food_brush);
    painter.drawEllipse(m_food->get_x() * m_item_size, m_food->get_y() * m_item_size,
                        m_item_size, m_item_size);
    painter.end();
    m_is_move_blocked = 0;
}

void Field::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        if (m_is_game_over)
        {
            start_new_game();
            return;
        }
        m_is_pause = !m_is_pause;
        set_game_status();
        return;
    }
    if (m_is_pause || m_is_move_blocked)
        return;
    if (event->key() == Qt::Key_Left && m_snake->get_snake_direction() != snake_direction::right)
        m_snake->set_snake_direction(snake_direction::left);
    if (event->key() == Qt::Key_Right && m_snake->get_snake_direction() != snake_direction::left)
        m_snake->set_snake_direction(snake_direction::right);
    if (event->key() == Qt::Key_Down && m_snake->get_snake_direction() != snake_direction::up)
        m_snake->set_snake_direction(snake_direction::down);
    if (event->key() == Qt::Key_Up && m_snake->get_snake_direction() != snake_direction::down)
        m_snake->set_snake_direction(snake_direction::up);
    m_is_move_blocked = 1;
}

void Field::set_game_status()
{
    QString text;
    if (m_is_pause)
    {
        m_move_timer->stop();
        text = "Счёт: " + QString::number(m_score) + "\nПродолжить - ПРОБЕЛ";
    }
    else
    {
        m_move_timer->start(100);
        text = "Счёт: " + QString::number(m_score) + "\nПауза - ПРОБЕЛ";
    }
    emit change_text_signal(text);
}

void Field::game_over()
{
    m_is_game_over = 1;
    QString text = "Начать заново - ПРОБЕЛ";
    emit change_text_signal(text);
    m_move_timer->stop();
    delete m_snake;
    delete m_food;
    delete m_move_timer;
}

void Field::start_new_game()
{
    m_snake = new Snake();
    m_food = new Item(m_field_size / 2, m_field_size / 2);
    m_score = 0;
    m_is_pause = 0;
    m_is_move_blocked = 0;
    m_is_game_over = 0;
    m_move_timer = new QTimer();
    connect(m_move_timer, &QTimer::timeout, this, &Field::move_snake_slot);
    m_move_timer->start(60);
    QString text = "Счёт: 0\nпауза - ПРОБЕЛ";
    emit change_text_signal(text);
}

void Field::create_food()
{
    m_food->set_x(QRandomGenerator::global()->bounded(0, m_field_size - 1));
    m_food->set_y(QRandomGenerator::global()->bounded(0, m_field_size - 1));
    for (int i = 0; i < m_snake->size(); ++i)
        if (*m_food == *m_snake->get_snake_body()->at(i))
            return create_food();
}

void Field::move_snake_slot()
{
    Item *new_item;
    if (m_snake->get_snake_direction() == snake_direction::right)
        new_item = new Item(m_snake->get_snake_body()->at(0)->get_x() + 1,
                            m_snake->get_snake_body()->at(0)->get_y());
    else if (m_snake->get_snake_direction() == snake_direction::left)
        new_item = new Item(m_snake->get_snake_body()->at(0)->get_x() - 1,
                            m_snake->get_snake_body()->at(0)->get_y());
    else if (m_snake->get_snake_direction() == snake_direction::up)
        new_item = new Item(m_snake->get_snake_body()->at(0)->get_x(),
                            m_snake->get_snake_body()->at(0)->get_y() - 1);
    else
        new_item = new Item(m_snake->get_snake_body()->at(0)->get_x(),
                            m_snake->get_snake_body()->at(0)->get_y() + 1);
    //playing field limitation
    if (new_item->get_x() >= m_field_size)
        new_item->set_x(0);
    if (new_item->get_x() < 0)
        new_item->set_x(m_field_size);
    if (new_item->get_y() >= m_field_size)
        new_item->set_y(0);
    if (new_item->get_y() < 0)
        new_item->set_y(m_field_size);
    //game over
    for (int i = 1; i < m_snake->size(); ++i)
        if (*m_snake->get_snake_body()->at(0) == *m_snake->get_snake_body()->at(i))
        {
            game_over();
            break;
        }
    //eating
    if (!m_is_game_over)
    {
    if (*new_item == *m_food)
    {
        m_score++;
        create_food();
        QString text = "Счёт: " + QString::number(m_score) + "\nпауза - ПРОБЕЛ";
        emit change_text_signal(text);
    }
    else
        m_snake->get_snake_body()->removeLast();
    m_snake->get_snake_body()->insert(0, new_item);
    }
    repaint();
}
