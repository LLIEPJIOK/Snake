#include "score.h"

Score::Score()
{
    setFixedSize(300, 50);
    m_text = "Счёт: 0\nпауза - ПРОБЕЛ";
}

void Score::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QColor(250, 250, 250));
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, m_text);
    painter.end();
}

void Score::change_text_slot(const QString &text)
{
    m_text = text;
    repaint();
}
