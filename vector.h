#ifndef VECTOR_H
  #define VECTOR_H

#include "city.h"

class Vector
{
  City **cityArray;
  int count; //number of cities
  int size; //allocated size of cityArray
public:
  Vector();
  ~Vector();
  void initialize();
  void readCities();
  void resize();
  void readAirports();
  void cleanCities();
  void findAirport();
  double calcDistance(City c1, City c2);
  void deallocate();
};
#endif
