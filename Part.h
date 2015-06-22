#ifndef _Part_
#define _Part_
#include <iostream>
#include "azar.h"
#include "Vect6.h"

class Part
{
private:
  double nx,ny,nz,nvx,nvy,nvz,nm,nfx,nfy,nfz;
  //double * part;

public:
Part();
 Part(double,double,double,double,double,double,double,double,double,double);
 //Part(double&,double&,double&,double,double,double,double,double,double,double); //para poder leer archivo
 //Part(float&,float&,float&,double,double,double,double,double,double,double); //para poder leer archivo

~Part();
// Part & operator = ( const Part &);
 double getx(){return nx;}
 double gety(){return ny;}
 double getz(){return nz;}
 double getvx(){return nvx;}
 double getvy(){return nvy;}
 double getvz(){return nvz;}
 double getm(){return nm;}
 double getfx(){return nfx;}
 double getfy(){return nfy;}
 double getfz(){return nfz;}

 void setx(double);
 void sety(double);
 void setz(double);
 void setvx(double);
 void setvy(double);
 void setvz(double);
 void setm(double);
 void setfx(double);
 void setfy(double);
 void setfz(double);

 Part setpart(Part);
 Part getpart(Part c){return c;}
 Part setfuerza(Part);
};


Part operator * (double,Part);
Part operator * (Part,double);

Part operator / (Part,double);
//Part operator = (Part,Part);
Part operator + (Part,Part);
std::ostream & operator << (std::ostream &, Part);
#endif

