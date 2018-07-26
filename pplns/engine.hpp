#include "strats.hpp"

int states(Player ** p, int num_players);
int rounds(Pool ** pools,Player ** players, int num_rounds, int num_players);
int rounds2(Pool ** pools,std::map<int,Player *> * players, int num_blocks, int num_players);
