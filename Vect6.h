#ifndef _Vect6_
#define _Vect6_


#include <iostream>
using namespace std;

class Vect6
{
private:

  double uno1,dos1,tres1,cuatro1,cinco1,seis1;

public:
 Vect6(double,double,double,double,double,double);
~Vect6();
 Vect6();
void setuno1(double);
void setdos1(double);
void settres1(double);
void setcuatro1(double);
void setcinco1(double);
 void setseis1(double);
double getuno1();
double getdos1();
double gettres1();
double getcuatro1();
 double getcinco1();
 double getseis1();
/*
double getuno1(){return uno1;}
double getdos1(){return dos1;}
double gettres1(){return tres1;}
double getcuatro1(){return cuatro1;}
double getcinco1(){return cinco1;}
 double getseis1(){return seis1;}
*/
double modulo();
};

//double ppunto(Vect6 , Vect6 );
Vect6 operator + (Vect6,Vect6);
//Vect6 operator * (Vect6, Vect6);
Vect6 operator / (Vect6, double);
//Vect6 operator - (Vect6, Vect6);
Vect6 operator * (double,Vect6);
std::ostream & operator << (std::ostream &, Vect6);
#endif
