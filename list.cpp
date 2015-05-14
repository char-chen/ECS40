#include "list.h"

template<typename T>
ListNode<T>::ListNode(const T d, ListNode<T> *n) : data(d), next(n)
{ 
} //ListNode<T>

template<typename T>
int List<T>::count = 0;

template<typename T>
List<T>::List() : head(NULL), tail(NULL)
{
} //Citylist

template<typename T>
List<T>::~List()
{
  for (ListNode<T> *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } //for each node in the list   
} //~List<T>

template<typename T>
int List<T>::getCount()
{
  return List<T>::count;
} //static getCount()

template<typename T>
List<T>& List<T>::operator+=(const T& rhs)
{
  if (!head)
    tail = head = new ListNode<T>(rhs, NULL);
  else //list not empty
    tail = tail->next = new ListNode<T>(rhs, NULL); 

  List<T>::count++;
  return *this;
} //operator+=

template<typename T>
List<T>& List<T>::operator-=(const T& rhs)
{
  ListNode<T> *ptr, *prev = NULL;
  
  for (ptr = head; ptr && !(ptr->data == rhs) ; ptr = ptr->next)
    prev = ptr;
  
  if (ptr && ptr->data == rhs)
  {
    if (!prev)
      head = ptr->next;
    else //later node 
      prev->next = ptr->next;
    
    if (tail == ptr)
      tail = prev;
      
    delete ptr;
  } //remove data
  
  List<T>::count--;
  return *this;
} //operator-=

template<typename T>
T& List<T>::operator[](int index)
{
  ListNode<T> *ptr = head;
  
  for (int i = 0; ptr && i < index; i++, ptr = ptr->next);
   
  return ptr->data;
} //opeartor[]

template<typename T>  
const T& List<T>::operator[](int index) const
{
  ListNode<T> *ptr = head;
  
  for (int i = 0; ptr && i < index; i++, ptr = ptr->next);
  
  return ptr->data;  
} //const operator[] const
