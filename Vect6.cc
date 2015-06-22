#include <iostream>
#include <cmath>
#include "Vect6.h"


void Vect6::setuno1(double x){
uno1=x;
}

void Vect6::setdos1(double y){
dos1=y;
}

void Vect6::settres1(double z){
tres1=z;
}

void Vect6::setcuatro1(double w){
cuatro1=w;
}

void Vect6::setcinco1(double t){
cinco1=t;
}
void Vect6::setseis1(double p){
seis1=p;
}


double Vect6::getuno1(){
return uno1;
}

double Vect6::getdos1(){
return dos1;
}

double Vect6::gettres1(){
return tres1;
}

double Vect6::getcuatro1(){
return cuatro1;
}

double Vect6::getcinco1(){
return cinco1;
}

double Vect6::getseis1(){
return seis1;
}



Vect6::Vect6(double x, double y, double z, double w,double t,double p):
uno1(x), dos1(y), tres1(z), cuatro1(w),cinco1(t),seis1(p)
{
}
Vect6::Vect6()
{

  uno1=0;
  dos1=0;
  tres1=0;
  cuatro1=0;
  cinco1=0;
  seis1=0;
//  part = NULL;
}

Vect6::~Vect6()
{
}
/*
double Vect6::modulo(){
return sqrt(uno1*uno1+dos1*dos1+tres1*tres1+cuatro1*cuatro1);
}

double ppunto(Vect6 s, Vect6 t)
{
return  s.getuno1()*t.getuno1()+s.getdos1()*t.getdos1()+s.gettres1()*t.gettres1()+s.getcuatro1()*t.getcuatro1();
}
*/
Vect6 operator / (Vect6 s, double t)
{
  return Vect6 (s.getuno1()/t,s.getdos1()/t,s.gettres1()/t,s.getcuatro1()/t,s.getcinco1()/t,s.getseis1()/t);
}
Vect6 operator + (Vect6 s,Vect6 t)
{
  return Vect6 (s.getuno1()+t.getuno1(),s.getdos1()+t.getdos1(),s.gettres1()+t.gettres1(),s.getcuatro1()+t.getcuatro1(),s.getcinco1()+t.getcinco1(),s.getseis1()+t.getseis1());
}



/*
Vect6 operator / (Vect6 s, double t)
{
return Vect6 (s.getuno1()/t,s.getdos1()/t,s.gettres1()/t,s.getcuatro1()/t);
}

Vect6 operator - (Vect6 s, Vect6 t)
{
return Vect6 (s.getuno1()-t.getuno1(),s.getdos1()-t.getdos1(),s.gettres1()-t.gettres1(),s.getcuatro1()-t.getcuatro1());
}
*/

Vect6 operator * (double t, Vect6 s)
{
  return Vect6 (s.getuno1()*t,s.getdos1()*t,s.gettres1()*t,s.getcuatro1()*t,s.getcinco1()*t,s.getseis1()*t);
}

std::ostream & operator << (std::ostream & os, Vect6 s){
  os<<"("<< s.getuno1()<<","<< s.getdos1()<<","<< s.gettres1()<<","<< s.getcuatro1()<<","<<s.getcinco1()<<","<<s.getseis1()<<")"<<endl;
return os;
}

