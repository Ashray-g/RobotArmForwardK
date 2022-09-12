#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "MathUtils.h"
#include "Pose3d.h"

using namespace std;


typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;

int main() {

    vector<vector<float>> DHTable = {{1, 0, 0, 0},
                                     {1, 0, 0, 3.14/6},
                                     {1, 0, 0, 3.14/6},
                                     {1, 0, 0, 3.14/6}};

    vector<MatrixXd> links = {};


    for(int i = 0;i<DHTable.size();i++){
        links.emplace_back(4, 4);
        links[i] <<
                cos(DHTable[i][3]), -sin(DHTable[i][3]) * cos(DHTable[i][1]), sin(DHTable[i][3]) * sin(DHTable[i][1]), DHTable[i][0] * cos(DHTable[i][3]),

                sin(DHTable[i][3]), cos(DHTable[i][3]) * cos(DHTable[i][1]), -cos(DHTable[i][3]) * sin(DHTable[i][1]), DHTable[i][0] * sin(DHTable[i][3]),

                0, sin(DHTable[i][1]), cos(DHTable[i][1]), DHTable[i][2],

                0, 0, 0, 1;
    }

    MatrixXd mult = links[0];

    vector<Pose3d> jointLocations;

    for(int i = 1;i<DHTable.size();i++){
        mult = mult * links[i];

        MathUtils mathUtil;
        vector<double> rotation = mathUtil.rotationMatrixToEulerAngles(mult);

        jointLocations.push_back(*new Pose3d(mult(0, 3), mult(1, 3), mult(2, 3), rotation[0], rotation[1], rotation[2]));
    }

    int i = 0;
    for(Pose3d pose : jointLocations){
        i++;
        cout << "Joint " << i << ": \n" << "POSE x: " << pose.getX() <<  "   y: " << pose.getY() << "   z: " << pose.getZ() << "\n";
        cout << "ORIENTATION Around x: " << pose.getRotX() << " Around y: " << pose.getRotY() << " Around z: " << pose.getRotZ() << "\n\n";
    }

    return 0;
}

