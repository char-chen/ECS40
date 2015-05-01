#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "vector.h"
#include "plane.h"
using namespace std;

void run(const Vector *cities, const Plane *planes, int pCount);
int getChoice();
void calcDistance(const Vector *cities, char *a1, char *a2);
void determineAirportTraffic(const Vector *cities, char *a1);
void displayPlaneInformation(const Plane *planes, int count);
void addPlaneInformation();
void determineBestPlane();

int main()
{
  Vector cities;
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
  
  int pCount = 5;
  Plane myPlanes[10];
  ifstream planeFile("planes.dat", ios::binary);
  planeFile.read((char*)myPlanes, sizeof(Plane)*pCount);  
//  planeFile.seekg(0, planeFile.end);
//  int length = planeFile.tellg();
//  char *str = new char[length];
//  planeFile.seekg(0, planeFile.beg);
//  planeFile.read(str, length);
  planeFile.close();
  
  run(&cities, myPlanes, pCount);
  return 0;
} //main

void run(const Vector *cities, const Plane *planes, int c)
{
  while(true)
  {
    char a1[80]; 
    char a2[80];
    int choice = getChoice();
    
    if (choice == 1)
      calcDistance(cities, a1, a2);
    else //input = 2
      if (choice == 2)
        determineAirportTraffic(cities, a1);
    else //input = 3
      if (choice == 3)
        displayPlaneInformation(planes, c);
    else //input = 4
      if (choice == 4)
        addPlaneInformation();
    else
      if (choice == 5)
        determineBestPlane();
    else //input not valid
      if (choice == -1)
        continue;
    else //done
      break;
  } //prompt continuously
} //gets user input and return results

int getChoice()
{
  int input;
  cout << "\nFlight Simulator Menu\n";
  cout << "0. Done.\n";
  cout << "1. Determine distance and passengers between two airports.\n";
  cout << "2. Determine all traffic from one airport.\n";
  cout << "3. Display planes information.\n";
  cout << "4. Add plane information.\n";
  cout << "5. Determine best plane between two airports.\n";
  cout << "\nYour choice (0 - 5): ";
  cin >> input;
  cin.ignore(10000, '\n');

  if (input > 5 || input < 0)
  {
    cout << "Your choice must be between 0 and 2. Please try again." << endl;
    return -1;
  } //check if valid range 

  return input;
} //returns -1 if not valid

void calcDistance(const Vector *v, char *a1, char *a2)
{
  cout << "\nPlease enter two airport abbreviations (XXX XXX): "; 
  cin >> a1 >> a2;
  cin.ignore(1000, '\n');
  int a1index = v->findAirport(a1);
  int a2index = v->findAirport(a2);
  v->calcDistance(a1index, a2index);
} //distance and passengers between two airports

void determineAirportTraffic(const Vector *cities, char *a1)
{
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> a1;
  cin.ignore(1000, '\n'); 
  cities->calcAirportTraffic(cities->findAirport(a1));
} //traffic from airport

void displayPlaneInformation(const Plane *p, int count)
{
  cout << "\nPlane Information\n";
  cout << left << setw(12) << "Name" << setw(6) << "Pass." << setw(6) << "Range" 
       << setw(6) << "Speed" << setw(7) << "Fuel" << setw(6) << "MPG" << setw(6)
       << "$/mi" << setw(12) << "Price * 10^6" << endl;
  locale mylocale("");
  cout.imbue(mylocale); 
  for (int i = 0; i < count; i++)
    cout << p[i] << endl;
}

void addPlaneInformation()
{
  
}

void determineBestPlane()
{
  
}