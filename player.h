#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"

//Modified by Paulo Costa.

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    
    Side player_side;
    Side opponent_side;
    
    Board *board;
    
    int score(Board * b, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif