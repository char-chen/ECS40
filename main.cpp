#include <iostream>
#include "vector.h"
using namespace std;

const int COMMAND_LENGTH = 80;

void run(Vector *v);

int main()
{
  Vector *cities = new Vector();
  run(cities);
  delete cities;	
}

void run(Vector *v)
{
  v->initialize();
  v->readCities();
  v->readAirports();
  //char input[COMMAND_LENGTH];
  //cout << "Please enter two airport abbreviations (XXX XXX = done): "; 
  //cin.getline(input, COMMAND_LENGTH);
}
