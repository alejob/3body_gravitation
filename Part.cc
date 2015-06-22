#include <iostream>
#include <cmath>
#include "Part.h"
#include "azar.h"
#include "Vect6.h"

using namespace std;

Part::Part()
{
}


Part::Part(double x,double y,double z,double vx,double vy,double vz,double m,double fx,double  fy,double fz):
  nx(x),ny(y),nz(z),nvx(vx),nvy(vy),nvz(vz),nm(m),nfx(fx),nfy(fy),nfz(fz)
{
}
/*
Part::Part(float& x,float& y,float& z,double vx,double vy,double vz,double m,double fx,double  fy,double fz):
  nx(x ),ny(y ),nz(z ),nvx(vx),nvy(vy),nvz(vz),nm(m),nfx(fx),nfy(fy),nfz(fz)
{
}
*/

/*
Part & Part::operator = ( const Part & i ){---> ?????
   delete [] part;
   part = new double[10];
 
  //double part[10];
  part[0]=nx;
 part[1]=ny;
 part[2]=nz;
 part[3]=nvx;
 part[4]=nvy;
 part[5]=nvz;
 part[6]=nm;
 part[7]=nfx;
 part[8]=nfy;
 part[9]=nfz;

  return * this;
}
*/

Part Part::setpart(Part a){
  return Part (a.getx(),a.gety(),a.getz(),a.getvx(),a.getvy(),a.getvz(),a.getm(),a.getfx(),a.getfy(),a.getfz());
}

void Part::setx(double x){nx=x;}
void Part::sety(double y){ny=y;}
void Part::setz(double z){nz=z;}
void Part::setvx(double vx){nvx=vx;}
void Part::setvy(double vy){nvy=vy;}
void Part::setvz(double vz){nvz=vz;}
void Part::setm(double m){nm=m;}
void Part::setfx(double fx){nfx=fx;}
void Part::setfy(double fy){nfy=fy;}
void Part::setfz(double fz){nfz=fz;}


Part::~Part(){}

Part Part::setfuerza(Part b){


  Part a(this->getx(),this->gety(),this->getz(),this->getvx(),this->getvy(),this->getvz(),this->getm(),b.getfx(),b.getfy(),b.getfz());
  return a;
}


Part operator * (double t, Part s)
{
  return Part (s.getx()*t,s.gety()*t,s.getz()*t,s.getvx()*t,s.getvy()*t,s.getvz()*t,s.getm()*t,s.getfx()*t,s.getfy()*t,s.getfz()*t);
}


Part operator * (Part s, double t)
{
  return Part (s.getx()*t,s.gety()*t,s.getz()*t,s.getvx()*t,s.getvy()*t,s.getvz()*t,s.getm()*t,s.getfx()*t,s.getfy()*t,s.getfz()*t);
}



Part operator / (Part s,double t)
{
  return Part (s.getx()/t,s.gety()/t,s.getz()/t,s.getvx()/t,s.getvy()/t,s.getvz()/t,s.getm()/t,s.getfx()/t,s.getfy()/t,s.getfz()/t);
}



Part operator +(Part s,Part b) //estoy sumando las masas
{

  return Part (s.getx()+b.getx(),s.gety()+b.gety(),s.getz()+b.getz(),s.getvx()+b.getvx(),s.getvy()+b.getvy(),s.getvz()+b.getvz(),s.getm()+b.getm(),s.getfx()+b.getfx(),s.getfy()+b.getfy(),s.getfz()+b.getfz());


}
/*
Part operator = (Part a,Part b)
{

  Part b(a.getx(),a.gety(),a.getz(),a.getvx(),a.getvy(),a.getvz(),a.getm(),a.getfx(),a.getfy(),a.getfz());
  return b;
}
*/

std::ostream & operator << (std::ostream & os, Part a){
  //os<<"Au "<<a.getx()<<" "<< a.gety()<<" "<< a.getz();
  os<<"Au "<<a.getx()<<" "<< a.gety()<<" "<< a.getz()<<" "<<a.getvx()<<" "<< a.getvy()<<" "<< a.getvz()<<" "<<a.getm()<<" "<<a.getfx()<<" "<<a.getfy()<<" "<<a.getfz();// esto es para cuando necesite los 8 valores
return os;
}
