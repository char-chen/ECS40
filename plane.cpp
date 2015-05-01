#include <iostream>
#include <iomanip>
#include "plane.h"
using namespace std;

Plane::Plane()
{
}

ostream& operator<<(ostream& os, const Plane& rhs)
{
  os << left << setw(12) << rhs.name << setw(6) << rhs.passengers << setw(6) 
     << rhs.range << setw(6) << rhs.speed << right << setw(7) << rhs.fuel << setw(6);
  
  return os;
}