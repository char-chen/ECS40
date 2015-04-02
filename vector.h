#ifndef VECTOR_H
  #define VECTOR_H

#include "city.h"

class Vector
{
  City **cityArray;
  int size;
  int alloc;
public:
  Vector();
  ~Vector();
  double getDistance(City c1, City c2);
};
#endif
