#include <iostream>
#include <stdlib.h>

#include "valuereader.h"

#ifdef _WIN32
#include <windows.h>

namespace 
{
  void mysleep(unsigned milliseconds)
  {              
    Sleep(milliseconds);
  }
}

#else
#include <unistd.h>

namespace
{
  void mysleep(unsigned milliseconds)
  {
    usleep(milliseconds * 1000);   
  }
}
#endif

VReader::VReader()
{
  _value = 0;
  
  return;  
}
    
VReader::~VReader() 
{
  return;
}

void VReader::readvalue ()
{
  while(1)
  {
    _value = read_the_value ();
    
    mysleep(1000);

    emit(returnvalue(_value));
  }
}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE 
///////////////////////////////////////////////////////////////////////////////

int VReader::read_the_value ()
{
  int r = (rand() % 100) + 1;

  return r;
}
