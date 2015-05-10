#ifndef CITY_H
  #define CITY_H

#include <iostream>
using namespace std;

class City
{
public:
  double longitude;
  double latitude;
  char *name;
  char *state;
  char airport[4];
  double population;
//public:
  City();
  City(const City& rhs);
  ~City();
  friend istream& operator>>(istream& is, City& rhs);
  void readAirport(char *str, char *state);
  bool operator==(const City& city) const;
  void copyLocation(const City& city);
  bool hasAirport() const;
  void setAirport(const char *airport);
  int getDistance(const City& city) const;
  int getPassengers(const City& city, int dist) const;
  void showDistance(const City& city) const;
  int showTraffic(const City& city) const;
  City& operator=(const City& rhs);
}; //class City
#endif
