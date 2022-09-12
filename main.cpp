#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "MathUtils.h"

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

    for(int i = 1;i<DHTable.size();i++){
        mult = mult * links[i];

        cout << "Joint " << i << " location: \n" << "x: " << mult(0, 3) <<  "   y: " << mult(1, 3) << "   z: " << mult(2, 3) << "\n";

        MathUtils mathUtil;
        vector<double> rotation = mathUtil.rotationMatrixToEulerAngles(mult);

        cout << rotation[0] << " " << rotation[1] << " " << rotation[2] << "\n\n";
    }

    return 0;
}

