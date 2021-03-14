#include "PuzzleState.h"

#include <QDebug>

#include <random>
#include <map>
#include <assert.h>

PuzzleState::PuzzleState()
{

}

PuzzleState::PuzzleState(unsigned matSize) :
    m_matrixSize(matSize),
    m_tiles(std::vector<unsigned>(matSize * matSize))
{
}

PuzzleState::PuzzleState(unsigned matSize, const std::vector<unsigned> &configuration) :
    m_matrixSize(matSize),
    m_tiles(configuration)
{
}

PuzzleState PuzzleState::generateRandomState(unsigned matSize)
{
    PuzzleState randomState;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned> distance(0, matSize * matSize - 1);

    do
    {
        std::map<unsigned, bool> usedTiles;
        std::vector<unsigned> configuration = std::vector<unsigned>(matSize * matSize);

        for(unsigned tileIndex = 0; tileIndex < matSize * matSize; tileIndex++)
        {
            unsigned tile;

            do
            {
                tile = distance(mt);
            } while(usedTiles[tile]);

            usedTiles[tile] = true;
            configuration[tileIndex] = tile;
        }

        randomState = PuzzleState(matSize, configuration);
    }while(!randomState.isSolvable());

    return randomState;
}

bool PuzzleState::isSolvable() const
{
    unsigned inversions = this->calculateInversions();
    unsigned emptyBackwardRow = m_matrixSize - this->getGridFromTile(0).first;


    if(m_matrixSize % 2 == 1)
    {
        return (inversions % 2 == 0);
    }
    else
    {
        bool blankOnOdd = (emptyBackwardRow % 2 == 1);
        return (blankOnOdd == (inversions % 2 == 0));
    }
}

unsigned PuzzleState::calculateInversions() const
{
    unsigned inversions = 0;

    for(unsigned first = 0; first < m_tiles.size() - 1; first++)
    {
        if(m_tiles[first] == 0)
        {
            continue;
        }

        for(unsigned second = first + 1; second < m_tiles.size(); second++)
        {
            if(m_tiles[second] && m_tiles[first] > m_tiles[second])
            {
                inversions++;
            }
        }
    }

    return inversions;
}

std::pair<unsigned, unsigned> PuzzleState::getGridFromArray(unsigned arrayIndex) const
{
    return {arrayIndex / m_matrixSize, arrayIndex % m_matrixSize};
}

std::pair<unsigned, unsigned> PuzzleState::getGridFromTile(unsigned tile) const
{
    return getGridFromArray(getIndex(tile));
}

unsigned PuzzleState::getIndex(unsigned tile) const
{
    for(unsigned i = 0; i < m_tiles.size(); i++)
    {
        if(m_tiles[i] == tile)
        {
            return i;
        }
    }

    assert("Error finding tile index");
    return 0;
}

bool PuzzleState::isGoalState() const
{
    for(unsigned index = 0; index < m_matrixSize * m_matrixSize - 1; index++)
    {
        if(m_tiles[index] != index + 1)
        {
            return false;
        }
    }

    return m_tiles[m_matrixSize * m_matrixSize - 1] == 0;
}

std::vector<unsigned> PuzzleState::getState() const
{
    return m_tiles;
}

void PuzzleState::setState(const std::vector<unsigned> &configuration)
{
    m_tiles = configuration;
}

void PuzzleState::swapTiles(unsigned int index1, unsigned int index2)
{
    unsigned temp = m_tiles[index1];
    m_tiles[index1] = m_tiles[index2];
    m_tiles[index2] = temp;
}

std::pair<unsigned, unsigned> PuzzleState::attemptMove(unsigned index, bool &succes)
{
    const std::vector<std::pair<int, int>> neighbours =
    {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };

    std::pair<unsigned, unsigned> currentPosition = getGridFromArray(index);

    for(int neighbour = 0; neighbour < 4; neighbour++)
    {
        std::pair<int, int> nextPosition = {currentPosition.first + neighbours[neighbour].first,
                                            currentPosition.second + neighbours[neighbour].second};

        if(nextPosition.first >= 0 && nextPosition.first < (int)m_matrixSize &&
           nextPosition.second >= 0 && nextPosition.second < (int)m_matrixSize)
        {
            if(getTile((unsigned)nextPosition.first * m_matrixSize + nextPosition.second) == 0)
            {
                succes = true;
                return nextPosition;
            }
        }
    }

    succes = false;
    return {0, 0};
}

unsigned PuzzleState::getTile(unsigned index) const
{
    return m_tiles[index];
}
