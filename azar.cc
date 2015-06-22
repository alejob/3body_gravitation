//
// Azar
//
// 11Nov99 primera version
// 30Nov99 header externo y sobrecarga de randomize
//________________________
//JR//

#include "azar.h"

void randomize(unsigned int seed)
{
  srandom(seed);	// Inicializa el random
}

void randomize()
{
  srandom(time(0) * getpid());	// Inicializa el random
}
  
double dazar(double inf, double sup)
{
  return (sup-inf)* double(random())/double(0x7fffffff)+inf ;
}

int iazar(int inf, int sup)
{
  return int(floor(dazar(inf, sup+1))) ;
}



