#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "MathUtils.h"
#include "Pose3d.h"
#include "RobotArm.h"

using namespace std;


typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;

int main() {

    //Physical constants
    vector<float> linkLengths = {1, 1, 1, 1};

    RobotArm robotArm(linkLengths);

    //Variable constants
    vector<float> jointAngles = {0, 30, 30, 30};


    vector<Pose3d> jointLocations = robotArm.solveFK(jointAngles);

    // Output
    int i = 0;
    for(Pose3d pose : jointLocations){
        i++;
        cout << "Joint " << i << ": \n" << "[POSE] x: " << pose.getX() <<  " | y: " << pose.getY() << " | z: " << pose.getZ() << "\n";
        cout << "[ORIENTATION] Around x: " << pose.getRotX() << " | Around y: " << pose.getRotY() << " | Around z: " << pose.getRotZ() << "\n\n";
    }

    return 0;
}

