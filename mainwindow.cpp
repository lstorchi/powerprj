#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QPushButton>
#include <QPalette>
#include <QWidget>
#include <QColor>

namespace
{
    const QString getColor (int value)
    {
      if (value <= 50)
        return QString("green");
      else
        return QString("red");
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
    vlay->addWidget(btn1, 0,0,1,1);
    QPushButton *btn2 = new QPushButton("Increase");
    vlay->addWidget(btn2, 0,2,1,1);

    _bar = new QProgressBar();
    _bar->setMinimum(0);
    _bar->setMaximum(100);
    _bar->setValue(0);

    connect(btn1, SIGNAL(clicked()), this, SLOT(decrease()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(increase()));

    vlay->addWidget(_bar, 1,1,10,1);

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
    QPalette p = _bar->palette();
    p.setColor(QPalette::Highlight, QColor(getColor(value)));
    _bar->setPalette(p);
    _bar->setValue(value);
}

void MainWindow::decrease()
{
    int value = _bar->value();
    value -= 1;
    QPalette p = _bar->palette();
    p.setColor(QPalette::Highlight, QColor(getColor(value)));
    _bar->setPalette(p);
    _bar->setValue(value);

}
