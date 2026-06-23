#include<RobotConfig.h>
#include<Coordinatetypes.h>
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

    StepPos GridMoveToSteps(GridPos from, GridPos to)
    {
        int dx = to.first - from.first;
        int dy = to.second - from.second;
        return {
           dx*cellSize, dy*cellSize
        };
    }
};