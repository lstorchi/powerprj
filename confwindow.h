#ifndef CONFWINDOW_H
#define CONFWINDOW_H

#include <QDialog>
#include <QProgressBar>

#include "ui_confwindow.h"

namespace Ui {
  class ConfWindow;
}

class ConfWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit ConfWindow(QWidget *parent = nullptr);
    ~ConfWindow();

    int get_maxvalue() const;

  protected:
    void closeEvent( QCloseEvent* event ) override;

  public slots:
    void updateprogress(int);

  signals:
    void IamClosing();

  private:
    Ui::ConfWindow *ui;
 
    QProgressBar * _bar;

    int _maxvalue;
};

#endif 
