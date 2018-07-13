#include "definitions.hpp"
/*Pool methods---------------------------------------------------------------------*/
Pool::Pool(int n){
  std::queue<Share *> * t = new std::queue<Share *>();
  std::map<int,Player *> * h = new std::map<int,Player *>();
  this->share_queue = t;
  this->players3 = h;
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
  std::map<int,Player *>::iterator it;
  Share * curr;
  while(!(share_queue->empty())){
    curr = share_queue->front();
    int id = curr->playerID;
    it = this->players3->find(id);
    if(it->first==id){
      it->second->paid_shares++;
    }
    // this->players[(id-1)]->paid_shares++;
    share_queue->pop();
  }
  it = this->players3->begin();
  while(it!=players3->end()){
    it->second->share_set->clear();
    it->second->has_solution = false;
    it->second->solution = NULL;
    it++;
  }
  

  return 0;
}

int Pool::reset(){
  while(!this->share_queue->empty()){
    this->share_queue->pop();
  }

  std::map<int,Player *>::iterator it = this->players3->begin();
  while(it!=this->players3->end()){
    it->second->reset();
    it++;
  }
}

int Pool::removePlayer(Player * p){
  this->players3->erase(p->id);
  return 0;
}

int Pool::addPlayer(Player * p){
  this->players3->insert(std::pair<int,Player *> (p->id,p));
  return 0;
}


/*Share methods-------------------------------------------------------------------------------------*/


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





/*Player methods------------------------------------------------------*/


Player::Player(float hash,int id){
  this->hash = hash;
  this->id = id;
  std::set<Share *> * s = new std::set<Share *>();
  this->share_set = s;
  this->paid_shares = 0;
  this->has_solution = false;
  this->pool = NULL;
  this->solution = NULL;
}

int Player::reset(){
  this->share_set->clear();
  this->has_solution=false;
  this->solution=NULL;
}

int Player::leavePool(){
  this->pool->removePlayer(this);
  this->pool = NULL;
}

int Player::joinPool(Pool * p){
  p->addPlayer(this);
  this->pool = p;
  return 0;
}





