#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "vector.h"
#include "plane.h"
using namespace std;

void readPlanes(Plane *planes, int& pCount);
void run(const Vector& cities, Plane *planes, int& pCount);
int getChoice();
void calcDistance(const Vector& cities);
void determineAirportTraffic(const Vector& cities);
void displayPlaneInformation(const Plane *planes, int count);
void addPlaneInformation(Plane *planes, int& count);
void determineBestPlane(const Vector& cities, const Plane *p, int ct);

void readPlanes(Plane *planes, int& pCount)
{
  ifstream planeFile("planes.dat", ios::binary);
  
  if (planeFile)
  {
    for (Plane *p = planes; !planeFile.eof(); p++)
    {
      planeFile.read((char*)p, sizeof(Plane)); 
      pCount++;
    } //parse lines
    
    planeFile.close();
    pCount--;
  } //file exists
} //readPlanes

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
  int a1index = v.findAirport(a1);
  int a2index = v.findAirport(a2);
  v.calcDistance(a1index, a2index, NULL, NULL, -1);
} //Dispaly distance and number of passengers between two airports

void determineAirportTraffic(const Vector& v)
{
  char airport[80];
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  v.calcAirportTraffic(v.findAirport(airport));
} //Display all traffic from airport

void displayPlaneInformation(const Plane *planes, int count)
{
  cout << "\nPlane Information\n";
  cout.imbue(locale(""));
  cout << left << setw(12) << "Name" << setw(6) << "Pass." << setw(6) << "Range"
       << setw(6) << "Speed" << setw(6) << "Fuel" << " " << setw(5) << "MPG" 
       << " " << setw(5) << "$/mi" << " " << setw(12) << "Price * 10^6" << endl;
  
  for (int i = 0; i < count; i++)
    cout << planes[i] << endl;

} //Display information of all existing planes

void addPlaneInformation(Plane *p, int& count)
{
  p[count++].input();
} //User-defined airplane

void determineBestPlane(const Vector& v, const Plane *pArr, int count)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> a1 >> a2;
  int a1Index = v.findAirport(a1);
  int a2Index = v.findAirport(a2);
  int distance = 0;
  int passengers = 0;
  cout.imbue(locale("C"));
  v.calcDistance(a1Index, a2Index, &distance, &passengers, count);
   
  if (passengers != 0 && count > 0)
  {
    int lowestCost = 1e9, best;
  
    for (int i = 0; i < count; i++)
    { 
      int cost = pArr[i].getCost(passengers, distance);

      if ( cost != -1 && cost < lowestCost)
      {
        lowestCost = cost;
        best = i; 
      } //if lower
    } //for each plane in planeArray
   
    int t = pArr[best].getTrips((double)passengers);
    cout << setw(6) << t << setw(10) << pArr[best].getName()
    << "$" << lowestCost << endl;
  } //planes available
} //Determine the best plane for a given route 

int main()
{
  Vector cities;
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
   
  int planeCount = 0;
  Plane myPlanes[10];
  readPlanes(myPlanes, planeCount);
  run(cities, myPlanes, planeCount);
  return 0;
} //main
