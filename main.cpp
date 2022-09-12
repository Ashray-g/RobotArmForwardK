#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "MathUtils.h"
#include "Pose3d.h"

using namespace std;


typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;

int main() {

    //Physical constants
    vector<float> linkLengths = {1, 1, 1, 1};
    vector<float> jointAngles = {0, 30, 30, 30};

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

    // Output
    int i = 0;
    for(Pose3d pose : jointLocations){
        i++;
        cout << "Joint " << i << ": \n" << "[POSE] x: " << pose.getX() <<  " | y: " << pose.getY() << " | z: " << pose.getZ() << "\n";
        cout << "[ORIENTATION] Around x: " << pose.getRotX() << " | Around y: " << pose.getRotY() << " | Around z: " << pose.getRotZ() << "\n\n";
    }

    return 0;
}

