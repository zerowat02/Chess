#pragma once
#include<RobotConfig.h>
#include<CoordinateTypes.h>
#include<vector>
using namespace std;

class Kinematics
{
private:
    RobotConfig config;
    int cellSize; // amount of steps needed to traverse a cell
    vector <StepPos> compressGridPath(vector<GridPos> gridPath);
public:


    Kinematics(RobotConfig cfg)
        : config(cfg), cellSize(cfg.cellSize * cfg.stepsPerMm) {}

    vector <StepPos> GridPathTOSteps(vector<GridPos> gridPath);

    StepPos GridMoveToSteps(GridPos gridPos)
    {
        return {
           gridPos.first*cellSize+config.OffsetX, gridPos.second*cellSize+config.OffsetY
        };
    }
}; 