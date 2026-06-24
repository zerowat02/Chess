#pragma once
#include<Board.h>
#include<RobotConfig.h>
#include<Kinematics.h>
#include<PathPlanner.h>
#include<MotionController.h>

using namespace std;


class Robot
{
private:
    Board board;
    PathPlanner planner;
    MotionController motion;
    Kinematics kinematics;

    GridPos currentPosition;

public:
    void movePiece(GridPos src, GridPos dest);
};




