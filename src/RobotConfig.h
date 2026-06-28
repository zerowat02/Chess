#pragma once

struct RobotConfig
{
    int cellSize;
    int stepsPerMm;
    long OffsetX;
    long OffsetY;

    RobotConfig(int cs, int spmm, long ox = 0, long oy = 0)
        : cellSize(cs), stepsPerMm(spmm), OffsetX(ox), OffsetY(oy) {}
};