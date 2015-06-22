#ifndef _Cont_
#define _Cont_
#include "Part.h"
#include "Vect6.h"
#include <iostream>


class Cont
{
 private:
  int n;
  Part * part;//aca tengo que meter n Part, o sea un puntero.
  double * p_dbl;
  double * F;
  
 public:
  Cont();
  Cont(int);//aca meto n Part entre los parentesis.
  Cont(const Cont &);
  Cont & operator = ( const Cont &);
  ~Cont();
  int getn() const { return n;}
  void setparti(Part a,int i) const {part[i]=a; } //setear particula dentro del contenedor
  Part getparti(int i) const {return part[i];}
  Cont fuerza();
   Part derivada(int,Vect6);
   double energia_gravitatoria();
   double energia_gravitatoria(double);
  //double getF();
      
};

std::ostream & operator << (std::ostream &, Cont);
#endif
