#include <iostream>
#include <cstring>
#include "airport.h"
using namespace std;
bool Flight::operator==(const Flight& rhs) const
{
  return strcmp(destAirport, rhs.destAirport) == 0; 
}
