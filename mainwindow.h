#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "confwindow.h"

#include <QMenu>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QContextMenuEvent>

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

  private slots:
    void save();
    void about();
    void close();
    void configure();

    void increase();
    void decrease();

  private:
    bool _iamenabled;

    Ui::MainWindow *ui;
    QProgressBar * _bar;

    int _max_value;

    QMenu * _file_menu;
    QMenu * _help_menu;

    QAction * _save_act;
    QAction * _exit_act;
    QAction * _about_act;
    QAction * _configure_act;

    QLabel * _info_label;

    ConfWindow * _confwin;

    void createactions();
    void createmenus();

    const QString getcolor (int value) const;

    void setmaxvalue(int inval);
    int getmaxvalue() const;
};

#endif 
