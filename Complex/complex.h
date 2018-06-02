#ifndef __Complex_H__
#define __Complex_H__
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
class div_by_zero{};

class Complex
{
private:
  double Real, Imag;
public:/*
    Complex ():Real (0), Imag (0){
  };

  Complex (double co){
    Real = co;
    Imag = 0;
  };*/

  Complex (double Real=0, double Imag=0){
    this->Real = Real;
    this->Imag = Imag;
  };

  Complex & operator= (const Complex & s){
    Real = s.Real;
    Imag = s.Imag;
    return *this;
  };

  Complex operator- () const{
    return Complex(-Real,-Imag);
  };

  Complex & operator= (double co){
    Real = co;
    Imag = 0;
    return *this;
  };

  Complex operator+ (const Complex& co) const{
    Complex n;
    n.Real = this->Real + co.Real;
    n.Imag = this->Imag + co.Imag;
    return n;
  };

  Complex & operator+= (Complex co){
    Real += co.Real;
    Imag += co.Imag;
    return *this;
  };

  Complex & operator-= (Complex co){
    Real -= co.Real;
    Imag -= co.Imag;
    return *this;
  };

  Complex operator/ (const Complex& co) const{
         Complex n;
         double help=co.Real * co.Real + co.Imag * co.Imag;
         
         if (help > 0) {       
             n.Real = (this->Real * co.Real + this->Imag * co.Imag)/help;
             n.Imag = (co.Real * this->Imag - this->Real * co.Imag)/help;
             return n;
        }else
			throw div_by_zero();
	
  };
	
  Complex &operator/= (Complex co){
         double help=co.Real * co.Real + co.Imag * co.Imag;
         
         if (help > 0) {       
             Real = (this->Real * co.Real + this->Imag * co.Imag)/help;
             Imag = (co.Real * this->Imag - this->Real * co.Imag)/help;
	     return *this;
         }else
			throw div_by_zero();
	
	
  }; 	
  
 double abs(const Complex& co) const{
	 return sqrt((co.Real*co.Real)+(co.Imag+co.Imag));
 }
 
 double phase(const Complex& co) const{
	 double phase_angle = atan2(co.Imag,co.Real)*180/3.14;
	 if (phase_angle < 0.0)
		return 360 + phase_angle;
	else
		return phase_angle;
 }
 
 Complex conj(const Complex& co){
	this->Imag = (-1)*co.Imag;
	return *this;
	 
 }


 friend Complex operator- (Complex, Complex);
  friend ostream & operator << (ostream & s, const Complex & c){
    s << "(" << c.Real << "," << c.Imag << ")";
    return s;
  };
};

inline Complex
operator - (Complex s1, Complex s2){
  Complex n (s1);
  return n -= s2;
};

#endif  /*__Complex_H__ */
