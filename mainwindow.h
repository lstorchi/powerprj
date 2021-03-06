#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "confwindow.h"

#include <QMenu>
#include <QLabel>
#include <QFrame>
#include <QMainWindow>
#include <QGridLayout>
#include <QProgressBar>
#include <QContextMenuEvent>

#include "valuereader.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void configure_is_closed();
    void updateprogress(int); 

  private slots:
    void save();
    void about();
    void close();
    void configure();

  private:
    bool _iamenabled, _selectoption;

    QGridLayout * _vlay;

    Ui::MainWindow *ui;
    QProgressBar * _bar;

    int _max_value;

    QMenu * _file_menu;
    QMenu * _help_menu;

    QPushButton * _accept, * _refuse;

    QAction * _save_act;
    QAction * _exit_act;
    QAction * _about_act;
    QAction * _configure_act;

    QLabel * _info_label;

    ConfWindow * _confwin;

    QThread * _mainthread;
    VReader * _valrdr;

    QFrame * _line10;
    QFrame * _line40;
    QFrame * _line70;

    void createactions();
    void createmenus();

    const QString getcolor (int value) const;

    void setmaxvalue(int inval);
    int getmaxvalue() const;
};

#endif 
