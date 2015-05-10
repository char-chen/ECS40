#ifndef CITYLIST_H
  #define CITYLIST_H

#include "city.h"

class CityList;

class CityNode
{ 
  friend class CityList;
  
  City city;
  CityNode *next;
  CityNode(City c, CityNode *n);
  ~CityNode(); 
}; //class CityNode

class CityList
{
  CityNode *head;
  CityNode *tail;
  static int count;
public:
  CityList();
  ~CityList();
  static int getCount();
  CityList& operator+=(const City& rhs);
  CityList& operator-=(const City& rhs);
  City& operator[](int index);
  const City& operator[](int index) const;
}; //class CityList
#endif //CITYLIST_H
