#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"

using namespace std;

void City::initialize()
{
  longitude = -1;
  latitude = -1;
  population = -1;
  name = NULL;
  state = NULL;
  airport = NULL;
} //initialize

int City::readCty(FILE *f)
{
  char line[100];
  
  if (fgets(line, 100, f))
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
  airport = strtok(line, " []");  
  latitude = atof(strtok(NULL, " "));
  longitude = atof(strtok(NULL, " "));
  name = strtok(NULL, ",");
  name[0] = '.'; //this and the next line is for removing blank space
  name = strtok(name, ".");
  state = new char[strlen(s) + 1];
  strcpy(state, s);
} //readAirport

bool City::isEqual(const City *c)
{
  if (!c->airport)
  {
    if (strcmp(name, c->name) == 0 && strcmp(state, c->state) == 0)
    {
      return true;
    } //if same city

      return false; 
  } //if airport not set
  else //if airport set 
  {
    if (strcmp(airport, c->airport) == 0)
    {
      return true;
    } //if same airport

      return false;
  } //not same airport 
} //isEqual

void City::copyLocation(const City *c)
{
  latitude = c->latitude;
  longitude = c->longitude;

  if (c->airport)
  {
    airport = new char[4];
    strcpy(airport, c->airport);
  } //if airport set
} //copyLocation

bool City::hasAirport()
{
  if (airport)
  {
    return true;
  } //if airport NULL

    return false; 
} //hasAirport

void City::setAirport(const char *a)
{
  airport = new char[4];
  strcpy(airport, a);
} //setAirport

void City::calcDistance(const City *c)
{
  double lo1 = longitude * M_PI / 180;
  double lo2 = c->longitude * M_PI / 180;
  double la1 = latitude * M_PI / 180;
  double la2 = c->latitude * M_PI / 180;
  double r = 3963;
  int distance, passengers;
  distance = acos(sin(la1) * sin(la2) + cos(la1) * cos(la2) * cos(lo1-lo2)) * r;
  
  if (distance >= 100)
  {
    passengers = (population * c->population) / 250000000;
  } //if distance >= 100, calc populatoin
  else //distance < 100
    passengers = 0;
  
  cout << passengers << " passengers fly the " << distance << " miles from\n"
  << name << "," << state << " to " << c->name << "," << c->state << endl;
  
} //calcDistance

void City::deallocate()
{
  if (name)
    delete [] name;

  if (state)
    delete [] state;
  
} //deallocate
