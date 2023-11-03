#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(320, 390);
    m_field = new Field();
    m_score = new Score();
    m_grid_lay = new QGridLayout();
    m_central_widget = new QWidget();
    connect(m_field, &Field::change_text_signal, m_score, &Score::change_text_slot);
    m_grid_lay->addWidget(m_field, 0, 0);
    m_grid_lay->addWidget(m_score, 1, 0);
    m_grid_lay->setSpacing(5);
    m_central_widget->setLayout(m_grid_lay);
    setCentralWidget(m_central_widget);
    setStyleSheet("background: rgb(90, 100, 112)");

}

MainWindow::~MainWindow()
{

}

