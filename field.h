#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QString>
#include <QRandomGenerator>
#include "snake.h"

class Field : public QWidget
{
    Q_OBJECT
public:
    Field();
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    Snake *m_snake;
    Item *m_food;
    QTimer *m_move_timer;
    int m_item_size;
    int m_field_size;
    int m_score;
    bool m_is_pause;
    bool m_is_move_blocked;
    bool m_is_game_over;
    void set_game_status();
    void game_over();
    void start_new_game();
    void create_food();
private slots:
    void move_snake_slot();
signals:
    void change_text_signal(const QString& text);
};

#endif // FIELD_H
