#include <iostream>
#include <Eigen/Dense>
#include <vector>


typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;

int main() {

    std::vector<std::vector<float>> DHTable = {{1, 0, 0, 0},
                                               {1, 0, 0, 3.14/4},
                                               {1, 0, 0, 3.14/4}};

    std::vector<MatrixXd> links = {};


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
    }

    std::cout << "x: " << mult(0, 3) <<  "   y: " << mult(1, 3) << "   z: " << mult(2, 3);


    return 0;
}


