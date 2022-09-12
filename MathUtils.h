//
// Created by Ashray Gupta on 9/11/22.
//

#ifndef UNTITLED_MATHUTILS_H
#define UNTITLED_MATHUTILS_H

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;

class MathUtils {
public:
    MathUtils();
    std::vector<double> rotationMatrixToEulerAngles(MatrixXd a) const;
};


#endif //UNTITLED_MATHUTILS_H
