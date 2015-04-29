#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"

using namespace std;

City::City()
{
  longitude = -1;
  latitude = -1;
  population = -1;
  name = NULL;
  state = NULL;
  airport[0] = '\0';
} //City

int City::readCity(ifstream& inf)
{
  char line[100];
  
  if (inf.getline(line, 100))
  {
    char *token;
    token = strtok(line, ",");
    name = new char[strlen(token) + 1];
    strcpy(name, token);
    token = strtok(NULL, ",");
    state = new char[strlen(token) + 1];
    strcpy(state, token);
    token = strtok(NULL, "");
    population = atof(token);
    return 1; 
  } //parsing line
  else //reach end of file
    return 0; 
} //readCity

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

bool City::isEqual(const City *c) const
{
  if (name && c->name)
    return strcmp(name, c->name) == 0 && strcmp(state, c->state) == 0;
  
  if (airport[0] && c->airport[0])
    return strcmp(airport, c->airport) == 0;

  return false;
} //isEqual

void City::copyLocation(const City *c)
{
  latitude = c->latitude;
  longitude = c->longitude;
  strcpy(airport, c->airport);
} //copyLocation

bool City::hasAirport()
{
  return airport[0] != '\0'; 
} //hasAirport

void City::setAirport(const char *a)
{
  strcpy(airport, a);
} //setAirport

void City::calcDistance(const City *c) const
{
  double lo1 = longitude * M_PI / 180;
  double lo2 = c->longitude * M_PI / 180;
  double la1 = latitude * M_PI / 180;
  double la2 = c->latitude * M_PI / 180;
  double r = 3963;
  int distance, passengers;
  distance = acos(sin(la1) * sin(la2) + cos(la1) * cos(la2) * cos(lo1-lo2)) * r;
  
  if (distance >= 100)
    passengers = (population * c->population) / 2500000000U;
  else //distance < 100
    passengers = 0;
  
  cout << passengers << " passengers fly the " << distance << " miles from\n"
    << name << ", " << state << " to " << c->name << ", " << c->state << ".\n";
} //calcDistance

int City::getPassengers(const City *c) const
{
  double lo1 = longitude * M_PI / 180;
  double lo2 = c->longitude * M_PI / 180;
  double la1 = latitude * M_PI / 180;
  double la2 = c->latitude * M_PI / 180;
  double r = 3963;
  int dist = acos(sin(la1) * sin(la2) + cos(la1) * cos(la2) * cos(lo1-lo2)) * r;
  int passengers;

  if (dist < 100)    
    passengers = 0;
  else // greater than or equal to 100
    passengers = (population * c->population) / 2500000000U;

  cout << name << ", " << state << ": " << passengers << endl;
  return passengers;
} //getPassengers

City::~City()
{
  if (name)
    delete [] name;
  
  if (state)
    delete [] state;
} //~City

City& City::operator=(const City& rhs)
{
  longitude = rhs.longitude;
  latitude = rhs.latitude;
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  state = new char[strlen(rhs.state) + 1];
  strcpy(state, rhs.state);
  strcpy(airport, rhs.airport);
  population = rhs.population;  
  return *this;
} //Copy assignment operator
