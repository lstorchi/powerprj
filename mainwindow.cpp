#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QPushButton>
#include <QPalette>
#include <QWidget>
#include <QColor>

#include <iostream>

namespace
{
    const QString getColor (int value)
    {
      QString basic = QString("QProgressBar {"
         "border: 1px solid black;"
         "text-align: top;"
         "padding: 1px;"
         "border-bottom-right-radius: 7px;"
         "border-bottom-left-radius: 7px;"
         "width: 50px;}");
      QString green = QString("QProgressBar::chunk {"
          "background-color: #7CFC00;" 
          "border-bottom-right-radius: 7px;" 
          "border-bottom-left-radius: 7px;" 
          "border: 1px solid black;" 
          "}");
      QString yellow = QString("QProgressBar::chunk {"
          "background-color: #FFFF00;" 
          "border-bottom-right-radius: 7px;" 
          "border-bottom-left-radius: 7px;" 
          "border: 1px solid black;" 
          "}");
      QString red = QString("QProgressBar::chunk {"
          "background-color: #FF0000;" 
          "border-bottom-right-radius: 7px;" 
          "border-bottom-left-radius: 7px;" 
          "border: 1px solid black;" 
          "}");

      if (value <= 30)
        return basic + green;
      else if (value > 30 && value < 60)
        return basic + yellow;
      else
        return basic + red;
    };
} 

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Power Project");

    QWidget * centralwdg = new QWidget(this);
    QGridLayout *vlay = new QGridLayout(centralwdg);
    QPushButton *btn1 = new QPushButton("Decrease");
    vlay->addWidget(btn1,0,0,1,1);
    QPushButton *btn2 = new QPushButton("Increase");
    vlay->addWidget(btn2,0,2,1,1);

    _bar = new QProgressBar();
    _bar->setOrientation(Qt::Vertical);
    _bar->setMinimum(0);
    _bar->setMaximum(100);
    _bar->setValue(0);
    _bar->setTextVisible(true);

    connect(btn1, SIGNAL(clicked()), this, SLOT(decrease()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(increase()));

    vlay->addWidget(_bar,1,1,10,1);

    centralwdg->setLayout(vlay);

    setCentralWidget(centralwdg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::increase()
{
    int value = _bar->value();
    value += 1;
    setStyleSheet (getColor(value));
    _bar->setValue(value);
}

void MainWindow::decrease()
{
    int value = _bar->value();
    value -= 1;
    setStyleSheet (getColor(value));
    _bar->setValue(value);
}
