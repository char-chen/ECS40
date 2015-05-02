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
  ofstream planeFile("planes.dat");
  
  if (planeFile.good())
    planeFile.open("planes.dat", ios::binary | ios::app);
  else //file not exist
    planeFile.open("planes.dat", ios::binary);

  planeFile.write((char*)this, sizeof(Plane));
  planeFile.close(); 
} //input

int Plane::getCost(double p, double d) const
{
  if (d <= range)
  {
    double fuelCost = (double)fuel * Plane::gallonPrice / range * d;
    double fSal = ceil(p / 100.0) * 30.0 * (2.0 + ceil(d / speed));
    double pilotSal = 2 * 100 * (2 + ceil(d / speed));
    double maintenance = 0.000025 * price * ceil(d / speed);
    //cout << fuelCost<<" "<<ceil(d/speed)<<" "<<pilotSal<<" "<<maintenance<< endl;
    return ceil(fuelCost + fSal + pilotSal + maintenance);
  } //satisfy range
  
  return -1;
}

int Plane::getTrips(double total) const
{
  return ceil(total/passengers);
}

const char* Plane::getName() const
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
