#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include <QPainter>

class Score : public QWidget
{
    Q_OBJECT
public:
    Score();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QString m_text;
public slots:
    void change_text_slot(const QString& text);
};

#endif // SCORE_H
