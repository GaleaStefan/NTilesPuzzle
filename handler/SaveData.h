#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <vector>

#include <gameLogic/PuzzleState.h>

struct SaveData
{
    unsigned                    m_moves;
    unsigned                    m_hints;
    unsigned                    m_time;
    unsigned                    m_grid;
    unsigned                    m_state;
    std::vector<PuzzleState>    m_history;
};

#endif // SAVEDATA_H
