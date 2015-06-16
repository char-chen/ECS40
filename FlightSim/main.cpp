#include <iostream>
#include <locale>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "airport.h"
#include "list.h"
#include "plane.h"
using namespace std;

void readPlanes(List<Plane>& planes);
void run(const List<Airport>& cities, List<Plane>& planes);
int getChoice();
void calcDistance(const List<Airport>& cities);
void determineAirportTraffic(const List<Airport>& cities);
void displayPlaneInformation(const List<Plane>& planes);
void addPlaneInformation(List<Plane>& planes);
void determineBestPlane(const List<Airport>& cities, const List<Plane>& planes);
void determineRoute(const List<Airport>& cities);
void readCities(List<Airport>& cities);
void readAirports(List<Airport>& cities);
void cleanCities(List<Airport>& cities);
int findAirport(const List<Airport>& cities, const char *a);
void calcDistance(const List<Airport>& cities, int id1, int id2, int *d, int *p,
                  int c, int m);
void calcAirportTraffic(const List<Airport>& cities, int index);
void readAirlines(List<Airport>& cities, const char *airlineFile);

void readPlanes(List<Plane>& planes)
{
  ifstream planeFile("planes.dat", ios::binary);
  
  if (planeFile)
  { 
    for (int i = 0; !planeFile.eof(); i++)
    {
      Plane temp;
      planeFile.read((char*)&temp, sizeof(Plane));

      if (planeFile)
        planes += temp;
    } //parse linee
  } //file exists
  
  planeFile.close();
} //readPlanes

void run(const List<Airport>& cities, List<Plane>& planes)
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
        displayPlaneInformation(planes);
    else //input = 4
      if (choice == 4)
        addPlaneInformation(planes);
    else //input = 5
      if (choice == 5)
        determineBestPlane(cities, planes);
    else //input = 6
      if (choice == 6)
        cout << cities;
    else //input = 7
      if (choice == 7)
        determineRoute(cities);
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
  cout << "6. Show airline flights.\n";
  cout << "7. Determine route between two airports.\n";
  cout << "\nYour choice (0 - 7): ";
  cin >> input;
  cin.ignore(10000, '\n');

  if (input > 7 || input < 0)
  {
    cout << "Your choice must be between 0 and 2. Please try again." << endl;
    return -1;
  } //check if valid range 

  return input;
} //returns -1 if not valid

void calcDistance(const List<Airport>& cities)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): "; 
  cin >> a1 >> a2;
  int a1index = findAirport(cities, a1);
  int a2index = findAirport(cities, a2);
  calcDistance(cities, a1index, a2index, NULL, NULL, -1, -1);
} //Dispaly distance and number of passengers between two airports

void determineAirportTraffic(const List<Airport>& cities)
{
  char airport[80];
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  calcAirportTraffic(cities, findAirport(cities, airport));
} //Display all traffic from airport

void displayPlaneInformation(const List<Plane>& planes)
{
  cout << "\nPlane Information\n";
  cout.imbue(locale(""));
  cout << left << setw(12) << "Name" << setw(6) << "Pass." << setw(6) << "Range"
       << setw(6) << "Speed" << setw(6) << "Fuel" << " " << setw(5) << "MPG" 
       << " " << setw(5) << "$/mi" << " " << setw(12) << "Price * 10^6\n";
  cout << planes;
} //Display information of all existing planes

void addPlaneInformation(List<Plane>& planes)
{
  Plane temp;
  temp.inputPlane();
  planes += temp;
} //User-defined airplane

void determineBestPlane(const List<Airport>& cities, const List<Plane>& planes)
{
  char a1[80], a2[80];
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> a1 >> a2;
  int i1 = findAirport(cities, a1);
  int i2 = findAirport(cities, a2);
  int dist = 0, pass = 0;
  int maxRange = -1;
  
  for (int i = 0; i < planes.getCount(); i++)
    if (planes[i].getRange() > maxRange)
      maxRange = planes[i].getRange();

  cout.imbue(locale("C"));
  calcDistance(cities, i1, i2, &dist, &pass, planes.getCount(), maxRange);
   
  if (pass != 0 && planes.getCount() > 0)
  {
    int lowestCost = 1e9, best;
  
    for (int i = 0; i < planes.getCount(); i++)
    { 
      int cost = planes[i].getCost(pass, dist);

      if ( cost != -1 && cost < lowestCost)
      {
        lowestCost = cost; 
        best = i; 
      } //if lower
    } //for each plane in planeArray
   
    int t = planes[best].getTrips((double)pass);
    cout << setw(6) << t << setw(10) << planes[best].getName()
    << "$" << lowestCost << endl;
  } //planes available
} //Determine the best plane for a given route 

void determineRoute(const List<Airport>& cities)
{
  char airport1[4], airport2[4], airline[10];
  cout << "\nPlease enter origin destination and an airline: ";
  cin >> airport1 >> airport2 >> airline;
  airline[2] = '\0';
  Airport origin, destination;
  origin.setAirport(airport1);
  destination.setAirport(airport2);
  
  List<Flight> results;
  bool found = false;
  origin.findRoute(destination, cities, results, airline, found);
   
  if (found)
  {
    cout << airline << "-" << airport1 << " ";
    
    for (int i = 0; i < results.getCount(); i++)
      cout << results[i];
  } //success
  else //dest not found 
    cout << "No route found.";
  
  cout << endl;
} //determineRoute

void readCities(List<Airport>& cities)
{
  ifstream cityFile("citypopulations.csv");
  Airport temp;
  
  while (!cityFile.eof())
  {
    cityFile >> temp; 
    cities += temp;
  } //parsing
  
  cityFile.close();     
} //readCities

void readAirports(List<Airport>& cities)
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
      Airport test;
      test.readAirport(line, state);
      
      for (int i = 0; i < cities.getCount(); i++)
        if (test == cities[i])
          cities[i].copyLocation(test);
    } //airport line
  } //parsing each line in file 
} //readAirports

void cleanCities(List<Airport>& cities)
{
  for (int i = 0; i < cities.getCount(); i++)
    if (!cities[i].hasAirport())
        cities -= cities[i--];
} //cleanCities

int findAirport(const List<Airport>& cities, const char *airport)
{
  if (strlen(airport) != 3)
  {
    cout << airport << " is not a valid airport." << endl;
    return -1;
  } //size must be 3 to be valid 

  Airport temp;
  temp.setAirport(airport);
  
  for (int i = 0; i < cities.getCount(); i++)
    if (temp == cities[i])
      return i;
 
  cout << airport << " is not a valid airport." << endl;
  return -1;
} //findAirport

void calcDistance(const List<Airport>& cities, int id1, int id2, int *d, int *p,
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

void calcAirportTraffic(const List<Airport>& cities, int index)
{
  int total = 0;

  if (index != -1)
  {
    for (int i = 0; i < cities.getCount(); i++) 
      if (i != index)
        total += cities[i].showTraffic(cities[index]);
    
    cout << "Total passengers: " << total << endl;  
  } //valid index returned from Vector::findAirport() 
} //calcAirportTraffic

void readAirlines(List<Airport>& cities, const char *file)
{
  ifstream airlineFile(file);
   
  if (airlineFile)
  { 
    for (int i = 0; i < 10; i++)
      airlineFile.ignore(100, '\n'); //skip 10 lines
  
    Airport temp;
    char origin[4];
    
    while (!airlineFile.eof())
    {
      airlineFile >> origin;
      temp.setAirport(origin);
      
      for (int i = 0; i < cities.getCount(); i++)
        if (cities[i] == temp)
          cities[i].readFlights(airlineFile);
    } //parsing
  } //if file exists
  
  airlineFile.close();
} //readAirlines

int main(int argc, char *argv[])
{
  List<Airport> cities;
  readCities(cities);
  readAirports(cities);
  cleanCities(cities);
  readAirlines(cities, argv[1]);
   
  List<Plane> planes;
  readPlanes(planes);
  
  run(cities, planes);
  return 0;
} //main
