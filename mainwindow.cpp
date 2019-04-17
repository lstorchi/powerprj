#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Power Project");

    QWidget * centralwdg = new QWidget(this);
    QGridLayout *vlay = new QGridLayout(centralwdg);
    QPushButton *btn1 = new QPushButton("Button1");
    vlay->addWidget(btn1, 0,0,1,1);
    QPushButton *btn2 = new QPushButton("Button2");
    vlay->addWidget(btn2, 0,2,1,1);

    QProgressBar * bar = new QProgressBar();
    bar->setMinimum(0.0);
    bar->setMaximum(100.0);
    bar->setValue(50);
    vlay->addWidget(bar, 1,1,10,1);

    centralwdg->setLayout(vlay);

    setCentralWidget(centralwdg);
}

MainWindow::~MainWindow()
{
    delete ui;
}
