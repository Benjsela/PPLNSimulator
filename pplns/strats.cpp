#include "strats.hpp"
#include<boost/math/distributions/poisson.hpp>
#include<iostream>

int honest(Player * p){
  
  int size = p->share_set->size();
  
  if(size>0){
  
    //submit share to the pool
    std::set<Share *>::iterator it = p->share_set->begin();
    Share * s = *it;
    p->pool->submit(s);
    p->share_set->erase(s);
    return 1;
  }
  else if(p->has_solution==true){
   p->pool->submit(p->solution);
   return 0;
  }
  else{
    return 0;
  }
  

}



int selfish1(Player * p){
  int num_shares = p->share_set->size();
  if(p->has_solution==true && num_shares>500){
      std::set<Share *>::iterator it = p->share_set->begin();
      while(it!=p->share_set->end()){
	p->pool->submit(*it);
	it++;
      }
      p->share_set->clear();
      p->pool->submit(p->solution);
      return 1;
  }
  else if(num_shares>0 && p->has_solution==false){
    std::set<Share *>::iterator it = p->share_set->begin();
    p->pool->submit(*it);
    p->share_set->erase(*it);
    return 1;
  }
  else{
    return 0;
    
  }
}





int hop1(Player * p){
  //mp1;
  Pool * p1 = p->pool;;
  Pool * p2;
  float rounds;
  float lambda1 = p1->getArrivalRate();
  float lambda2 = p2->getArrivalRate();
  int N1 = p1->N;
  int N2 = p2->N;
  float mu1 = rounds*lambda1;
  float mu2 = rounds*lambda2;

  
  boost::math::poisson_distribution<float> * a1 = new boost::math::poisson_distribution<float>(mu1);
  boost::math::poisson_distribution<float> * a2 = new boost::math::poisson_distribution<float>(mu2);  
  float m1 = boost::math::cdf(*a1,N1-2);
  float n1 = boost::math::cdf(*a1,N1-1);
  
  float m2 = boost::math::cdf(*a2,N2-2);
  float n2 = boost::math::cdf(*a2,N2-1);
  

  float MP1Ex = (mu1*m1+N1*(1-n1))/((float)N1);
  float MP2Ex = (mu2*m2+N1*(1-n2))/((float)N2);

  if(MP1Ex>MP2Ex){
    //stay in same pool
  }
  else{
    
  }
  
}






