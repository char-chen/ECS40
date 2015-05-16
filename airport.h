#ifndef AIRPORT_H
  #define AIRPORT_H

#include <fstream>
#include "city.h"
#include "list.h"
using namespace std;

class Flight;

class Airport : public City
{
  List<Flight> flights;
public:
  void readFlights(ifstream& file);
}; //class Airport

class Flight
{
  char airline[3];
  char destAirport[4];
public: 
  bool operator<(const Flight& rhs) const;
  friend class Airport;
}; //class Flight
#endif 
