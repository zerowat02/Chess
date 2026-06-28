#pragma once
#include<Board.h>
#include<CoordinateTypes.h>
#include <set>
#include<vector>
#include <cfloat>
#include <cmath>
#include<algorithm>
#include<Logger.h>


struct Node{
    GridPos parent = {-1,-1};
    float f = FLT_MAX;
    float h = FLT_MAX;
    float g = FLT_MAX;
};

struct OpenNode
{
    float f;
    GridPos pos;

    bool operator<(const OpenNode& other) const
    {
        if (f != other.f)
            return f < other.f;

        return pos < other.pos;
    }
};

class PathPlanner
{
    int getHValue(GridPos form, GridPos to);
    vector<GridPos> tracePath(Node nodes[Board::ROW][Board::COL], GridPos dest);
    void loggPath(vector<GridPos> path);
public:
    vector<GridPos> findPath(Board& board, GridPos form, GridPos to);
};
