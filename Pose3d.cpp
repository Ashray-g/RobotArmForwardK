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

double Pose3d::getRotX() const {
    return rot_x;
}

double Pose3d::getRotY() const {
    return rot_y;
}

double Pose3d::getRotZ() const {
    return rot_z;
}

Pose3d::Pose3d(double x, double y, double z, double rot_x, double rot_y, double rot_z) {
    this->x = x;
    this->y = y;
    this->z = z;

    this->rot_x = rot_x;
    this->rot_y = rot_y;
    this->rot_z = rot_z;
}

Pose3d::Pose3d() {
    this->x = 0;
    this->y = 0;
    this->z = 0;

    this->rot_x = 0;
    this->rot_y = 0;
    this->rot_z = 0;
}
