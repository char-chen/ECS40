#include "citylist.h"

CityList::CityList() : head(NULL), tail(NULL)
{
    
} //Citylist

CityList::~CityList()
{
  for (CityNode *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } 
} //~CityList

CityList& CityList::operator+=(const City& rhs)
{
  return *this;
}

CityList& CityList::operator-=(const City& rhs)
{
  return *this;
}

CityNode::CityNode(City c, CityNode *n) : city(c), next(n)
{
  
}

CityNode::~CityNode()
{
  
}
