#include <cmath>
#include "vector.h"

Vector::Vector()
{
  alloc = 10;
}

Vector::~Vector()
{

}

double Vector::getDistance(City c1, City c2)
{
  double lo1 = c1.getLong()*M_PI/180;
  double lo2 = c2.getLong()*M_PI/180;
  double la1 = c1.getLat()*M_PI/180;
  double la2 = c2.getLat()*M_PI/180;
  double r = 3963;
  return acos(sin(la1)*sin(la2)+cos(la1)*cos(la2)*cos(lo1-lo2))*r;
}


