#include <iostream>
#include <cmath>
#include "Cont.h"
#include "Part.h"
#include "azar.h"
#include "Vect6.h"

using namespace std;

Cont::Cont(const Cont & i){ //constructor de copia
  n=i.getn();
  part = new Part[n];
  for(int j=0;j<n;j++) {
    part[j]=i.getparti(j);
  }
}
Cont & Cont::operator = ( const Cont & i ){
  n=i.getn();
  delete [] part;
  part = new Part [n]; 
  for(int j=0;j<n;j++){
    part[j]=i.getparti(j);
  }
  return * this;
}


Cont::Cont(int x):
  n(x) // x=cantidad de particulas
{
  part = new Part[n];
  double q=1000,v=0.01;
  for(int j=0;j<n;j++) {
    //double g=iazar(2,8);
    double g=dazar(-q,q);
    double h=dazar(-q,q);
    double i=dazar(-q,q);
    double k=dazar(-v,v);
    double l=dazar(-v,v);
    double m=dazar(-v,v);
    Part a(g,h,i,k,l,m,3333,0,0,0);
    part[j]=a;
  }  
}

Cont::Cont(){
  n=0;
  part = NULL;
}

Cont::~Cont(){
delete [] part;
}


//POTENCIAL GRAVITATORIO
double Cont::energia_gravitatoria(){ // esta es ENERGIA POTENCIAL GRAVITATORIA
   int L=2000; //este es el tamanio de la caja
  cout.precision(15);      
  int numpart=this->getn(); // esto me devuelve el n
  F = new double [3*numpart];
  double dx,dy,dz,d;
  double energiaPotencial = 0.0e0 ;    
  Part parti,partj;
  double parti_x,parti_y,parti_z,parti_m,partj_m;
  
  for (int i=0; i<numpart; i++) { 
    // double Fx = 0.0e0;
    //double Fy = 0.0e0;
    //double Fz = 0.0e0;
    
    parti=this->getparti(i);
    parti_x=parti.getx();
    parti_y=parti.gety();
    parti_z=parti.getz();
    parti_m=parti.getm();

    for (int j=0; j<numpart; j++) {
      if(i!=j) {
	
	partj=this->getparti(j);
	dx=parti_x-partj.getx();
	dy=parti_y-partj.gety();
	dz=parti_z-partj.getz();
	partj_m=partj.getm();
	
	
	if(dx>L/2){dx=dx-L;}//CONDICION DE BORDE PERIODICA
	 else if (dx<=-L/2){dx=dx+L;}
	
	 if(dy>L/2){dy=dy-L;}
	 else if (dy<=-L/2){dy=dy+L;}
	
	 if(dz>L/2){dz=dz-L;}
	 else if (dz<=-L/2){dz=dz+L;}
		 
	 d=sqrt(dx*dx+dy*dy+dz*dz);
	 
	 double par_pot= -(0.5*parti_m*partj_m)/(d);//aca esta divido por 2, ya que sumo 2 veces la energia ij y ji
	 energiaPotencial +=  par_pot ; 
	 //
	 
      } 
    }  
  }    
  
  delete [] F;
  return energiaPotencial ;
}



//FUERZA GRAVITATORIA

Cont Cont::fuerza(){ //quiero la fuerza de todas, luego en el prog. principal elijo la que quiero.
  int L=2000;
  cout.precision(15);     
  int numpart=this->getn(); // esto me devuelve el n
  Part parti,partj;
  double parti_x,parti_y,parti_z,parti_m,partj_m;
  double dx,dy,dz,d;
  F = new double [3*numpart];  
  double energiaPotencial = 0.0e0 ;    
  double fdist;
  
  for (int i=0; i<numpart; i++) { 
    double Fx = 0.0e0;
    double Fy = 0.0e0;
    double Fz = 0.0e0;
    
    
    parti=this->getparti(i);
    //cout<<"contador="<<i<<" particula="<<parti<<endl;
    parti_x=parti.getx();
    parti_y=parti.gety();
    parti_z=parti.getz();
    parti_m=parti.getm();
    for (int j=0; j<numpart; j++) {
      if(i!=j) {
	
	  partj=this->getparti(j);
	  dx=parti_x-partj.getx();
	  dy=parti_y-partj.gety();
	  dz=parti_z-partj.getz();
	  partj_m=partj.getm();
	  	 
	  
	  if(dx>L/2){dx=dx-L;}//CONDICION DE BORDE PERIODICA
	  else if (dx<=-L/2){dx=dx+L;}
	  
	  if(dy>L/2){dy=dy-L;}
	  else if (dy<=-L/2){dy=dy+L;}
	  
	  if(dz>L/2){dz=dz-L;}
	  else if (dz<=-L/2){dz=dz+L;}
	 
	  
	  d=sqrt(dx*dx+dy*dy+dz*dz);
	 
	 double f = -(parti_m*partj_m)/(d*d);
	fdist=f/d;
	Fx+=fdist*dx;
	Fy+=fdist*dy;
	Fz+=fdist*dz;
      } 
    }
    F[3*i]=Fx/parti_m; //esta divido por la masa para obtener la aceleracion
    F[3*i+1]=Fy/parti_m;
    F[3*i+2]=Fz/parti_m;  
  }    
  
  for (int i=0; i<numpart; i++) { 
    Part a(F[3*i],F[3*i+1],F[3*i+2],0,0,0,getparti(i).getm(),0,0,0);
    //A.setparti(a,i); //con esta otra forma es mas lento, pero mas ordenado
    this->setparti(a,i);
  }
  delete [] F;
  return * this;
}



Part Cont::derivada(int p, Vect6 g){

//  int numpart=this->getn(); // esto me devuelve el n
  Part cam=this->getparti(p);

  Part pdg(cam.getvx(),cam.getvy(),cam.getvz(),g.getuno1(),g.getdos1(),g.gettres1(),0,0,0,0);

  return pdg;
}


std::ostream & operator << (std::ostream & os, Cont s){
  
  int n=s.getn();
  for(int j=0;j<n;j++) {
    os<<s.getparti(j)<<endl;
  } 
  return os;
}
