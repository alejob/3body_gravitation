#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Part.h"
#include "Cont.h"
#include "azar.h"
#include "Vect6.h"


using namespace std;

double ecinetica(Part);
double sumafuerzas(Part);

int main(){
  //ARCHIVOS DE ENTRADA Y SALIDA
  ifstream entrada("entrada.xyz");
  ofstream salida("salidas/3cuerpos.xyz"),tetotal("salidas/tetotal.dat"),tgrafecinetica("salidas/tecinetica.dat");
   ofstream salida1("salidas/3cuerposB_3d_part1.dat");
     ofstream salida2("salidas/3cuerposB_3d_part2.dat");
       ofstream salida3("salidas/3cuerposB_3d_part3.dat");
     
  ofstream tepotencial("salidas/tepotencial.dat");
  ofstream tfuerza("salidas/tfuerza.dat");
  
  int archiv,extras,p;
  tetotal.precision(8);//
    
    
    
  //CANTIDAD DE PARTICULAS DEL ARCHIVO
  archiv=3;
  //p=extras+archiv;
  p=3;
  time_t ta=time(NULL); 
  Cont r(p);
  Part part[p],a[p],leida;
  long double x1[p],y1[p],z1[p],vnx[p],vny[p],vnz[p],ecinet[p],sumfuer[p],t=1e-2,tau=1e-2;
  int q=1000; //2q=L, q=L/2, original q=20
  int L=2*q;
  int contr=0;
  
    for(int i=0;i<archiv;i++){ // archiv=particulas que tiene el archivo; esta parte setea el archivo en el Cont.
      if(i<archiv){
	double xpos,ypos,zpos,xvpos,yvpos,zvpos,masa;
	entrada>>xpos>>ypos>>zpos>>xvpos>>yvpos>>zvpos>>masa;
	Part leida(xpos,ypos,zpos,xvpos,yvpos,zvpos,masa,0.0,0.0,0.0);
	r.setparti(leida,i);}
      else{
	break  ;
      }
    }
    
    cout<<" "<<endl;
    cout<<r<<endl;
    cout<<"energia potencial "<<r.energia_gravitatoria()<<endl;
    salida<<p<<endl;
    double contarchsal=0;//,din=0;;
    long double f1[p],f2[p],f3[p];

   //ACA COMIENZA A TRABAJAR EL INTEGRADOR
    for(int j=0;j<3e5;j++){//original 3e5, 19000
      for(int i=0;i<p;i++){
	a[i]=r.getparti(i);
	//cout<<"a[i] "<<a[i]<<endl;
      }
      Cont force=r;
      //cout<<"tau "<<tau<<endl;
      Cont fuerza1= force.fuerza();
      
      for(int i=0;i<p;i++){
	
	Part part_sal=fuerza1.getparti(i);
	double partm=part_sal.getm();
	f1[i]=part_sal.getx();
	f2[i]=part_sal.gety();
	f3[i]=part_sal.getz();
	x1[i]=a[i].getx()+tau*a[i].getvx()+tau*tau*f1[i]/2.0;
	y1[i]=a[i].gety()+tau*a[i].getvy()+tau*tau*f2[i]/2.0;
	z1[i]=a[i].getz()+tau*a[i].getvz()+tau*tau*f3[i]/2.0;
      
	
	part[i].setx(x1[i]);
	part[i].sety(y1[i]);
	part[i].setz(z1[i]);
	part[i].setvx(a[i].getvx());
	part[i].setvy(a[i].getvy());
	part[i].setvz(a[i].getvz());
	part[i].setm(partm);
	part[i].setfx(0);
	part[i].setfy(0);
	part[i].setfz(0);
	r.setparti(part[i],i);
      }
    /*
  for(int i=0;i<p;i++){
      r.setparti(part[i],i);
      }*/

    Cont force2=r;
    

    Cont fuerza2=force2.fuerza();//aca los igualo y no lo cambio en Cont.cc porque es mas rapido de esta manera
    //Cont fuerza2=r.fuerza();
  
     for(int i=0;i<p;i++){
       Part part_sal2=fuerza2.getparti(i);
            vnx[i]=a[i].getvx()+tau*0.5*(f1[i]+part_sal2.getx());
            vny[i]=a[i].getvy()+tau*0.5*(f2[i]+part_sal2.gety());
            vnz[i]=a[i].getvz()+tau*0.5*(f3[i]+part_sal2.getz());
	    
	    
	    a[i].setx(x1[i]);
	    a[i].sety(y1[i]);
	    a[i].setz(z1[i]);
	    a[i].setvx(vnx[i]);
	    a[i].setvy(vny[i]);
	    a[i].setvz(vnz[i]);
	    
     }
     
     long double sumaecinet=0.0e0;
     long double sumaf=0.0e0;
     for(int i=0;i<p;i++){
       ecinet[i]=ecinetica(a[i]);
       sumfuer[i]=sumafuerzas(a[i]);
       sumaecinet+=ecinet[i];
       sumaf+=sumfuer[i];
     }
      
     
     for(int i=0;i<p;i++){ //CONDICION DE BORDE PERIODICA
       // L y q definidos al comienzo
       if(a[i].getx()>q){a[i].setx(a[i].getx()-L);}
       else if(a[i].getx()<-q){a[i].setx(a[i].getx()+L);}
       
       if(a[i].gety()>q){a[i].sety(a[i].gety()-L);}
       else if(a[i].gety()<-q){a[i].sety(a[i].gety()+L);}
       
       if(a[i].getz()>q){a[i].setz(a[i].getz()-L);}
       else if(a[i].getz()<-q){a[i].setz(a[i].getz()+L);}
       
       r.setparti(a[i],i);
     }
      

      /*
      for(int i=0;i<p;i++){ //CONDICION DE BORDE CERRADOOOOOOO 
	int q=20;
	
	if(a[i].getx()>q){
	  a[i].setvx(-a[i].getvx());
	  a[i].setx(2*q-a[i].getx());}
	else if(a[i].getx()<-q){
	  a[i].setvx(-a[i].getvx());
	  a[i].setx(-2*q-a[i].getx());}
	
	
	if(a[i].gety()>q){
	  a[i].setvy(-a[i].getvy());
	  a[i].sety(2*q-a[i].gety());}
	else if(a[i].gety()<-q){
	  a[i].setvy(-a[i].getvy());
	  a[i].sety(-2*q-a[i].gety());}
	
	if(a[i].getz()>q){
	  a[i].setvz(-a[i].getvz());
	  a[i].setz(2*q-a[i].getz());}
	else if(a[i].getz()<-q){
	  a[i].setvz(-a[i].getvz());
	  a[i].setz(-2*q-a[i].getz());}
	
	r.setparti(a[i],i);
      }
      */
     

	
      ////////////////////////////////////////////////////////////////////////////////fin calculos
      int salida_cada_cuanto=40;
      contarchsal+=1;
      //ACA ARROJAMOS INFORMACION EXTRA A LA SALIDA
      if(contarchsal==salida_cada_cuanto ){//lo tiro cada "salida_cada_cuanto" iteraciones; SALIDAS
	long double energia_potencial=r.energia_gravitatoria();
	tetotal<<t<<" "<<sumaecinet+energia_potencial<<endl;
	tgrafecinetica<<t<<" "<<sumaecinet<<endl;
	tepotencial<<t<<" "<<energia_potencial<<endl;
	tfuerza<<t<<" "<<sumaf<<endl;//con esto veo la fuerza del centro de masas
	contarchsal=0;
	    
	salida<<"E"<<energia_potencial+sumaecinet<<" t="<<t<<endl;// 1 esto no va comentado originalmente
	/*
	salida<<"Au "<<-q<<" "<<-q<<" "<<-q<<endl;
	salida<<"Au "<<q<<" "<<q<<" "<<q<<endl;
	salida<<"Au "<<-q<<" "<<q<<" "<<-q<<endl;
	salida<<"Au "<<q<<" "<<-q<<" "<<q<<endl;
	salida<<"Au "<<-q<<" "<<-q<<" "<<q<<endl;
	salida<<"Au "<<q<<" "<<q<<" "<<-q<<endl;
	salida<<"Au "<<-q<<" "<<q<<" "<<q<<endl;
	salida<<"Au "<<q<<" "<<-q<<" "<<-q<<endl;
	*/
	int h=0;
	for(int i=0;i<p;i++){ //2 aca originalmente es i<p  
	  salida<<a[i]<<endl;//3 dentro del corchete va originalmente un i, va salida<<a[i]<<endl;
	   //salida<<a[0].getx()<<" "<<a[0].getvx()<<endl;//3 dentro del corchete va originalmente un i, va salida<<a[i]<<endl;
	 /*  
	   salida1<<a[0].getx()<<" "<<a[0].gety()<<" "<<a[0].getz()<<endl;
	   salida2<<a[1].getx()<<" "<<a[1].gety()<<" "<<a[1].getz()<<endl;
	   salida3<<a[2].getx()<<" "<<a[2].gety()<<" "<<a[2].getz()<<endl;
	   */
	   
	   
	   h=h+1;
	  if(h==p){
	    salida<<endl;
	    h=0;
	  } 
	}
	
      } //end salida archivo
      
      t+=tau;   
      
  }//////////////////////////////////////////////////////final del for
  
   
   //INFORMACION DESPLEGADA EN PANTALLA AL TERMINAR EL CALCULO
  time_t tb=time(NULL);
  time_t ttotal=tb-ta;
  tm tm2 = *gmtime(&ttotal); 
  cout<<"Tiempo transcurrido en la simulacion: "<<t<<" unidades de tiempo"<<endl;
  cout<<"Los datos se han guardado en el archivo dinamicaverlet.xyz "<<endl;
  cout<<"Los datos de energia cinetica vs tiempo estan en tecinetica.dat "<<endl;
  cout<<"Los datos de energia potencial vs tiempo estan en tepotencial.dat "<<endl;
  cout<<"Los datos de energia total vs tiempo estan en tetotal.dat "<<endl;
  cout<<"Los datos de temperatura vs tiempo estan en ttemperatura.dat "<<endl<<endl;

  cout<<"Este programa calculo en " << tm2.tm_hour << ":" <<  tm2.tm_min << ":"<< tm2.tm_sec << endl;
  salida.close();
  tetotal.close();
  tgrafecinetica.close();
  tepotencial.close();
  tfuerza.close();
  entrada.close();

  return 0;
  /////////////////////////////////////////////////////////FIN DEL PRIMER IF#################################

    }//final del main


double ecinetica(Part a){
  return 0.5*(a.getvx()*a.getvx()+a.getvy()*a.getvy()+a.getvz()*a.getvz())*a.getm();
}
 

double sumafuerzas(Part a){
  return a.getvx()+a.getvy()+a.getvz();
}
