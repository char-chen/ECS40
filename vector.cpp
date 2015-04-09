#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "vector.h"

using namespace std;

void Vector::initialize()
{ 
  count = 0;
  size = 10;
  cityArray = new City[size];

  for (int i = 0; i < size; i++)
  {
    cityArray[i].initialize();
  } //for each element in cityArray 
} //initialize

void Vector::readCities()
{
  FILE *cityFile = fopen("citypopulations.csv", "r");

  while(cityArray[count].readCty(cityFile))
  {
    count++;

    if (count >= size)
    {
      resize();
    } //resize if reach size limit
  } //parsing lines from file

  fclose(cityFile);        
} //readCities

void Vector::resize()
{
  size *= 2;
  City *cityArrayTemp = new City[size];

  for (int i = 0; i < count; i++)
  {
    cityArrayTemp[i] = cityArray[i];
    //cityArray[i].deallocate();
  } //upper half of cityArray

  for (int i = count; i < size; i++)
  {
    cityArrayTemp[i].initialize();
  } //lower half of cityArray
  
  cityArray = cityArrayTemp;
} //resize

void Vector::readAirports()
{
  FILE *airportFile = fopen("airportLL.txt", "r");
  char line[50];
  char *state = NULL;
  fgets(line, 50, airportFile); //to skip the first line;
  
  while(fgets(line, 50, airportFile)) 
  {
    if (line[0] >= 'A' && line[0] <= 'Z')
    {
      if (state)
        delete state;
      //copies line over except its new line character \n
      state = new char[strlen(line)];
      strcpy(state, strtok(line, "\n"));
    } //state line

    if (line[0] == '[')
    {
      City test;
      test.initialize();
      test.readAirport(line, state);

      for (int i = 0 ; i < count ; i++)
      {
        if (test.isEqual(&cityArray[i]))
        {       
          cityArray[i].copyLocation(&test);
        } //check city
      } //for each element in cityArry

      //test.deallocate();
    } //airport line
  } //parsing each line in file
} //readAirports

void Vector::cleanCities()
{
  for (int i = 0; i < count; i++)
  {
    if (!cityArray[i].hasAirport())
    {
      cityArray[i].deallocate();

      for (int j = count-1; j > i; j--)
      {
        if (cityArray[j].hasAirport())
        {
          //cout << cityArray[i].name << cityArray[i].state <<endl;
          cityArray[i] = cityArray[j];
          //cityArray[j].deallocate();
          count--;
          break;
        } //has airport
      } //searching for replacement, from last
    } //delete if airport = NULL
  } //for each element in cityArray
} //cleanCities

int Vector::findAirport(char *a)
{
  if (strlen(a) != 3)
  {
    return -1;
  } //size must be 3 to be valid 

  City temp;
  temp.setAirport(a);
  
  for (int i = 0; i < count-1 ; i++)
  {
    if (temp.isEqual(&cityArray[i]))
    {
      return i;
    } //check if equal
    
  } //for each element of cityArray
 
  temp.deallocate();
  return -1;
} //findAirport

void Vector::calcDistance(int ind1, int ind2) const
{
  cityArray[ind1].calcDistance(&cityArray[ind2]);
} //calcDistance

void Vector::deallocate()
{
  for (int i = 0; i < size; i++)
  {
    //cityArray[i].deallocate();
  } //for each element in cityArray

  delete [] cityArray;
} //deallocate
