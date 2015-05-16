#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"
using namespace std;

City::City() : name(NULL), state(NULL)
{
  longitude = -1;
  latitude = -1;
  population = -1;
  airport[0] = '\0';
} //City default constructor

City::City(const City& rhs) : 
  longitude(rhs.longitude), 
  latitude(rhs.latitude),
  population(rhs.population)
{
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  state = new char[strlen(rhs.state) + 1];
  strcpy(state, rhs.state);
  airport[0] = '\0';
  strcpy(airport, rhs.airport);
} //City copy constructor 

istream& operator>>(istream& is, City& rhs)
{
  char line[100], *token;
  
  if  (!is.getline(line, 100) || !strstr(line, ","))
    return is;
  
  token = strtok(line, ",");
  
  if (token)
  {
    rhs.name = new char[strlen(token) + 1];
    strcpy(rhs.name, token);
    token = strtok(NULL, ",");
    rhs.state = new char[strlen(token) + 1];
    strcpy(rhs.state, token);
    rhs.population = atof(strtok(NULL, ",\n"));
  } //parsing line

  return is;
} //operator >>

void City::readAirport(char *line, char *s)
{
  strcpy(airport, strtok(line, " []"));  
  latitude = atof(strtok(NULL, " "));
  longitude = atof(strtok(NULL, " "));
  char* tok = strtok(NULL, ",");
  tok[0] = '$'; //for removing leading space character
  name = new char[strlen(tok)];
  strcpy(name, strtok(tok, "$"));
  state = new char[strlen(s) + 1];
  strcpy(state, s);
} //readAirport

bool City::operator==(const City& rhs) const
{
  if (name && rhs.name)
    return strcmp(name, rhs.name) == 0 && strcmp(state, rhs.state) == 0;
  
  if (airport[0] && rhs.airport[0])
    return strcmp(airport, rhs.airport) == 0;
  
  return false;
} //operator ==

bool City::operator<(const City& rhs) const
{
  return population < rhs.population;
} //operator <

void City::copyLocation(const City& c)
{
  latitude = c.latitude;
  longitude = c.longitude;
  strcpy(airport, c.airport);
} //copyLocation

bool City::hasAirport() const
{
  return airport[0] != '\0'; 
} //hasAirport

void City::setAirport(const char *a)
{
  strcpy(airport, a);
} //setAirport

int City::getDistance(const City& c) const
{
  double lo1 = longitude * M_PI / 180;
  double lo2 = c.longitude * M_PI / 180;
  double la1 = latitude * M_PI / 180;
  double la2 = c.latitude * M_PI / 180;
  double r = 3963;
  return acos(sin(la1) * sin(la2) + cos(la1) * cos(la2) * cos(lo1-lo2)) * r;
} //getDistance

int City::getPassengers(const City& c, int dist) const
{
  if (dist < 100)    
    return 0;
  else // greater than or equal to 100
    return (population * c.population) / 2500000000U;
} //getPassengers

void City::showDistance(const City& rhs) const
{
  int distance, passengers;
  distance = this->getDistance(rhs);
  passengers = this->getPassengers(rhs, distance);
  
  cout << passengers << " passengers fly the " << distance << " miles from\n" 
  << name << ", " << state << " to " << rhs.name << ", " << rhs.state << ".\n";
} //operator -

int City::showTraffic(const City& c) const
{
  int distance = this->getDistance(c);
  int passengers = this->getPassengers(c, distance);

  cout << name << ", " << state << ": " << passengers << endl;
  return passengers;
} //showTraffic

City::~City()
{
  if (name)
    delete [] name;
  
  if (state)
    delete [] state;
} //~City

City& City::operator=(const City& rhs)
{
  if (name)
    delete name;
  
  if (state)
    delete state;
  
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  state = new char[strlen(rhs.state) + 1];
  strcpy(state, rhs.state);
  strcpy(airport, rhs.airport);
  longitude = rhs.longitude;
  latitude = rhs.latitude;
  population = rhs.population;  
  return *this;
} //operator =
