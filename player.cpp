#include "player.h"
//AI coded and developed by Paulo Costa

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    player_side = side;
    if (side == WHITE)
        opponent_side = BLACK;
    else
        opponent_side = WHITE;
    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/* Taken from "A genetic algorithm to improve an Othello program"
 * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.16.1218&rep=rep1&type=pdf
 * */
    int values[8][8] = { {500 , -150 , 30 , 10 , 10 , 30 , -150 , 500},
    {-150 , -250 , 0 , 0 , 0 , 0 , -250 , -150},
    {30 , 0 , 1 , 2 , 2 , 1 , 0 , 30},
    {10 , 0 , 2 , 16 , 16 , 2 , 0 , 10},
    {10 , 0 , 2 , 16 , 16 , 2 , 0 , 10},
    {30 , 0 , 1 , 2 , 2 , 1 , 0 , 30},
    {-150 , -250 , 0 , 0 , 0 , 0 , -250 , -150},
    {500 , -150 , 30 , 10 , 10 , 30 , -150 , 500} };

/*
 * Returns the score of a given side using the aforementioned array.
 */
int Player::score(Board * b, Side side)
{
    int total = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(b->occupied(i, j))
            {
                if(b->get(side, i, j))
                    total += values[i][j];
                else
                    total -= values[i][j];
            }
        }
    }
    return total;
}

/*
 * Decides the next move to play using conditional nested loops up to depth 5
 * and factoring in a minimax tree, the heuristic array defined previously,
 * and the opponent's previous move.
 */
Move * Player::doMove(Move * opponentsMove, int msLeft)
{
    board->doMove(opponentsMove, opponent_side);
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            values[i][j]++;
	}
    }
    
    int score_0  = -99999;
    int sc_0 = 0;
    int i_final = -1;
    int j_final = -1;
    bool ANOTHER = false;
    Move *return_move = NULL;
    
    for (int i_0 = 0; i_0 < 8; i_0++)
    {
      for (int j_0 = 0; j_0 < 8; j_0++)
      {
        Move *m0 = new Move(i_0, j_0);
        if (board->checkMove(m0, player_side))
        {
          Board *b = board->copy();
          b->doMove(m0, player_side);
          int score = -99999;
          int s = 0;
          for(int i = 0; i < 8; i++)
          {
            for(int j = 0; j < 8; j++)
            {
              Move *m =  new Move(i,j);
              if(b->checkMove(m, opponent_side))
              {
                Board *b1 = b->copy();
                b1->doMove(m, opponent_side); // Depth 1
                int score1  = -99999;
                int sc_1 = 0;
                for(int i_1 = 0; i_1 < 8; i_1++)
                {
                  for(int j_1 = 0; j_1 < 8; j_1++)
                  {
                    Move *m1 =  new Move(i_1, j_1);
                    if(b1->checkMove(m1, player_side))
                    {
                      Board *b2 = b1->copy();
                      b2->doMove(m1, player_side); // Depth 2
                      int score2  = -99999;
                      int sc_2 = 0;
                      for(int i_2 = 0; i_2 < 8; i_2++)
                      {
                        for(int j_2 = 0; j_2 < 8; j_2++)
                        {
                          Move *m2 =  new Move(i_2, j_2);
                          if(b2->checkMove(m2, opponent_side))
                          {
                            Board *b3 = b2->copy();
                            b3->doMove(m2, opponent_side); // Depth 3
                            int score3  = -99999;
                            int sc_3 = 0;
                            for(int i_3 = 0; i_3 < 8; i_3++)
                            {
                              for(int j_3 = 0; j_3 < 8; j_3++)
                              {
                                Move *m3 =  new Move(i_3, j_3);
                                if(b3->checkMove(m3, player_side))
                                {
                                  Board *b4 = b3->copy();
                                  b4->doMove(m3, player_side); // Depth 4
                                  int score4 = -99999;
                                  int sc_4 = 0;
                                  for(int i_4 = 0; i_4 < 8; i_4++)
                                  {
                                    for(int j_4 = 0; j_4 < 8; j_4++)
                                    {
                                      Move *m4 = new Move(i_4, j_4);
                                      if(b4->checkMove(m4, opponent_side))
                                      {
                                        Board *b5 = b4->copy();
                                        b5->doMove(m4, opponent_side); // Depth 5
                                        if(ANOTHER)
                                        {
                                          int score5 = -99999;
                                          int sc_5 = 0;
                                          for(int i_5 = 0; i_5 < 8; i_5++)
                                          {
                                            for(int j_5 = 0; j_5 < 8; j_5++)
                                            {
                                              Move *m5 = new Move(i_5, j_5);
                                              if(b5->checkMove(m5, player_side))
                                              {
                                                Board *b6 = b5->copy();
                                                b6->doMove(m5, player_side); // Depth 6 (if ANOTHER is true)
                                                sc_5 = this->score(b6, player_side);
                                                if(sc_5 > score5)
                                                {
                                                  score5 = sc_5;
                                                }
                                                delete b6;
                                              }
                                              delete m5;
                                            }
                                          }
                                          sc_4 = -score5;
                                          if(sc_5 > score5)
                                          {
                                            sc_4 = 10000 + this->score(b5, opponent_side);
                                          }
                                        }
                                        else
                                        {
                                          sc_4 = this->score(b5, opponent_side);
                                        }
                                        if(sc_4 > score4)
                                        {
                                          score4 = sc_4;
                                        }
                                        delete b5;
                                      }
                                      delete m4;
                                    }
                                  }
                                  sc_3 = -score4;
                                  if(sc_4 > score4)
                                  {
                                    sc_3 = 10000 + this->score(b4, player_side);
                                  }
                                  if(sc_3 > score3)
                                  {
                                    score3 = sc_3;
                                  }
                                  delete b4;
                                }
                                delete m3;
                              }
                            }
                            sc_2 = -score3;
                            if(sc_3 > score3)
                            {
                              sc_2 = 10000 + this->score(b3, opponent_side);
                            }
                            if(sc_2 > score2)
                            {
                              score2 = sc_2;
                            }
                            delete b3;
                          }
                          delete m2;
                        }
                      }
                      sc_1 = -score2;
                      if(sc_2 > score2)
                      {
                        sc_1 = 10000 + this->score(b2, player_side);
                      }
                      if (sc_1 > score1)
                      {
                        score1 = sc_1;
                      }
                      delete b2;
                    }
                    delete m1;
                  }
                }
                s = -score1;
                if(sc_1 > score1)
                {
                  s = 10000 + this->score(b1, opponent_side);
                }
                if(s > score)
                {
                  score = s;
                }
                delete b1;
              }
              delete m;
            }
          }
          sc_0 = -score;
          if(s > score)
          {
            sc_0 = 10000 + this->score(b, player_side);
          }
          if(sc_0 > score_0)
          {
            score_0 = sc_0;
            i_final = i_0;
            j_final = j_0;
          }
          delete b;
        }
        delete m0;
      }
    }
    
    if (i_final != -1 && j_final != -1){
        return_move = new Move(i_final, j_final);
    }
    
    board->doMove(return_move, player_side);
    return return_move;
}