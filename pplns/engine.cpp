#include<random>
#include "engine.hpp"

int states2(std::map<int,Player *> * players){
  int done = 1;
  Player * p;
  while(done!=0){
    done = 0;
    std::map<int,Player *>::iterator it = players->begin();
    while(it!=players->end()){
      p = it->second;
      done = done + p->strategy();
      it++;
    }

  }


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


int time_interval(int num_players, Player ** players, std::vector<Share *> * s){
  



}


//awards blocks one at a time round based according to sizes
int rounds(Pool ** pools, Player ** players, int num_rounds, int num_players){

  for(int i=0;i<num_rounds;i++){
    int j = 0;
    float total = 0;
    float r = ((float)rand())/((float)RAND_MAX);
    //iteration -> time step t
    //compute expected number found for each miner
    //make shares and place in array
    //shuffle array
    //sequentially award shares until array is empty (use vector not array?)
    //poisson process: lambda = h p t
    std::default_random_engine generator;
    std::poisson_distribution<int> distribution(4);
    
    
    
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

//store players in set

int rounds2(Pool ** pools, std::map<int,Player *> * players, int num_blocks, int num_players){
  int blocks = 0;
  BlockMaker * b = new BlockMaker(num_players,players);
  while(blocks<num_blocks){
    Share * s = b->nextShare();
    Player * p = (players->find(s->playerID))->second;
    if(s->complete==true){
      p->has_solution=true;
      p->solution=s;
      blocks++;
    }
    else{
      p->share_set->insert(s);
    }
    states2(players);

  }




 
       

 




  return 0;
}








