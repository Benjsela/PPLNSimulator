#include "engine.hpp"

int states2(){



}



int states(Player ** players, int num_players){
  
  int done = 1;
  Player * p;
  int i = 0;
  while(done!=0){
    done = 0;
    for(i=0;i<num_players;i++){
      p = players[i];
      done = done + p->strategy();
    }
  }
  return 0;
}

int rounds(Pool ** pools, Player ** players, int num_rounds, int num_players){

  for(int i=0;i<num_rounds;i++){
    int j = 0;
    float total = 0;
    float r = ((float)rand())/((float)RAND_MAX);
    while(j<num_players){
      Player * p = players[j];
      total = total + p->hash;
      j++;
      if(r<total){//player j wins round
	Share * s = new Share(p->id);
	if(s->complete==true){
	  p->has_solution = true;
	  p->solution = s;
	}
	else{
	  p->share_set->insert(s);
	}
        j = num_players+1;
      }
    }
    states(players,num_players);
  }

  return 0;
}




