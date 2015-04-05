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
  bool isEqual(const City *c);
  void copyLocation(const City *c);
  bool hasAirport();
  void setAirport(char *airport);
  int calcDistance(const City *c);
  int calcPassengers(const City *c);
  char* getCity();
  void deallocate();
};
#endif
