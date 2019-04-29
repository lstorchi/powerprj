#include <iostream>
#include <stdlib.h>

#include "valuereader.h"

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
    
    int val = 0;
    for (int i=0; i<1000000000; ++i)
      ++val;

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
