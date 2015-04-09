#include <iostream>
#include <cstring>
#include "vector.h"
using namespace std;

const int COMMAND_LENGTH = 80;

void run(Vector *v);

int main()
{
  Vector cities;
  cities.initialize();
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();
  run(&cities);
  cities.deallocate();
} //main

void run(Vector *v)
{
  while(true)
  {
    char input[COMMAND_LENGTH];
    cout << "\nPlease enter two airport abbreviations (XXX XXX = done): "; 
    cin.getline(input, COMMAND_LENGTH);
    
    if (strcmp(input, "XXX XXX") != 0)
    {
      bool valid = true; char *a1, *a2;
      a1 = strtok(input, " "); a2 = strtok(NULL, "");
      int a1ind = v->findAirport(a1); int a2ind = v->findAirport(a2); 
      
      if (a1ind == -1)
      {
        cout << a1 << " is not a valid airport." << endl; valid = false;
      } //if first is valid

      if (a2ind == -1)
      {
        cout << a2 << " is not a valid airport." << endl; valid = false;
      } //if second is valid

      if (valid)
      {
        v->calcDistance(a1ind, a2ind);
      } //prints result
    } //program continues
    else //exits
    {
      break;
    } //set done
  } //prompting user 
} //gets user input
