#include <iostream>
#include <cstring>
#include "vector.h"
using namespace std;

const int COMMAND_LENGTH = 80;

void run(Vector *v);

int main()
{
  Vector *cities = new Vector();
  cities->initialize();
  cities->readCities();
  cities->readAirports();
  //cities->cleanCities();
  for(int i = 0; i < cities->size ; i++)
  {
    //cout << cities->cityArray[i]->name <<" "<< cities->cityArray[i]->state;
  }
  //run(cities);
  cities->deallocate();	
}

void run(Vector *v)
{
  bool done = false;
  while(!done)
  {
    char input[COMMAND_LENGTH];
    cout << "Please enter two airport abbreviations (XXX XXX = done): "; 
    cin.getline(input, COMMAND_LENGTH);
    if(strcmp(input, "XXX XXX") != 0)
    {
      char *a1, *a2;
      a1 = strtok(input, " ");
      a2 = strtok(NULL, " ");
      bool valid = true;
      int a1ind = v->findAirport(a1); //airport 1 index
      int a2ind = v->findAirport(a2); //airport 2 index
      if(a1ind == -1)
      {
        cout << a1 << " is not a valid airport" << endl;
        valid = false;
      }
      if(a2ind == -1)
      {
        cout << a2 << " is not a valid airport" << endl;
        valid = false;
      }
      if(valid)
      {
        cout << v->calcPassengers(a1ind, a2ind) << " passengers fly the " 
          << v->calcDistance(a1ind, a2ind) << " miles from" << endl;
        cout << v->getCity(a1ind) << " to " << v->getCity(a2ind) << "." << endl;  
      }
    } 
    else
    {
      done = true;
    }
  }
}
