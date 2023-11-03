#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "field.h"
#include "score.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Field *m_field;
    Score *m_score;
    QGridLayout *m_grid_lay;
    QWidget *m_central_widget;
};
#endif // MAINWINDOW_H
