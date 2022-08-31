//rkOthelloAI.hpp
#ifndef RKOTHELLOAI_HPP
#define RKOTHELLOAI_HPP

#include "OthelloAI.hpp"


namespace kumarrn
{
    class rkOthelloAI: public OthelloAI
    {
        public:
            std::pair<int,int> chooseMove(const OthelloGameState& state) override;

    };
}

#endif