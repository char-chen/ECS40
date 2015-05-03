#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "vector.h"
using namespace std;

Vector::Vector()
{ 
  count = 0;
  size = 10;
  cityArray = new City[size]; 
} //Vector

void Vector::readCities()
{
  ifstream cityFile("citypopulations.csv");

  while(cityArray[count].readCity(cityFile))
  {
    count++;
    
    if (count == size)
      resize();
  } //parsing lines from file
  
  cityFile.close();     
} //readCities

void Vector::resize()
{
  size *= 2;
  City *cityArrayTemp = new City[size];

  for (int i = 0; i < count; i++)
    cityArrayTemp[i] = cityArray[i];
  
  delete [] cityArray; 
  cityArray = cityArrayTemp;
} //resize

void Vector::readAirports()
{
  ifstream airportFile("airportLL.txt");
  char line[50];
  char *state = NULL;
  airportFile.getline(line, 50); //to skip the first line;
  
  while(airportFile.getline(line, 50)) 
  {
    if (line[0] >= 'A' && line[0] <= 'Z')
    {
      if (state)
        delete state;
        
      state = new char[strlen(line) + 1];
      strcpy(state, line);
    } //state line
    
    if (line[0] == '[')
    {
      City test;
      test.readAirport(line, state);
      
      for (int i = 0 ; i < count ; i++)
        if (test.isEqual(cityArray[i]))
          cityArray[i].copyLocation(test);
    } //airport line
  } //parsing each line in file 
} //readAirports

void Vector::cleanCities()
{
  City *cityArrayTemp = new City[count];
  int t = 0; //size of temp array
 
  for (int i = 0; i < count; i++)
  {
    if (cityArray[i].hasAirport())
    {
      cityArrayTemp[t] = cityArray[i];
      t++;
    } //copy to new array for city with airport
  } //for each element in cityArray

  delete [] cityArray;
  cityArray = cityArrayTemp;
  count = t;
} //cleanCities

int Vector::findAirport(const char *a) const
{
  if (strlen(a) != 3)
  {
    cout << a << " is not a valid airport." << endl;
    return -1;
  } //size must be 3 to be valid 

  City temp;
  temp.setAirport(a);
  
  for (int i = 0; i < count ; i++)
    if (temp.isEqual(cityArray[i]))
      return i;
 
  cout << a << " is not a valid airport." << endl;
  return -1;
} //findAirport

void Vector::calcDistance(int ind1, int ind2, int *d, int *p) const
{
  if (ind1 != -1 && ind2 != -1)
  {
    if (d && p)
    {
      *d = cityArray[ind1].getDistance(cityArray[ind2]);
      *p = cityArray[ind1].getPassengers(cityArray[ind2], *d);
      
      if (*p != 0)
      {
        cout << setw(11) << left << "Passengers" << setw(7) << "Miles" 
             << setw(6) << "Trips" << setw(10) << "Name" << setw(7) << "Cost";
        cout << endl << setw(11) << *p << setw(7) << *d;
      } //has flights
      else //no flight
        cout << "No planes available" << endl;
    } //to determine best plane
    else //calc
      cityArray[ind1].showDistance(cityArray[ind2]);
  } //if valid
} //calcDistance

void Vector::calcAirportTraffic(int index) const
{
  int total = 0;

  if (index != -1)
  {
    for (int i = 0; i < count; i++)
      if (i != index)
        total += cityArray[i].showTraffic(cityArray[index]);
    
    cout << "Total passengers: " << total << endl;  
  } //valid index returned from Vector::findAirport() 
} //calcAirportTraffic

Vector::~Vector()
{
  delete [] cityArray;
} //~Vector
