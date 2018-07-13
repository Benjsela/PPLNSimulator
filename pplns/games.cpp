#include "engine.hpp"
#include<stdio.h>



int main(){
  Pool * pool1 = new Pool(500);
  Pool * pool2 = new Pool(500);
  Player * p1 = new Player(.01,1);  
  Player * p2 = new Player(.9,2);
  Player * p3 = new Player(.09,3);
  Player * p4 = new Player(.5,3);
  Player * p5 = new Player(.5,3);
  Player * p6 = new Player(.5,3);
  p1->joinPool(pool1);
  p2->joinPool(pool1);
  p3->joinPool(pool1);
  Player ** players1 = new Player*[2];
  Pool ** pools = new Pool*[2];
  pools[0] = pool1;
  pools[1] = pool2;
  
  int (*h)(Player * p) = honest;
  int (*s)(Player * p) = selfish1;

  p1->strat = h;
  p2->strat = h;
  p3->strat = h;
  
  players1[0] = p1;
  players1[1] = p2;
  players1[2] = p3;
  
  pool1->players = players1;
  rounds(pools,players1,10000000,3);
  int s1 = p1->paid_shares;
  int s2 = p2->paid_shares;
  int s3 = p3->paid_shares;
  int s4 = s1+s2+s3;
  float m1 = ((float)s1)/((float)(s4));
  float m2 = ((float)s2)/((float)(s4));
  float m3 = ((float)s3)/((float)(s4));
  printf("p1:%f\n",m1);
  printf("p2:%f\n",m2);
  printf("p3:%f\n",m3);
}





