//
// Created by Ashray Gupta on 9/11/22.
//
#include <Eigen/Dense>
#include <vector>
#include "MathUtils.h"

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;

using namespace std;

vector<double> MathUtils::rotationMatrixToEulerAngles(MatrixXd a) const {
    double sy = sqrt(a(0, 0) * a(0, 0) + a(1, 0) * a(1, 0));

    double x, y, z;

    x = atan2(a(2, 1), a(2, 2));
    y = atan2(-a(2, 0), sy);
    z = atan2(a(1, 0), a(0, 0));

    vector<double> vec = {x*180/3.1415, y*180/3.1415, z*180/3.1415};

    return vec;
}

MathUtils::MathUtils() {

}
