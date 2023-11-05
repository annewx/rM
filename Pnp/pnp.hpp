//
// Created by anne on 10/28/23.
//

#ifndef ARMOR_PNP_HPP
#define ARMOR_PNP_HPP
#include <opencv2/opencv.hpp>
#include "vector"
#include "../Detect/detect.hpp"



class pnp {
public:

    cv::Mat distCoeffs = (Mat_<double>(5,1)<<-0.313818281448022,0.16042483,0,0,0);
    cv::Mat cameraMatrix = (Mat_<double>(3,3)<<1572.4,0,655,0,1572.4,503.4,0,0,1);
    void pnpSolve(armor &armorPoint);
    float yaw,pitch,pitch_off;
    void offSet(armor &armorPoint);
    int iter = 20;
    float ay,ry,thera,t;
    float x,y;
    float k=0.01,g=9.8;
    float v= 30;


};


#endif //ARMOR_PNP_HPP
