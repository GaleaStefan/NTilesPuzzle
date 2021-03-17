#include "SolverState.h"

#include <math.h>

SolverState::SolverState() :
    PuzzleState()
{
    m_manhattanDistance = 0;
}

SolverState::SolverState(unsigned grid, std::vector<unsigned> tiles) :
    PuzzleState(grid, tiles)
{
    calculateDistances();
}

std::pair<unsigned, unsigned> SolverState::getGridPosition(unsigned index, unsigned grid)
{
    return {index / grid, index % grid};
}

void SolverState::calculateDistances()
{
    m_manhattanDistance = 0;

    for(unsigned index = 0; index < m_tiles.size(); index++)
    {
        std::pair<unsigned, unsigned> tilePos = SolverState::getGridPosition(index, m_matrixSize);
        std::pair<unsigned, unsigned> destPos = SolverState::getGridPosition(m_tiles[index] + m_tiles.size() * (m_tiles[index] == 0), m_matrixSize);

        m_manhattanDistance += abs((int)(tilePos.first - destPos.first)) + abs((int)(tilePos.second - destPos.second));
    }
}

unsigned SolverState::getManhattanDistance() const
{
    return m_manhattanDistance;
}

void SolverState::setManhattanDistance(unsigned manhattanDistance)
{
    m_manhattanDistance = manhattanDistance;
}

SolverState SolverState::swap(std::pair<unsigned, unsigned> tile1, std::pair<unsigned, unsigned> tile2)
{
    unsigned index1 = tile1.first * m_matrixSize + tile1.second;
    unsigned index2 = tile2.first * m_matrixSize + tile2.second;

    SolverState newState(m_matrixSize, m_tiles);
    newState.swapTiles(index1, index2);

    return newState;
}

bool SolverState::operator==(const SolverState &other) const
{
    return m_tiles == other.m_tiles;
}

std::size_t std::hash<SolverState>::operator()(const SolverState& state) const noexcept
{
    std::size_t seed = state.getState().size();

    for(auto& i : state.getState())
    {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
}
