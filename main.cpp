#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "vector.h"
#include "plane.h"
using namespace std;

void run(const Vector& cities, Plane *planes, int& pCount);
int getChoice();
void calcDistance(const Vector& cities);
void determineAirportTraffic(const Vector& cities);
void displayPlaneInformation(const Plane *planes, int count);
void addPlaneInformation(Plane *planes, int &count);
void determineBestPlane(const Vector& cities, const Plane *planes, int count);

int main()
{
  Vector cities;
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
  
  int pCount = 0;
  Plane myPlanes[10];
  Plane *p = myPlanes;
  ifstream planeFile("planes.dat", ios::binary);
  
  if (planeFile)
  { 
    while (!planeFile.eof())
    {
      planeFile.read((char*)p, sizeof(Plane)); 
      p++;
      pCount++;
    } //parse lines
    
    planeFile.close();
    pCount--;
  } //file exists

  run(cities, myPlanes, pCount);
  return 0;
} //main

void run(const Vector& cities, Plane *planes, int& c)
{
  while(true)
  {
    int choice = getChoice();
    
    if (choice == 1)
      calcDistance(cities);
    else //input = 2
      if (choice == 2)
        determineAirportTraffic(cities);
    else //input = 3
      if (choice == 3)
        displayPlaneInformation(planes, c);
    else //input = 4
      if (choice == 4)
        addPlaneInformation(planes, c);
    else //input = 5
      if (choice == 5)
        determineBestPlane(cities, planes, c);
    else //input not valid
      if (choice == -1)
        continue;
    else //done
      break;
  } //prompt continuously
} //Gets user input and return results

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

void calcDistance(const Vector& v)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): "; 
  cin >> a1 >> a2;
  cin.ignore(1000, '\n');
  int a1index = v.findAirport(a1);
  int a2index = v.findAirport(a2);
  v.calcDistance(a1index, a2index, NULL, 0);
} //Dispaly distance and number of passengers between two airports

void determineAirportTraffic(const Vector& v)
{
  char airport[80];
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  cin.ignore(1000, '\n'); 
  v.calcAirportTraffic(v.findAirport(airport));
} //Display all traffic from airport

void displayPlaneInformation(const Plane *p, int count)
{
  cout << "\nPlane Information\n";
  cout << left << setw(12) << "Name" << setw(6) << "Pass." << setw(6) << "Range" 
       << setw(6) << "Speed" << setw(6) << "Fuel" << " " << setw(5) << "MPG" 
       << " " << setw(5) << "$/mi" << " " << setw(12) << "Price * 10^6" << endl;
  cout.imbue(locale("")); 

  for (int i = 0; i < count; i++)
    cout << p[i] << endl;
} //Display information of all existing planes

void addPlaneInformation(Plane *p, int& count)
{
  p[count++].input();
} //User-defined airplane

void determineBestPlane(const Vector& v, const Plane *p, int count)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> a1 >> a2;
  cin.ignore(1000, '\n');
  int a1Index = v.findAirport(a1);
  int a2Index = v.findAirport(a2);
  cout << setw(11) << left << "Passengers" << setw(7) << "Miles" << setw(6) << "Trips"
       << setw(10) << "Name" << setw(7) << "Cost" << endl;
  v.calcDistance(a1Index, a2Index, p, count);
} //Determine the best plane for a given route 
