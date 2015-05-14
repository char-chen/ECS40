#ifndef PLANE_H
  #define PLANE_H

#include <iostream>
using namespace std;

class Plane
{
  char name[12];
  int passengers;
  int range;  //in miles
  int speed;  //in mile per hour
  int fuel;   //in US gallons
  int price;  //in US dollars
  static const double gallonPrice = 3.39;
public:
  void inputPlane();
  int getCost(double passengers, double distance) const;
  int getTrips(double passengers) const;
  int getRange() const;
  const char* getName() const;
  bool operator<(const Plane& rhs) const;
  friend ostream& operator<<(ostream& os, const Plane& rhs);
}; //class Plane
#endif
