#ifndef VECTOR_H
  #define VECTOR_H

#include "city.h"

class Vector
{
  City *cityArray;
  int count; //number of cities
  int size; //allocated size of cityArray
  void resize();
public:
  Vector();
  ~Vector();
  void readCities();
  void readAirports();
  void cleanCities();
  int findAirport(const char *airport) const;
  void calcDistance(int ind1, int ind2, int *dist, int *pass, int p) const;
  void calcAirportTraffic(int index) const;
}; //class Vector
#endif
