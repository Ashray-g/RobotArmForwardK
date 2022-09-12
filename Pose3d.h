//
// Created by Ashray Gupta on 9/11/22.
//

#ifndef UNTITLED_POSE3D_H
#define UNTITLED_POSE3D_H


class Pose3d {
private:
    double x;
    double y;
    double z;

    double rot_x;
    double rot_y;
    double rot_z;

public:
    Pose3d();
    Pose3d(double x, double y, double z, double rot_x, double rot_y, double rot_z);

    double getX() const;
    double getY() const;
    double getZ() const;

    double getRotX() const;
    double getRotY() const;
    double getRotZ() const;

};

#endif //UNTITLED_POSE3D_H
