#ifndef SOLVERSTATE_H
#define SOLVERSTATE_H

#include "gameLogic/PuzzleState.h"

class SolverState : public PuzzleState
{
public:
    SolverState();
    SolverState(unsigned grid, std::vector<unsigned> tiles);

    static std::pair<unsigned, unsigned>    getGridPosition(unsigned index, unsigned grid);

    void                                    calculateDistances();

    unsigned                                getManhattanDistance() const;
    void                                    setManhattanDistance(unsigned manhattanDistance);

    SolverState                             swap(std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>);

    bool                                    operator==(const SolverState& other) const;

private:
    unsigned m_manhattanDistance;
};

template<> struct std::hash<SolverState>
{
    std::size_t operator()(const SolverState& state) const noexcept;
};

#endif // SOLVERSTATE_H
