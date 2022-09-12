//
// Created by Ashray Gupta on 9/12/22.
//

#include "RobotArm.h"
#include <Eigen/Dense>
#include <utility>
#include "MathUtils.h"

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
using namespace std;

RobotArm::RobotArm() {
    linkLengths = std::vector<float>(4);
    jointAngles = std::vector<float>(4);
}

RobotArm::RobotArm(std::vector<float> linkLengths) {
    this->linkLengths = std::move(linkLengths);
    jointAngles = std::vector<float>(4);
}

RobotArm::RobotArm(std::vector<float> linkLengths, std::vector<float> jointAngles) {
    this->linkLengths = std::move(linkLengths);
    this->jointAngles = std::move(jointAngles);
}

std::vector<Pose3d> RobotArm::solveFK() const {
    // Denavit-Hartenberg Parameters
    vector<vector<float>> DHTable = {{linkLengths[0], 0, 0, jointAngles[0] * 3.1415f / 180},
                                     {linkLengths[1], 0, 0, jointAngles[1] * 3.1415f / 180},
                                     {linkLengths[2], 0, 0, jointAngles[2] * 3.1415f / 180},
                                     {linkLengths[3], 0, 0, jointAngles[3] * 3.1415f / 180}};

    // Homogeneous transform matrix for each link
    vector<MatrixXd> links = {};

    for(int i = 0;i<DHTable.size();i++){
        links.emplace_back(4, 4);
        links[i] <<
                 cos(DHTable[i][3]), -sin(DHTable[i][3]) * cos(DHTable[i][1]), sin(DHTable[i][3]) * sin(DHTable[i][1]), DHTable[i][0] * cos(DHTable[i][3]),

                sin(DHTable[i][3]), cos(DHTable[i][3]) * cos(DHTable[i][1]), -cos(DHTable[i][3]) * sin(DHTable[i][1]), DHTable[i][0] * sin(DHTable[i][3]),

                0, sin(DHTable[i][1]), cos(DHTable[i][1]), DHTable[i][2],

                0, 0, 0, 1;
    }


    // Find Pose3d of each join with forward-kinematics
    MatrixXd mult = links[0];

    vector<Pose3d> jointLocations;

    MathUtils mathUtil;
    vector<double> rotation = mathUtil.rotationMatrixToEulerAngles(mult);

    jointLocations.push_back(*new Pose3d(mult(0, 3), mult(1, 3), mult(2, 3), rotation[0], rotation[1], rotation[2]));


    for(int i = 1;i<DHTable.size();i++){
        mult = mult * links[i];

        rotation = mathUtil.rotationMatrixToEulerAngles(mult);

        jointLocations.push_back(*new Pose3d(mult(0, 3), mult(1, 3), mult(2, 3), rotation[0], rotation[1], rotation[2]));
    }

    return jointLocations;
}

std::vector<Pose3d> RobotArm::solveFK(std::vector<float> jointAngles){
    this->jointAngles = std::move(jointAngles);
    return solveFK();
}


