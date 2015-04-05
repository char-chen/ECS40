#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"

City::City()
{
}

City::~City()
{
}

void City::initialize()
{
  longitude = -1;
  latitude = -1;
  population = -1;
  name = NULL;
  state = NULL;
  airport = NULL;
}

int City::readCity(FILE *f)
{
  char line[100];
  if(fgets(line, 100, f))
  {
    char *token;
    token = strtok(line, ",");
    name = new char[strlen(token)+1];
    strcpy(name, token);
    token = strtok(NULL, ",");
    state = new char[strlen(token)+1];
    strcpy(state, token);
    token = strtok(NULL, ",");
    population = atoi(token);
    return 1; 
  }
  else 
    return 0; 
}

void City::readAirport(char *line, char *s)
{
  airport = new char[4];
  airport = strtok(line, " []");  
  latitude = atof(strtok(NULL, "  "));
  longitude = atof(strtok(NULL, " "));
  name = strtok(NULL, ",");
  name[0] = '.'; //this and the next line is for removing blank space
  name = strtok(name, ".");
  state = new char[strlen(s)+1];
  strcpy(state, s);
}

bool City::isEqual(const City *c)
{
  if(!c->airport)
  {
    if(strcmp(name, c->name)==0 && strcmp(state, c->state)==0)
    {
      return true;
    }
      return false; 
  }
  else 
  {
    if(strcmp(airport, c->airport)==0)
    {
      return true;
    }
      return false;
  }
}

void City::copyLocation(const City *c)
{
  latitude = c->latitude;
  longitude = c->longitude;
  if(c->airport)
  {
    airport = new char[4];
    strcpy(airport,c->airport);
  }
}

bool City::hasAirport()
{
  //std::cout<<airport<< " "<< name << std::endl;
  if(airport)
  {
    return true;
  }
    return false; 
}

void City::setAirport(char *a)
{
  airport = new char[4];
  strcpy(airport, a);
}

int City::calcDistance(const City *c)
{
  double lo1 = longitude*M_PI/180;
  double lo2 = c->longitude*M_PI/180;
  double la1 = latitude*M_PI/180;
  double la2 = c->latitude*M_PI/180;
  double r = 3963;
  return acos(sin(la1)*sin(la2)+cos(la1)*cos(la2)*cos(lo1-lo2))*r;
}

int City::calcPassengers(const City *c)
{
  if(this->calcDistance(c) >= 100)
  {
    return (population*c->population)/250000000; 
  }
    return 0;
}

char* City::getCity()
{
  char *city = new char[strlen(name)+strlen(state)+3];
  strcpy(city, name);
  strcat(city, ", ");
  strcat(city, state);
  return city;
} 
void City::deallocate()
{
  delete this;
}
