#include <iostream>
#include <cstring>
#include <cstdlib>
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
  name[0] = '.'; //this and the next line is to remove the blank space
  name = strtok(name, ".");
  state = new char[strlen(s)+1];
  strcpy(state, s);
}

bool City::isEqual(City *c)
{
  if(strcmp(name, c->name)==0 )// && strcmp(state)
  {
    return true;
  }
    return false; 
}

void City::copyLocation(City *c)
{
  latitude = c->latitude;
  longitude = c->longitude;
  airport = c->airport;
  std::cout << latitude << " " << longitude <<" "<< name << " "<<airport<<"\n";
}

void City::deallocate()
{
  //delete [] name;
  //delete [] state;
  //delete this;
}

bool City::hasAirport()
{
  if(airport)
  {
    return true;
  }
    return false; 
}
