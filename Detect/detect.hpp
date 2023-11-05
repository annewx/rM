//
// Created by anne on 10/26/23.
//

#ifndef ARMOR_DETECT_HPP
#define ARMOR_DETECT_HPP
#include "opencv2/opencv.hpp"
#include "iostream"
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;
using namespace cv;
struct armor{
    armor() = default;
    cv::Mat img;
    cv::Mat softmax_prob;
    cv::Mat blob;
    cv::Mat number_image;
    cv::Point2f left_top;
    cv::Point2f left_bottom;
    cv::Point2f right_top;
    cv::Point2f right_bottom;
    cv::Point2f rect_center;
    std::string armor_type;
    std::string label_id;
    float pitch;
    float yaw;
    float realDistance;
    float confidence;
    Mat translation_vector;
    Mat rotation_vector;
};
class detect {
public:
    cv::VideoCapture video;
    cv::Mat img,pre;
    std::string enemyColor = "blue";
    cv::dnn::Net net = cv::dnn::readNetFromONNX("../model/fc.onnx");
    cv::Mat softmax_prob;
    cv::Mat blob;
    cv::Mat number_image;
    std::vector<cv::RotatedRect> lightPoint;
    std::vector<cv::RotatedRect> light;
    std::vector<armor> armorPoint;
    std::vector<std::string> numClasses={"Base","1","2","3","4","5","Guard","Outpost","Negative"};
    std::string serData,readData;
    int list = 0;

    void readVideo(const std::string &videoPath);
    void imgProcess();
    void findLightBar();
    void numClassify(const std::string &model_path);



};


#endif //ARMOR_DETECT_HPP
