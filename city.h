#ifndef CITY_H
  #define CITY_H

#include <cstdio>

class City
{
public:
  double longitude;
  double latitude;
  char *name;
  char *state;
  char *airport;
  double population;

//public:
  City();
  ~City();
  void initialize();
  int readCity(FILE *f); //returns 0 if end of file
  void readAirport(char *str, char *state);
  bool isEqual(City *c);
  void copyLocation(City *c);
  bool hasAirport();
  void setAirport();
  void deallocate();
};
#endif
