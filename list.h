#ifndef LIST_H
  #define LIST_H

#include <iostream>
using namespace std;

template<typename T>
class List;

template<typename T>
ostream& operator<<(ostream& os, const List<T>& rhs);

template<typename T>
class ListNode
{ 
  T data;
  ListNode<T> *next;
  ListNode<T> (const T& d, ListNode<T> *n);
  friend class List<T>; 
}; //class ListNode

template<typename T>
class List
{
  ListNode<T> *head;
  int count;
public:
  List<T>();
  List<T>(const List<T>& orig);
  ~List<T>();
  int getCount() const;
  List<T>& operator+=(const T& rhs);
  List<T>& operator-=(const T& rhs);
  T& operator[](int index);
  const T& operator[](int index) const;

  template<typename R> 
  friend ostream& operator<<(ostream& os, const List<R>& rhs);
}; //class List
#include "list.cpp"
#endif
