#ifndef _INC_VALUERREADER_
#define _INC_VALUERREADER_

#include <QObject>

class VReader : public QObject
{    
    Q_OBJECT

  public:    
    VReader();
    virtual ~VReader();

  public slots:
    void readvalue();

  signals:
    void returnvalue(int); 
  
  private:
    int _value;

    int read_the_value();
};

#endif
