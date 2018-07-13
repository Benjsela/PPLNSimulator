#include<stdlib.h>
#include<set>
#include<queue>
#include<vector>
#include<map>

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
  std::vector<Player *> * players2;
  std::map<int,Player *> * players3;
  int submit(Share * s);  
  int payment();
  int reset();
  int removePlayer(Player * p);
  int addPlayer(Player * p);
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
  int leavePool();
  int joinPool(Pool * p);
  int reset();
  Player(float hash, int id);
};



