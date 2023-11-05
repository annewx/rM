//
// Created by anne on 10/28/23.
//

#include "pnp.hpp"
#include <opencv2/opencv.hpp>
#include "vector"
#include "../Detect/detect.hpp"
#define PI float(acos(-1))
using namespace std;
using namespace cv;

void pnp::pnpSolve(armor &armorPoint) {
    vector<Point2d> imagePoints;
    imagePoints.push_back(Point2d(armorPoint.left_top.x, armorPoint.left_top.y));
    imagePoints.push_back(Point2d(armorPoint.right_top.x, armorPoint.right_top.y));
    imagePoints.push_back(Point2d(armorPoint.right_bottom.x, armorPoint.right_bottom.y));
    imagePoints.push_back(Point2d(armorPoint.left_bottom.x, armorPoint.left_bottom.y));

    const std::vector<cv::Point3d> *Armor_Point;

    std::vector<Point3d> model_points;
    if (armorPoint.armor_type=="BIG") {
        model_points.push_back(Point3d(-115.0f, -27.5f, 0)); // 左上角顺时针
        model_points.push_back(Point3d(+115.0f,-27.5f, 0));
        model_points.push_back(Point3d(+115.0f, +27.5f, 0));
        model_points.push_back(Point3d(-115.0f, +27.5f, 0));
    }
    if (armorPoint.armor_type=="SMALL") {
        model_points.push_back(Point3d(-67.5f, -27.5f, 0)); // 左上角顺时针
        model_points.push_back(Point3d(+67.5f, -27.5f, 0));
        model_points.push_back(Point3d(+67.5f, +27.5f, 0));
        model_points.push_back(Point3d(-67.5f, +27.5f, 0));
    }
    Mat translation_vector;
    Mat rotation_vector;
    solvePnP(model_points, imagePoints, cameraMatrix, distCoeffs,
             rotation_vector, translation_vector, 0,SOLVEPNP_IPPE);
    translation_vector.at<double>(0,1) = -translation_vector.at<double>(0,1);
//    rotation_vector.convertTo(Rvec, CV_32F);  // 旋转向量转换格式
//    translation_vector.convertTo(Tvec, CV_32F); // 平移向量转换格式
    armorPoint.translation_vector = translation_vector;
    armorPoint.rotation_vector = rotation_vector;
//    cout<<translation_vector<<endl;
    armorPoint.realDistance=sqrt(pow(translation_vector.at<double>(0,0),2)+pow(translation_vector.at<double>(0,1),2)+pow(translation_vector.at<double>(0,2),2))/10;
    yaw = atan2(translation_vector.at<double>(0,0), translation_vector.at<double>(0,2))*180/PI;
    pitch = atan2(translation_vector.at<double>(0,1),sqrt(pow(translation_vector.at<double>(0,0),2)+pow(translation_vector.at<double>(0,2),2)))*180/PI;
    armorPoint.yaw = yaw;
//    cout<<"yaw"<<armorPoint.yaw;
//    cout<<"distance:"<<armorPoint.realDistance<<endl;

}
void pnp::offSet(armor &armorPoint){
    x = sqrt(pow(armorPoint.translation_vector.at<double>(0,0),2)+pow(armorPoint.translation_vector.at<double>(0,2),2))/100;
    y = armorPoint.translation_vector.at<double>(0,1)/100;
    ay = y;
    for(int i = 0;i<iter;i++){
        thera = atan2(ay,x);
        t = (exp(k*x)-1)/(k*v*cos(thera));
        ry = v*sin(thera)*t - g * pow(t, 2) / 2;
        ay = ay+(y-ry);
        if (abs(ay) < 0.001) {
            break;
        }
    }
    pitch_off = atan2(ay,x)*180/PI;
    armorPoint.pitch = pitch_off;
//    cout<<"pitch_off"<<armorPoint.pitch;
}
