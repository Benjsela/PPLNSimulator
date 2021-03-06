#include "definitions.hpp"

/*Pool methods---------------------------------------------------------------------*/
Pool::Pool(int n,std::map<int,Player *> * players){
  std::list<Share *> * t = new std::list<Share *>();
  std::map<int,Player *> * h = new std::map<int,Player *>();
  this->share_queue = t;
  this->players3 = h;
  this->N = n;
  this->players = players;
  
}


int Pool::submit(Share * s){
  this->share_queue->push_front(s);
  if(s->complete==true){
    this->payment();
  }
  if(this->share_queue->size()>this->N){
    this->share_queue->pop_back();
  }

  return 0;
}

int Pool::payment(){
  std::map<int,Player *>::iterator it;
  Share * curr;
  std::list<Share *>::iterator it2 = this->share_queue->begin();
  while(it2!=this->share_queue->end()){
    curr = *it2;
    int id = curr->playerID;
    it = this->players->find(id);
    if(it->first==id){
      it->second->paid_shares++;
    }
    it2++;
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

float Pool::getArrivalRate(){
  std::map<int,Player *>::iterator it = this->players3->begin();
  float lambda = 0;
  while(it!=this->players3->end()){
    lambda = lambda + it->second->lambda;
    it++;
  }
  return lambda;
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
  this->dist = new std::poisson_distribution<int>(hash*100);
  this->lambda=0;
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

int Player::mineBlocks(){
  std::poisson_distribution<int> g = *(this->dist);
  int n = g(this->gen);
  return n;
}

/*BlockMaker methods----------------------------------------------------------------*/
BlockMaker::BlockMaker(int num_players,std::map<int,Player*> * players){
  std::list<Share *> * s = new std::list<Share *>();
  std::poisson_distribution<int> * s2 = new std::poisson_distribution<int>[num_players];
  this->shares = s;
  this->poisson = s2;
  this->players = players;
}


Share * BlockMaker::nextShare(){
  if(this->shares->size()==0){
    this->prepareShares();
  }
  Share * s = this->shares->back();
  this->shares->pop_back();
  return s;

}




int BlockMaker::prepareShares(){
  std::default_random_engine gen;
  std::map<int,int> * shares = new std::map<int,int>();
  std::map<int,Player *>::iterator it = this->players->begin();
  while(it!=this->players->end()){
    int num = it->second->mineBlocks();
    shares->insert(std::pair<int,int>(it->first,num));
    it++;
  }
  std::vector<Share *> * temp_list = new std::vector<Share *>();
  std::map<int,int>::iterator it2 = shares->begin();
  while(it2!=shares->end()){
    int num = it2->second;
    int id = it2->first;
    for(int i=0;i<num;i++){
      Share * s = new Share(id);
      temp_list->push_back(s);
    }
    it2++;
  }
  std::random_shuffle (temp_list->begin(),temp_list->end());
  std::vector<Share *>::iterator it3 = temp_list->begin();
  while(it3!=temp_list->end()){
    Share * share = *(it3);
    this->shares->push_front(share);
    it3++;
  }
  
  return 0;
}







