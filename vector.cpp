#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
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
  }
  delete [] cityArray;
  cityArray = cityArrayTemp;
}

void Vector::readAirports()
{
  
  FILE *airportFile = fopen("airportLL.txt", "r");
  char line[100];
  char *state;
  fgets(line, 100, airportFile); //to skip the first line;
  while(fgets(line, 100, airportFile)) 
  {
    if(line[0] >= 'A' && line[0] <= 'Z')
    {
      state = strtok(line, "\n");
    }   
    if(line[0] == '[')
    {
      //cout << state << endl;
      City *test = new City();
      test->initialize();
      test->readAirport(line, state);
      for(int i = 0 ; i < count ; i++)
      {
        if(test->isEqual(cityArray[i]))
        {
          cityArray[i]->copyLocation(test); 
          //cout << cityArray[i]->airport << " "<< cityArray[i]->name << " "<<cityArray[i]->airport<<" "<<cityArray[i]->state<<endl;
        } 
      }
      test->deallocate();
      delete test;
    } 
  }
}

void Vector::cleanCities()
{
  for(int i = 0; i < count; i++)
  {
    if(cityArray[i]->hasAirport())
    {
      cout << "p";
      //cout << cityArray[i]->name << " " << cityArray[i]->airport << endl;
    }
  }
}
double Vector::calcDistance(City c1, City c2)
{
  /*double lo1 = c1.getLong()*M_PI/180;
  double lo2 = c2.getLong()*M_PI/180;
  double la1 = c1.getLat()*M_PI/180;
  double la2 = c2.getLat()*M_PI/180;
  double r = 3963*/
  return 0; //acos(sin(la1)*sin(la2)+cos(la1)*cos(la2)*cos(lo1-lo2))*r;
}
