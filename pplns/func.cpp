#include<stdio.h>
#include<queue>
#include<set>
#include<stdlib.h>
#include<random>
#include<iostream>
#include<cmath>


class Share{
public:
  static int difficulty;
  int playerID;
  bool complete;
  Share(int id);
};


class Player;

class Pool{
public:
  int N;
  int num_players;
  std::queue<Share *> * share_queue;
  Player ** players;
  int submit(Share * s);  
  int payment();
  Pool(int n);

};



class Player{
public:
  int id;
  float hash;
  bool has_solution;
  int paid_shares;
  Share * solution;
  std::queue<Share *> * pool_Q;
  std::set<Share *> * share_set;
  Pool * pool;
  int (*strat)(Player * p);
  int strategy(){
    return (*strat)(this);
  }
  Player(float hash, int id, Pool * pool);
};




Pool::Pool(int n){
  std::queue<Share *> * t = new std::queue<Share *>();
  this->share_queue = t;
  this->N = n;
  
}


int Pool::submit(Share * s){
  this->share_queue->push(s);
  if(s->complete==true){
    this->payment();
  }
  if(this->share_queue->size()>this->N){
    this->share_queue->pop();
  }

  return 0;
}

int Pool::payment(){
  Share * curr;
  while(!(share_queue->empty())){
    curr = share_queue->front();
    int id = curr->playerID;
    this->players[(id-1)]->paid_shares++;
    share_queue->pop();
  }
  for(int i=0;i<this->num_players;i++){
    this->players[i]->share_set->clear();
    this->players[i]->has_solution = false;
    this->players[i]->solution=NULL;
  }

  return 0;
}



Share::Share(int id){
  this->playerID = id;
  int d = 1;
  for(int i = 0;i<this->difficulty;i++){
    float r = ((float)rand())/((float)RAND_MAX);
    if(r>.5){
      d = 0;
    }
  }
  if(d==1){
    this->complete = true;
  }
  else{
    this->complete = false;
  }
}



int Share::difficulty = 15;


Player::Player(float hash,int id, Pool * pool){
  this->hash = hash;
  this->id = id;
  std::set<Share *> * s = new std::set<Share *>();
  this->share_set = s;
  this->paid_shares = 0;
  this->has_solution = false;
  this->pool = pool;
  this->solution=NULL;
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


}


int rounds(Player ** players, int num_rounds, int num_players){

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












}




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


int main(){
  Pool * pool = new Pool(500);
  Player * p1 = new Player(.25,1,pool);  
  Player * p2 = new Player(.75,2,pool);
  Player ** players = new Player*[2];
  int (*h)(Player * p) = honest;
  int (*s)(Player * p) = selfish1;
  pool->num_players = 2;
  p1->strat = s;
  p2->strat = h;
  players[0] = p1;
  players[1] = p2;
  pool->players = players;
  rounds(players,10000000,2);
  int s1 = p1->paid_shares;
  int s2 = p2->paid_shares;
  int s3 = s1+s2;
  float m1 = ((float)s1)/((float)(s3));
  float m2 = ((float)s2)/((float)(s3));
  printf("p1:%f\n",m1);
  printf("p1:%f\n",m2);
}




