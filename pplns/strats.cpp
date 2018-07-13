#include "strats.hpp"

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

