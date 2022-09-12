//
// Created by Ashray Gupta on 9/12/22.
//

#ifndef UNTITLED_ROBOTARM_H
#define UNTITLED_ROBOTARM_H


#include <vector>
#include "Pose3d.h"

class RobotArm {
private:
    std::vector<float> linkLengths;
    std::vector<float> jointAngles;

public:
    RobotArm();
    explicit RobotArm(std::vector<float> linkLengths);
    RobotArm(std::vector<float> linkLengths, std::vector<float> jointAngles);

    std::vector<Pose3d> solveFK() const;
    std::vector<Pose3d> solveFK(std::vector<float> jointAngles);
};


#endif //UNTITLED_ROBOTARM_H
