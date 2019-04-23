#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void increase();
    void decrease();

  private slots:
    void save();
    void about();

  private:
    Ui::MainWindow *ui;
    QProgressBar * _bar;

    QMenu * _file_menu;
    QMenu * _help_menu;

    QAction * _save_act;
    QAction * _exit_act;
    QAction * _about_act;

    QLabel * _info_label;

    void createactions();
    void createmenus();
};

#endif // MAINWINDOW_H
