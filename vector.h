#ifndef VECTOR_H
  #define VECTOR_H

#include "city.h"

class Vector
{
public:
  City **cityArray;
  int count; //number of cities
  int size; //allocated size of cityArray
//public:
  Vector();
  ~Vector();
  void initialize();
  void readCities();
  void resize();
  void readAirports();
  void cleanCities();
  int findAirport(char *airport);
  int calcDistance(int ind1, int ind2);
  int calcPassengers(int ind1, int ind2);
  char* getCity(int index);
  void deallocate();
};
#endif
