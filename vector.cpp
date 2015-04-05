#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "vector.h"

using namespace std;

Vector::Vector()
{
  count = 0;
  size = 10;
}

Vector::~Vector()
{
}

void Vector::initialize()
{
  cityArray = new City*[size];
  for(int i = 0; i < size; i++)
  {
    cityArray[i] = new City();
    cityArray[i]->initialize();
  } 
}

void Vector::readCities()
{
  FILE *cityFile = fopen("citypopulations.csv", "r");
  while(cityArray[count]->readCity(cityFile))
  {
    count++;
    if(count >= size)
    {
      resize();
    }
  } 
  fclose(cityFile);        
}

void Vector::resize()
{
  size *= 2;
  City **cityArrayTemp = new City*[size];
  for(int i = 0; i < count; i++)
  {
    cityArrayTemp[i] = cityArray[i];
  }
  for(int i = count; i < size; i++)
  {
    cityArrayTemp[i] = new City();
    cityArrayTemp[i]->initialize();
  }
  delete [] cityArray;
  cityArray = cityArrayTemp;
}

void Vector::readAirports()
{
  FILE *airportFile = fopen("airportLL.txt", "r");
  char line[50];
  char *state = NULL;
  fgets(line, 50, airportFile); //to skip the first line;
  while(fgets(line, 50, airportFile)) 
  {
    if(line[0] >= 'A' && line[0] <= 'Z')
    {
      if(state)
        delete state;
      //copies line over except its new line character \n
      int s = strlen(line)-1;
      state = new char[s];
      for(int i = 0; i < s; i++)
      {
        state[i] = line[i];
      }
      state[s-1] = '\0';
    }
    if(line[0] == '[')
    {
      City *test = new City();
      test->initialize();
      test->readAirport(line, state);
      for(int i = 0 ; i < count ; i++)
      {
        if(test->isEqual(cityArray[i]))
        {       
          cityArray[i]->copyLocation(test);
        } 
      }
      test->deallocate();
    } 
  }
}

void Vector::cleanCities()
{
  for(int i = 0; i < count; i++)
  {
    if(!cityArray[i]->hasAirport())
    {
      cityArray[i]->deallocate();
    }
  }
}

int Vector::findAirport(char *a)
{
  City *temp = new City();
  if(strlen(a) != 3)
  {
    return -1;
  } 
  temp->setAirport(a);
  for(int i = 0; i < count ; i++)
  {
    if(temp->isEqual(cityArray[i]))
    {
      return i;
    } 
  }
  temp->deallocate();
  return -1;
}

int Vector::calcDistance(int ind1, int ind2)
{
  return cityArray[ind1]->calcDistance(cityArray[ind2]);
}

int Vector::calcPassengers(int ind1, int ind2)
{
  return cityArray[ind1]->calcPassengers(cityArray[ind2]);
}

char *Vector::getCity(int i)
{
  return cityArray[i]->getCity();
}

void Vector::deallocate()
{
  delete this;
}
