//
// Created by Ashray Gupta on 9/11/22.
//

#include "Pose3d.h"

double Pose3d::getX() const {
    return x;
}

double Pose3d::getY() const {
    return y;
}

double Pose3d::getZ() const {
    return z;
}

Pose3d::Pose3d(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Pose3d::Pose3d() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
