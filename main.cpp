#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "list.h"
#include "city.h"
#include "plane.h"
using namespace std;

void readPlanes(Plane *planes, int& pCount);
void run(const List<City>& cities, Plane *planes, int& pCount);
int getChoice();
void calcDistance(const List<City>& cities);
void determineAirportTraffic(const List<City>& cities);
void displayPlaneInformation(const Plane planes[10], int ct);
void addPlaneInformation(Plane *planes, int& ct);
void determineBestPlane(const List<City>& cities, const Plane p[10], int ct);
void readCities(List<City>& cities);
void readAirports(List<City>& cities);
void cleanCities(List<City>& cities);
int findAirport(const List<City>& cities, const char *a);
void calcDistance(const List<City>& cities, int id1, int id2, int *d, int *p, 
                  int c, int m);
void calcAirportTraffic(const List<City>& cities, int index);

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

void run(const List<City>& cities, Plane *planes, int& c)
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

void calcDistance(const List<City>& v)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): "; 
  cin >> a1 >> a2;
  int a1index = findAirport(v, a1);
  int a2index = findAirport(v, a2);
  calcDistance(v, a1index, a2index, NULL, NULL, -1, -1);
} //Dispaly distance and number of passengers between two airports

void determineAirportTraffic(const List<City>& v)
{
  char airport[80];
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  calcAirportTraffic(v, findAirport(v, airport));
} //Display all traffic from airport

void displayPlaneInformation(const Plane planes[10], int pCount)
{
  cout << "\nPlane Information\n";
  cout.imbue(locale(""));
  cout << left << setw(12) << "Name" << setw(6) << "Pass." << setw(6) << "Range"
       << setw(6) << "Speed" << setw(6) << "Fuel" << " " << setw(5) << "MPG" 
       << " " << setw(5) << "$/mi" << " " << setw(12) << "Price * 10^6" << endl;
  
  for (int i = 0; i < pCount; i++)
    cout << planes[i] << endl;
} //Display information of all existing planes

void addPlaneInformation(Plane *p, int& pCount)
{
  p[pCount++].inputPlane();
} //User-defined airplane

void determineBestPlane(const List<City>& v, const Plane pArr[10], int pCount)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> a1 >> a2;
  int a1Index = findAirport(v, a1);
  int a2Index = findAirport(v, a2);
  int distance = 0, passengers = 0;
  int maxRange = -1;
  
  for (int i = 0; i < pCount; i++)
    if (pArr[i].getRange() > maxRange)
      maxRange = pArr[i].getRange();

  cout.imbue(locale("C"));
  calcDistance(v, a1Index, a2Index, &distance, &passengers, pCount, maxRange);
  
  if (passengers != 0 && pCount > 0)
  {
    int lowestCost = 1e9, best;
  
    for (int i = 0; i < pCount; i++)
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

void readCities(List<City>& cities)
{
  ifstream cityFile("citypopulations.csv");
  
  while (!cityFile.eof())
  {
    City temp;
    cityFile >> temp;
  
    if (cityFile)
      cities += temp;
  } //parsing
  
  cityFile.close();     
} //readCities

void readAirports(List<City>& cities)
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
      
      for (int i = 0; i < List<City>::getCount(); i++)
        if (test == cities[i])
          cities[i].copyLocation(test);
    } //airport line
  } //parsing each line in file 
} //readAirports

void cleanCities(List<City>& cities)
{
  for (int i = 0; i < List<City>::getCount(); i++)
    if (!cities[i].hasAirport())
        cities -= cities[i--];
} //cleanCities

int findAirport(const List<City>& cities, const char *a)
{
  if (strlen(a) != 3)
  {
    cout << a << " is not a valid airport." << endl;
    return -1;
  } //size must be 3 to be valid 

  City temp;
  temp.setAirport(a);
  
  for (int i = 0; i < List<City>::getCount() ; i++)
    if (temp == cities[i])
      return i;
 
  cout << a << " is not a valid airport." << endl;
  return -1;
} //findAirport

void calcDistance(const List<City>& cities, int id1, int id2, int *d, int *p, 
                  int c, int m)
{
  if (id1 != -1 && id2 != -1)
  {
    if (d && p)
    {
      *d = cities[id1].getDistance(cities[id2]);
      *p = cities[id1].getPassengers(cities[id2], *d);
      
      if (*d > m)
        *p = 0;
      
      if (*p != 0 && c > 0) 
      {
        cout << setw(11) << left << "Passengers" << setw(7) << "Miles" 
             << setw(6) << "Trips" << setw(10) << "Name" << "Cost";
        cout << endl << setw(11) << *p << setw(7) << *d;
      } //has flights
      else //no flight
        cout << "No planes available" << endl;
    } //to determine best plane
    else //calc
      cities[id1].showDistance(cities[id2]);
  } //if valid
} //calcDistance

void calcAirportTraffic(const List<City>& cities, int index)
{
  int total = 0;

  if (index != -1)
  {
    for (int i = 0; i < List<City>::getCount(); i++) 
      if (i != index)
        total += cities[i].showTraffic(cities[index]);
    
    cout << "Total passengers: " << total << endl;  
  } //valid index returned from Vector::findAirport() 
} //calcAirportTraffic

int main()
{
  List<City> cities;
  readCities(cities);
  readAirports(cities);
  cleanCities(cities);
  
  int planeCount = 0;
  Plane myPlanes[10];
  readPlanes(myPlanes, planeCount);
  run(cities, myPlanes, planeCount);
  return 0;
} //main
