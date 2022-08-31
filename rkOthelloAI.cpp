//rkOthelloAI.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include "rkOthelloAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,kumarrn::rkOthelloAI,"RKOthelloAI#25 (Required)");

namespace {

    int searchthis(const OthelloGameState& state, int depth, bool myMove) {
        if (depth == 0) 
        {
            if (myMove == state.isWhiteTurn()) 
                return state.whiteScore() - state.blackScore();
            else 
                return state.blackScore() - state.whiteScore();
        }
        else 
        {
            if(myMove == state.isWhiteTurn()) 
            {
                int validmovecount = -1;
                int bestchoice = -10000;
                for (int w = 0; w< state.board().width(); w++) 
                {
                    for (int h = 0; h < state.board().height(); h++) 
                    {
                        if (state.isValidMove(w,h))
                        {
                            validmovecount++;
                            std:: unique_ptr<OthelloGameState> clone = state.clone();
                            clone ->makeMove(w,h);
                            
                            int thischoice = searchthis(*clone,depth-1,myMove);


                            // Detecting Killer Moves
                            if (clone->isGameOver()) 
                            {
                                thischoice = 10000000;
                            }
                            //Choose the corner pieces first for importance
                            if( (w == 0 && h == 0) || (w== 0 && h== state.board().height()-1) || (w == state.board().width()-1 && h == 0) 
                                || (w == state.board().width()-1 && h == state.board().height() -1)) 
                                {
                                    thischoice = 1000000;
                                }

                            // Blocking 
                            if (validmovecount == -1) {
                                bestchoice = 1000000;
                            }
                            // Blacklisting
                            if (thischoice < -10000) {
                                thischoice = -100000;
                            }

                            // if this move is better than the previous best move
                            if (thischoice > bestchoice) 
                            {
                                bestchoice = thischoice;
                            }
                        }
                     } 
                }
                return bestchoice;
            }
            else {
                int bestchoice = 10000;
                int validmovecount = -1;
                for (int w = 0; w< state.board().width(); w++) 
                {
                    for (int h = 0; h < state.board().height(); h++) 
                    {
                        if (state.isValidMove(w,h)) {
                            validmovecount++;
                            std:: unique_ptr<OthelloGameState> clone = state.clone();
                            clone ->makeMove(w,h);
                            int thischoice = searchthis(*clone,depth-1,myMove);

                            //Detecting Killer Move
                            if (clone->isGameOver()) 
                            {
                                thischoice = -10000000;
                            }

                            // Choose the corner pieces for importance
                            if( (w == 0 && h == 0) || (w== 0 && h== state.board().height()-1) || (w == state.board().width()-1 && h == 0) 
                                || (w == state.board().width()-1 && h == state.board().height() -1)) 
                                {
                                    thischoice = -1000000;
                                }

                            // Blocking 
                            if (validmovecount == -1) {
                                bestchoice = -1000000;
                            }
                            
                            // blacklisting
                            if (thischoice > 10000) {
                                thischoice = 100000;
                            }   

                            // if this move is better than the previous best move                             
                            if (thischoice < bestchoice) 
                            {
                                bestchoice = thischoice;
                            }
                        }
                     } 
                }
                return bestchoice;

            }
    }
}
}


std::pair <int,int> kumarrn::rkOthelloAI::chooseMove(const OthelloGameState& state)
{
    int myMove = state.isWhiteTurn();
    int bestchoice = -10000;
    std::pair<int,int> choice;
    for (int w = 0; w< state.board().width(); w++) 
    {
        for (int h = 0; h < state.board().height(); h++) 
        {
            if (state.isValidMove(w,h)) 
            {   
                std::unique_ptr<OthelloGameState> clone = state.clone();
                clone->makeMove(w,h);
                int newchoice = searchthis(*clone,4,myMove);
                if (newchoice > bestchoice)
                {
                    choice = std::pair(w,h);
                    bestchoice = newchoice;
                }
            }
        }
    }
    //If couln't find a better move, choose first available move
    if (choice == std::pair(0,0))
        {
    for (int w = 0; w< state.board().width(); w++) 
        {
        for (int h = 0; h < state.board().height(); h++) 
            {
            if (state.isValidMove(w,h)) 
                {  
                    choice = std::pair(w,h);
                }
            }
        }

    }

    return choice;
}