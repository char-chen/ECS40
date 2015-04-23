#include <iostream>
#include <cstring>
#include <cstdlib>
#include "vector.h"
using namespace std;

void run(const Vector *v);
int getChoice(char *input);

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
    char input[80]; 
    int choice = getChoice(input);
    
    if (choice == 1)
    {
      cout << "\nPlease enter two airport abbreviations (XXX XXX): "; 
      cin.getline(input, 80); 
      bool valid = true; 
      int a1ind = v->findAirport(strtok(input, " ")); 
      int a2ind = v->findAirport(strtok(NULL, "")); 
 
      if (a1ind == -1 || a2ind == -1)  
        valid = false;

      if (valid)
        v->calcDistance(a1ind, a2ind);
    } //distance and passengers between two airports
    else //input = 2
      if (choice == 2)
      {
        cout << "\nPlease enter two airport abbreviations (XXX): ";
        cin.getline(input, 80); 
        v->calcAirportTraffic(v->findAirport(input));
      } //traffic from airport
    else //input not valid
      if (choice == -1)
        continue;
    else //done
      break;
  } //prompt continuously
} //gets user input/and return results

int getChoice(char *in)
{
  cout << endl << "Flight Simulator Menu" << endl;
  cout << "0. Done." << endl;
  cout << "1. Determine distance and passengers between two airports." << endl;
  cout << "2. Determine all traffic from one airport." << endl;
  cout << endl << "Your choice (0 - 2): ";
  cin.getline(in, 80);
  
  if (atoi(in) > 2 || atoi(in) < 0)
  {
    cout << "Your choice must be between 0 and 2.  Please try again." << endl;
    return -1;
  } //check if valid range 

  return atoi(in);
} //returns -1 if not valid
