#ifndef LIST_H
  #define LIST_H

template<typename T>
class List;

template<typename T>
class ListNode
{ 
  T data;
  ListNode<T> *next;
  ListNode<T> (const T d, ListNode *n);
  friend class List<T>; 
}; //class ListNode

template<typename T>
class List
{
  ListNode<T> *head;
  ListNode<T> *tail;
  static int count;
public:
  List<T> ();
  ~List<T> ();
  static int getCount();
  List<T>& operator+=(const T& rhs);
  List<T>& operator-=(const T& rhs);
  T& operator[](int index);
  const T& operator[](int index) const;
}; //class List
#include "list.cpp"
#endif //LIST_H
