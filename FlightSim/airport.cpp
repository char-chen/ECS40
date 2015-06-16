#include <iostream>
#include <cstring>
#include "airport.h"
using namespace std;

void Airport::readFlights(ifstream& inf)
{
  int num = 0;
  inf >> num;
  
  for (int i = 0; i < num; i++)
  {
    Flight flight;
    char airline[10];
    inf >> airline >> flight.destAirport;
    strncpy(flight.airline, airline, 2); 
    flight.airline[2] = '\0';
    routes += flight;
  } //parsing
  
  inf.ignore(1000, '\n');
} //readFlights

void Airport::findRoute(const Airport& destination, const List<Airport>& cities,
                        List<Flight>& results, const char* airline, 
                        bool& found) const
{
  int i, j;
  
  for (i = 0; i < cities.getCount(); i++)
    if (cities[i] == *this)
      break;
  
  for (j = 0; j < cities[i].routes.getCount(); j++)
  {
    if (strcmp(cities[i].routes[j].airline, airline) == 0)  
    {   
      if (strcmp(cities[i].routes[j].destAirport, destination.airport) == 0)
      {
        found = true;
        results += cities[i].routes[j]; 
        return;
      } //destination found
          
      Airport temp;
      temp.setAirport(cities[i].routes[j].destAirport);   
      temp.findRoute(destination, cities, results, airline, found);
          
      if (found)
        results += cities[i].routes[j];
    } //Search for same airline, recursively traverse all nodes.
  } //traverse routes
} //findRoute

ostream& operator<<(ostream& os, const Airport& rhs)
{
  os << rhs.airport << ": ";

  for (int i = 0; i < rhs.routes.getCount(); i++)
    os << rhs.routes[i];

  return os;
} //operator <<

bool Flight::operator<(const Flight& rhs) const
{
  return false;
} //operator <

ostream& operator<<(ostream& os, const Flight& rhs)
{
  os << rhs.airline << "-" << rhs.destAirport << " ";
  return os;
} //operator <<
