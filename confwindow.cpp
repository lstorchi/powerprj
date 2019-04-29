#include "confwindow.h"

#include <QCloseEvent>
#include <QGridLayout>
#include <QPushButton>
#include <QPalette>
#include <QWidget>
#include <QColor>


ConfWindow::ConfWindow(QWidget *parent) : 
  QMainWindow(parent),
  ui(new Ui::ConfWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("Configure Win Power Project");
 
  QWidget * centralwdg = new QWidget(this);
  QGridLayout *vlay = new QGridLayout(centralwdg);
  
  _bar = new QProgressBar();
  _bar->setOrientation(Qt::Vertical);
  _bar->setMinimum(0);
  _bar->setMaximum(100);
  _bar->setValue(0);
  _bar->setTextVisible(true);
  
  vlay->addWidget(_bar,0,0,10,1);

  QPushButton *btn1 = new QPushButton("Done");
  vlay->addWidget(btn1,0,1,1,1);

  QObject::connect(btn1, SIGNAL(clicked()), this, SLOT(close()));
  
  centralwdg->setLayout(vlay);
  
  setCentralWidget(centralwdg);

  _maxvalue = -1;
}

ConfWindow::~ConfWindow()
{
}

int ConfWindow::get_maxvalue() const
{
  return _maxvalue;
}

void ConfWindow::reset_maxvalue()
{
  _maxvalue = -1;
}

void ConfWindow::closeEvent( QCloseEvent* event )
{
  emit IamClosing();
  event->accept();
}

void ConfWindow::updateprogress(int val)
{
  _bar->setValue(val);
  if (val > _maxvalue)
    _maxvalue = val;
}
