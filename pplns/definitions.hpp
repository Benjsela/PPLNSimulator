#include<stdlib.h>
#include<set>
#include<queue>
#include<vector>
#include<map>
#include<random>
#include<algorithm>
#include<list>


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
  std::list<Share *> * share_queue;
  std::map<int,Player *> * players;
  std::vector<Player *> * players2;
  std::map<int,Player *> * players3;
  int submit(Share * s);  
  int payment();
  int reset();
  int removePlayer(Player * p);
  int addPlayer(Player * p);
  float getArrivalRate();
  Pool(int n, std::map<int,Player *> * players);

};



class Player{
public:
  float lambda;
  std::poisson_distribution<int> * dist;
  int id;
  float hash;
  bool has_solution;
  int paid_shares;
  Share * solution;
  std::default_random_engine gen;
  std::queue<Share *> * pool_Q;
  std::set<Share *> * share_set;
  Pool * pool;
  int (*strat)(Player * p);
  int strategy(){
    return (*strat)(this);
  }
  int leavePool();
  int joinPool(Pool * p);
  int reset();
  int mineBlocks();
  Player(float hash, int id);
};


class BlockMaker{
public:
  std::map<int,Player *> * players;
  std::list<Share *> * shares;
  std::poisson_distribution<int> * poisson;
  Share * nextShare();
  BlockMaker(int num_players,std::map<int,Player *> * players);
private:
  int prepareShares();
};


