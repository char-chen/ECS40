#include <iostream>
#include <cstring>
#include <cstdlib>
#include "vector.h"
using namespace std;

void run(const Vector *v);
int getChoice();

int main()
{
  Vector cities;
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
  run(&cities);
} //main

void run(const Vector *v)
{
  while(true)
  {
    char a1[80]; 
    char a2[80];
    int choice = getChoice();
    
    if (choice == 1)
    {
      cout << "\nPlease enter two airport abbreviations (XXX XXX): "; 
      cin >> a1 >> a2;
      cin.ignore(1000, '\n');
      int a1index = v->findAirport(a1);
      int a2index = v->findAirport(a2);
      v->calcDistance(a1index, a2index);
    } //distance and passengers between two airports
    else //input = 2
      if (choice == 2)
      {
        cout << "\nPlease enter an airport abbreviation (XXX): ";
        cin >> a1;
        cin.ignore(1000, '\n'); 
        v->calcAirportTraffic(v->findAirport(a1));
      } //traffic from airport
    else //input not valid
      if (choice == -1)
        continue;
    else //done
      break;
  } //prompt continuously
} //gets user input and return results

int getChoice()
{
  char input[80];
  cout << "\nFlight Simulator Menu\n";
  cout << "0. Done.\n";
  cout << "1. Determine distance and passengers between two airports.\n";
  cout << "2. Determine all traffic from one airport.\n";
  cout << "\nYour choice (0 - 2): ";
  cin >> input;
  cin.ignore(10000, '\n');

  if (atoi(input) > 2 || atoi(input) < 0)
  {
    cout << "Your choice must be between 0 and 2. Please try again." << endl;
    return -1;
  } //check if valid range 

  return atoi(input);
} //returns -1 if not valid
