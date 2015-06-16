#include <iostream>
using namespace std;

class Shape
{
  virtual void write(ostream& os) const = 0;
  friend ostream& operator<<(ostream& os, const Shape& rhs)
  {
    rhs.write(os);
    return os;
  } //operator <<
}; //class Shape

class IntersectingLines : public Shape
{
  void write(ostream& os) const
  {
    os << "    /\\\n   /  \\\n  /    \\\n /      \\\n/        \\\n";
  } //two intersecting lines
}; //class IntersectingLines

class BaseLine : public Shape
{
  void write(ostream& os) const
  {
    os << "----------\n";  
  } //a horizondtal line
}; //class BaseLine

class ParallelLines : public Shape
{
  void write(ostream& os) const
  {
    os << "|        |\n|        |\n|        |\n";     
  } //two parallel lines
}; //class ParallelLines

class BlankLines : public Shape
{
  void write(ostream& os) const
  {
    os << "\n\n";
  } //two blank lines
}; //class BlankLines

class Circle : public Shape
{
  void write(ostream& os) const
  {
    os << "    *\n  *   *\n   * *\n";
  } //circle
}; //class Circle

int main()
{
  Shape *shapes[9];
  shapes[0] = new IntersectingLines;
  shapes[1] = new BaseLine;
  shapes[2] = new ParallelLines; 
  shapes[3] = new BaseLine;
  shapes[4] = new BlankLines;
  shapes[5] = new Circle;
  shapes[6] = new IntersectingLines;
  shapes[7] = new BaseLine;
  shapes[8] = new IntersectingLines;
  
  for (int i = 0; i < 9; i++)
    cout << *shapes[i];
  
  return 0;
} //main
