#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QPalette>
#include <QThread>
#include <QWidget>
#include <QColor>

#include <iostream>

#define MAXPERC 100
#define MINPERC 0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

  _selectoption = false;
  _iamenabled = true;
  _max_value = int(MAXPERC/2);
  
  ui->setupUi(this);
  this->setWindowTitle("Power Project");
  
  _info_label = new QLabel(tr("<i>Choose a menu option, or right-click to "
                            "invoke a context menu</i>"));
  _info_label->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  _info_label->setAlignment(Qt::AlignCenter);
  
  createactions();
  createmenus();
  
  QWidget * centralwdg = new QWidget(this);

  _line10 = new QFrame(centralwdg);
  _line10->setObjectName(QString::fromUtf8("line"));
  _line10->setGeometry(QRect(320, 150, 118, 3));
  _line10->setFrameShape(QFrame::HLine);
  _line10->setFrameShadow(QFrame::Sunken);

  _line40 = new QFrame(centralwdg);
  _line40->setObjectName(QString::fromUtf8("line"));
  _line40->setGeometry(QRect(320, 150, 118, 3));
  _line40->setFrameShape(QFrame::HLine);
  _line40->setFrameShadow(QFrame::Sunken);

  _line70 = new QFrame(centralwdg);
  _line70->setObjectName(QString::fromUtf8("line"));
  _line70->setGeometry(QRect(320, 150, 118, 3));
  _line70->setFrameShape(QFrame::HLine);
  _line70->setFrameShadow(QFrame::Sunken);

  _vlay = new QGridLayout(centralwdg);

  _accept = new QPushButton("Accept");
  _accept->setEnabled(false);
  _vlay->addWidget(_accept, 2, 0, 1, 1, 0);

  _refuse = new QPushButton("Refuse");
  _refuse->setEnabled(false);
  _vlay->addWidget(_refuse, 18, 0, 1, 1, 0);
  
  _bar = new QProgressBar();
  _bar->setOrientation(Qt::Vertical);
  _bar->setMinimum(MINPERC);
  _bar->setMaximum(MAXPERC);
  _bar->setValue(0);
  _bar->setTextVisible(true);
  
  _confwin = new ConfWindow(this);

  connect(_confwin, SIGNAL(IamClosing()), 
      this, SLOT(configure_is_closed()));
  
  _vlay->addWidget(_bar, 0, 1, 20, 1, 0);

  _vlay->addWidget(_line10, 18, 2, 1, 1, 0);
  _vlay->addWidget(_line40, 12, 2, 1, 1, 0);
  _vlay->addWidget(_line70, 6, 2, 1, 1, 0);
  
  centralwdg->setLayout(_vlay);
  
  setCentralWidget(centralwdg);

  _mainthread = new QThread(parent);
  _valrdr = new VReader();
  _valrdr->moveToThread(_mainthread);

  connect(_mainthread, SIGNAL(started()), _valrdr, SLOT(readvalue()));
  
  _mainthread->start();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::configure_is_closed ()
{
  _iamenabled = true;
  _max_value = _confwin->get_maxvalue();

  show();
}

void MainWindow::updateprogress(int val)
{
  if (_iamenabled)
  {
    setStyleSheet (getcolor(val));
    _bar->setValue(val);

    if (! _selectoption)
    {
      if (val >= (_max_value * 0.40)) 
      { 
        _selectoption = true;
        _accept->setEnabled(true);
        _refuse->setEnabled(true);
      }
    }
    else 
    {
      if (val >= (_max_value * 0.70))
      {

      }
      else if (val <= (_max_value * 0.10))
      {

      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//  PRIVATE
///////////////////////////////////////////////////////////////////////////////

void MainWindow::close()
{
  if ( _iamenabled )
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit PowerApp", "Quit ?",
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) 
      QApplication::quit();

    return;
  }
}

void MainWindow::save()
{
  if ( _iamenabled )
  {
    _info_label->setText(tr("Invoked <b>File|Save</b>"));
    
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save results"), "",
        tr("TXT file (*.txt)"));
    
    //std::cout << filename.toUtf8().constData() << std::endl;
    
    if (! (filename == ""))
    {
      if (QFile::exists(filename))
        QFile::remove(filename);
        
      QFile fp(filename);
      fp.open(QIODevice::WriteOnly);
      
      // TODO  
        
      fp.close();
    }
  }
}

void MainWindow::configure()
{
  if ( _iamenabled )
  {
    _selectoption = false;
    _accept->setEnabled(false);
    _refuse->setEnabled(false);
 
    hide();
    _iamenabled = false;
    _confwin->reset_maxvalue();
    _confwin->show();

    connect(_valrdr, SIGNAL(returnvalue(int)), 
        this, SLOT(updateprogress(int)));
    connect(_valrdr, SIGNAL(returnvalue(int)), 
        _confwin, SLOT(updateprogress(int)));
  }
}

void MainWindow::about()
{
  if ( _iamenabled )
  {
    _info_label->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About PowerApp"),
            tr("This is the Power project main Application created by "
              "<b>loriano at storchi dot org</b>"));
  }
}

void MainWindow::createactions()
{
  if ( _iamenabled )
  { 
    _save_act = new QAction(tr("&Save"), this);
    _save_act->setShortcuts(QKeySequence::Save);
    _save_act->setStatusTip(tr("Save result to disk"));
    connect(_save_act, &QAction::triggered, this, &MainWindow::save);
    
    _configure_act = new QAction(tr("&Configure"), this);
    _configure_act->setStatusTip(tr("Configure max value"));
    connect(_configure_act, &QAction::triggered, this, &MainWindow::configure);
    
    _exit_act = new QAction(tr("E&xit"), this);
    _exit_act->setShortcuts(QKeySequence::Quit);
    _exit_act->setStatusTip(tr("Exit from PowerApp"));
    connect(_exit_act, &QAction::triggered, this, &MainWindow::close);
    
    _about_act = new QAction(tr("&About"), this);
    _about_act->setStatusTip(tr("Show the application's About box"));
    connect( _about_act, &QAction::triggered, this, &MainWindow::about);
  }
}

void MainWindow::createmenus()
{
  if ( _iamenabled )
  {  
    _file_menu = menuBar()->addMenu(tr("&File"));
    _file_menu->addAction(_save_act);
    _file_menu->addAction(_configure_act);
    _file_menu->addSeparator();
    _file_menu->addAction(_exit_act);
   
    _help_menu = menuBar()->addMenu(tr("&Help"));
    _help_menu->addAction(_about_act);
  }
}

const QString MainWindow::getcolor (int value) const
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

  if (value <= _max_value )
    return basic + green;
  //else if (value > 30 && value < 60)
  //  return basic + yellow;
  else
    return basic + red;
}

void MainWindow::setmaxvalue(int inval)
{
  if (inval > MAXPERC || inval < MINPERC)
    _max_value = int(MAXPERC/2);
  else
    _max_value = inval;
}

int MainWindow::getmaxvalue() const
{
  return _max_value;
}
