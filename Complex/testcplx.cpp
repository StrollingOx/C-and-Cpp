#include <iostream>
using namespace std;
#include "complex.h"


int main()
{
try{

  Complex a(0.0,15),b(0,13),c;
  c = 10;
  cout << c <<endl;
  c = -a;
  cout << c <<endl;  
  c = a + b;
  c = c - Complex(10);
  cout << c <<endl;  
  c = 10 - a;
  (c +=b) +=10;
  cout << c <<endl;
  c/=a;
  cout << c <<endl;
  c = a / a;
  cout << c <<endl;

  const Complex d(1,3);
  c = d.operator/(a);

  double result;
  result = abs(d);
  cout << d <<endl;
  result = phase(d);
  cout << d <<endl;
  c=conj(d);
}
catch(div_by_zero&)
{
  cout << "You can't divide by 0!" <<endl;
}
catch(...)
{
  cout << "Unidentified error" <<endl;
}

}
