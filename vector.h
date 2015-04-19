#ifndef VECTOR_H
  #define VECTOR_H

#include "city.h"

class Vector
{
  City *cityArray;
  int count; //number of cities
  int size; //allocated size of cityArray
public:
  //Vector();
  //~Vector();
  void initialize();
  void readCities();
  void resize();
  void readAirports();
  void cleanCities();
  int findAirport(const char *airport) const;
  void calcDistance(int ind1, int ind2) const;
  void deallocate();
}; //class Vector
#endif
