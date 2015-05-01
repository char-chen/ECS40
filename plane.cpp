#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
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

int Plane::getCost() const
{
  double fuelCost = (double)range/fuel;
  double fSalaries = ceil((double)passengers / 100) * 30 * (2 + ceil((double)range / speed));
  double pilotSalaries = 2*100*(2 + ceil((double)range/speed));
  double maintenance = 0.000025 * price * ceil((double)range / speed);
  return fuelCost + fSalaries + pilotSalaries + maintenance;
}

int Plane::getTrips(int total) const
{
  return ceil((double)total/passengers);
}

char* Plane::getName()
{
  return name;
}

ostream& operator<<(ostream& os, const Plane& rhs)
{
  os << left << setw(12) << rhs.name << setw(6) << rhs.passengers << setw(6) 
     << rhs.range << setw(6) << rhs.speed << right << setw(6) << rhs.fuel 
     << " " << setw(5) << fixed << setprecision(3) << (double)rhs.range/rhs.fuel
     << " " << setw(5) << setprecision(2) 
     <<(double)rhs.fuel*Plane::gallonPrice/rhs.range << " $" << setw(5) 
     << setprecision(1) << (double)rhs.price/1000000;
  
  return os;
} //Insertion operator 
