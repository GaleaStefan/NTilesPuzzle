#ifndef PUZZLESTATE_H
#define PUZZLESTATE_H

#include <vector>
#include <utility>

class PuzzleState
{
public:
    PuzzleState();
    PuzzleState(unsigned matSize);
    PuzzleState(unsigned matSize, const std::vector<unsigned>& configuration);

    static PuzzleState generateRandomState(unsigned matSize);

    std::vector<unsigned> getState() const;
    void setState(const std::vector<unsigned>& configuration);

    void swapTiles(unsigned index1, unsigned index2);
    std::pair<unsigned, unsigned> attemptMove(unsigned index, bool& succes);
    unsigned getTile(unsigned index) const;

    std::pair<unsigned, unsigned> getGridFromArray(unsigned arrayIndex) const;
    std::pair<unsigned, unsigned> getGridFromTile(unsigned tile) const;
    unsigned getIndex(unsigned tile) const;

private:
    unsigned m_matrixSize;
    std::vector<unsigned> m_tiles;

private:

    bool isSolvable() const;
    unsigned calculateInversions() const;
};

#endif // PUZZLESTATE_H
