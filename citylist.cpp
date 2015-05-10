#include "citylist.h"

CityNode::CityNode(City c, CityNode *n) : city(c), next(n)
{ 
} //CityNode

CityNode::~CityNode()
{
} //~CityNOde

int CityList::count = 0;

CityList::CityList() : head(NULL), tail(NULL)
{

} //Citylist

CityList::~CityList()
{
  for (CityNode *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } //for each node in the list   
} //~CityList

int CityList::getCount()
{
  return CityList::count;
} //static getCount()

CityList& CityList::operator+=(const City& rhs)
{
  if (!head)
    tail = head = new CityNode(rhs, NULL);
  else //list not empty
    tail = tail->next = new CityNode(rhs, NULL); 

  CityList::count++;
  return *this;
} //operator+=

CityList& CityList::operator-=(const City& rhs)
{
  CityNode *ptr, *prev = NULL;
  
  for (ptr = head; ptr && !(ptr->city == rhs) ; ptr = ptr->next)
    prev = ptr;
  
  if (ptr && ptr->city == rhs)
  {
    if (!prev)
      head = ptr->next;
    else //later node 
      prev->next = ptr->next;
    
    if (tail == ptr)
      tail = prev;
      
    delete ptr;
  } //remove city
  
  CityList::count--;
  return *this;
} //operator-=

City& CityList::operator[](int index)
{
  CityNode *ptr = head;
  
  for (int i = 0; ptr && i < index; i++, ptr = ptr->next);
   
  return ptr->city;
} //opeartor[]
  
const City& CityList::operator[](int index) const
{
  CityNode *ptr = head;
  
  for (int i = 0; ptr && i < index; i++, ptr = ptr->next);
  
  return ptr->city;  
} //const operator[] const
