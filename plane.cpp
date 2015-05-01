#include <iostream>
#include <iomanip>
#include <fstream>
#include "plane.h"
using namespace std;

void Plane::input()
{
  cout << "Name: ";
  cin >> name;
  cout << "Passengers: ";
  cin >> passengers;
  cout << "Fuel Capacity (in U.S. gallons): ";
  cin >> fuel;
  cout << "Range (in miles): ";
  cin >> range;
  cout << "Speed (in mph): ";
  cin >> speed;
  cout << "Price: ";
  cin >> price;
  ofstream planeFile("planes.dat", ios::binary | ios::app);
  planeFile.write((char*)this, sizeof(Plane));
  planeFile.close(); 
} //input

char* Plane::getName()
{
  return name;
}

ostream& operator<<(ostream& os, const Plane& rhs)
{
  os << left << setw(12) << rhs.name << setw(6) << rhs.passengers << setw(6) 
     << rhs.range << setw(6) << rhs.speed << right << setw(7) << rhs.fuel
     << left << setw(6) << setprecision(3) << (double)rhs.range/rhs.fuel 
     << setw(6) << (double)rhs.fuel*Plane::gallonPrice/rhs.range 
     << left << setw(12) << "$" << setprecision(4) << (double)rhs.price/1000000;
  
  return os;
} //Insertion operator 
