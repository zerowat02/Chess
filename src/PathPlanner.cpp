#include "PathPlanner.h"



int PathPlanner::getHValue(GridPos from, GridPos to)
{
    return sqrt(pow(to.first-from.first,2)+pow(to.second-from.second,2));
}

vector<GridPos> PathPlanner::tracePath(Node nodes[Board::ROW][Board::COL],GridPos dest)
{

    
    vector<GridPos> path;

    GridPos current = dest;

    while (true)
    {
        path.push_back(current);
        GridPos parent = nodes[current.first][current.second].parent;
        if (parent == current)   // reached source
            break;

        current = parent;
    }
    
    reverse(path.begin(), path.end());
    return path;
}

vector<GridPos> PathPlanner::findPath(Board &board, GridPos src, GridPos dest)
{
    // If the source is out of range
    if (board.isValid(src) == false) {
        // Source is invalid
        return{};
    }

    // If the destination is out of range
    if (board.isValid(dest) == false) {
        // Destination is invalid
        return{};
    }

    // If the destination cell is already occupied by another piece
    if (board.isOccupied(dest)== true) {
        //the destination is blocked
        return{};
    }

    // If the destination cell is the same as source cell
    if (board.isOccupied(dest)== true) {
        return{src};
    }


    set<OpenNode> visitCells;
    visitCells.insert({0.0f, src});

    Node nodes[Board::ROW][Board::COL];

    nodes[src.first][src.second].parent = src;
    nodes[src.first][src.second].f = 0;
    nodes[src.first][src.second].g = 0;
    nodes[src.first][src.second].h = 0;

    bool visitedCells[Board::ROW][Board::COL] = {};

    while (!visitCells.empty())
    {
        OpenNode current = *visitCells.begin();
        visitCells.erase(visitCells.begin());

        GridPos currentPos = current.pos;

        // Ignore stale entries
        if (visitedCells[currentPos.first][currentPos.second])
            continue;

        visitedCells[currentPos.first][currentPos.second] = true;

        if (currentPos == dest)
            return tracePath(nodes, dest);

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // Skip current cell
                if (i == 0 && j == 0)
                    continue;

                GridPos nextPos = {
                    currentPos.first + i,
                    currentPos.second + j
                };

                if (!board.isValid(nextPos))
                    continue;

                if (board.isOccupied(nextPos))
                    continue;

                if (visitedCells[nextPos.first][nextPos.second])
                    continue;
                // cost of move depends on weather it's a vertical or horizontal move, or if it's diagonal (more costly),
                // also weather it's adiacent to another chess piece, as it will require lowering magnet power.
                float g = nodes[currentPos.first][currentPos.second].g
                        + sqrt(i*i + j*j) + (board.isAdiacientToOtherPiece(nextPos) ? 1.0f : 0.0f);

                float h = getHValue(nextPos, dest);

                float f = g + h;

                if (f < nodes[nextPos.first][nextPos.second].f)
                {
                    nodes[nextPos.first][nextPos.second].parent = currentPos;
                    nodes[nextPos.first][nextPos.second].g = g;
                    nodes[nextPos.first][nextPos.second].h = h;
                    nodes[nextPos.first][nextPos.second].f = f;

                    visitCells.insert({f, nextPos});
                }
            }
        }
    }

    return {};
}
