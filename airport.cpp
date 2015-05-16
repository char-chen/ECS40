#include <iostream>
#include <cstring>
#include "airport.h"
using namespace std;

void Airport::readFlights(ifstream& inf)
{
  int num;
  inf >> num;

  for (int i = 0; i < num; i++)
  {
    Flight flight;
    inf >> flight.airline >> flight.destAirport;
    flights += flight;
  } //parsing 
} //readFlights

bool Flight::operator<(const Flight& rhs) const
{
  return strcmp(airline, rhs.airline) < 0; 
} //operator <
