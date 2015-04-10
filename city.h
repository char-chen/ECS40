#ifndef CITY_H
  #define CITY_H

#include <cstdio>

class City
{
public:
  double longitude;
  double latitude;
  char* name;
  char* state;
  char airport[4];
  double population;
//public:
  //City();
  //~City();
  void initialize();
  int readCty(FILE *f); //returns 0 if end of file
  void readAirport(char *str, char *s); //s = STATE 
  bool isEqual(const City *c);
  void copyLocation(const City *c);
  bool hasAirport();
  void setAirport(const char *a); //a = AIRPORT
  void calcDistance(const City *c);
  void deallocate();
}; //class City
#endif
