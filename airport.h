#ifndef AIRPORT_H
  #define AIRPORT_H

#include <iostream>
#include <fstream>
#include "city.h"
#include "list.h"
using namespace std;

class Airport;

class Flight
{
  friend class Airport;
  char airline[3];
  char destAirport[4];
public: 
  bool operator<(const Flight& rhs) const;
  friend ostream& operator<<(ostream& os, const Flight& rhs); 
}; //class Flight

class Airport : public City
{
  List<Flight> flights;
public:
  void readFlights(ifstream& file);
  friend ostream& operator<<(ostream& os, const Airport& rhs); 
}; //class Airport
#endif 
