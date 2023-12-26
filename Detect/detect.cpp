//
// Created by anne on 10/26/23.
//

#include "detect.hpp"
#include "opencv2/opencv.hpp"
#include "iostream"
#include <thread>
#include <cmath>

using namespace std;
using namespace cv;
void detect::readVideo(const std::string &videoPath) {
    video.open(videoPath,cv::CAP_FFMPEG);
    if (!video.isOpened()){
        cout<<"not video"<<endl;
    }
}
void detect::imgProcess(){

    vector<Mat> channels;
    split(img,channels);
    Mat imgGray;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
//    if(enemyColor =="blue"){
//        imgGray = channels.at(0) - channels.at(2);
//    }
//    else{
//        imgGray = channels.at(2) - channels.at(0);
//    }
    int value = 180;
    threshold(imgGray,img,value,255,0);
    Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(-1,-1));
    morphologyEx(img,pre,MORPH_OPEN,kernel);
}



void detect::findLightBar() {
    vector<vector<Point>> contours;
    vector<cv::Vec4i> hierarchy;
    vector<cv::Point2f> lightPoint;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<Rect>boundRect(contours.size());
    vector<RotatedRect>bar(contours.size());
    Point2f P[4];
    vector<Point2f>centerPoint;
    for(int i = 0;i<contours.size();i++){
        bar[i] = minAreaRect(Mat(contours[i]));
        boundRect[i] = boundingRect(Mat(contours[i]));
        cv::Scalar bgr;
        bgr = cv::mean(img);
        std::string lightColor;
        lightColor = bgr.val[0]>bgr.val[1] ? "blue":"red";
        if (lightColor!=enemyColor){
            continue;

        }

        vector<Point2f>::iterator center = find(centerPoint.begin(),centerPoint.end(),Point2f(bar[i].center.x,bar[i].center.y));
        if(center == centerPoint.end()){
            centerPoint.push_back(Point2f(bar[i].center.x,bar[i].center.y));
        }
        else{
            continue;
        }
        bar[i].points(P);
        line(pre,P[0],P[1],Scalar(0,255,0),2);
        line(pre,P[1],P[2],Scalar(0,255,0),2);
        line(pre,P[2],P[3],Scalar(0,255,0),2);
        line(pre,P[3],P[0],Scalar(0,255,0),2);
        double area = contourArea(contours[i]);
        if(area < 3 ||contours[i].size() <= 1){
            continue;
        }
        if(bar[i].size.width/bar[i].size.height > 1.2){
            continue;
        }
        else{
            light.push_back(bar[i]);
        }
    }
}
void detect::numClassify(const std::string &model_path) {
    armor armorClass;
    const int light_length = 12;
    const int warp_height = 28;
    const int small_armor_width = 32;
    const int large_armor_width = 54;
    const cv::Size roi_size(28, 20);
    const int top_y = (warp_height - light_length) / 2;
    const int bottom_y = top_y + light_length;
    const int warp_width = large_armor_width;
    while(light.size()>2){
        RotatedRect Bar = light[0];
        light.erase(light.begin());
        for (int i = 0;i<light.size();++i){
            Point2f rect1[4];
            Point2f rect2[4];
            Point2f left_bottom;
            Point2f left_top;
            Point2f right_bottom;
            Point2f right_top;
            Bar.points(rect1);
            light[i].points(rect2);

           if(rect1[0].y < rect1[2].y){
                Point2f pt;
                pt = rect1[3];
                rect1[0] = rect1[0];
                rect1[3] = rect1[1];
                rect1[1] = rect1[2];
                rect1[2] = pt;
            }

            if(rect2[0].y < rect2[2].y){
                Point2f pt;
                pt = rect2[3];
                rect2[3] = rect2[1];
                rect2[1] = rect2[2];
                rect2[0] = rect2[0];
                rect2[2] = pt;
            }
            float angleDiff = abs(Bar.angle - light[i].angle);
            float lenDiff = abs(Bar.size.height - light[i].size.height)/ max(Bar.size.height ,light[i].size.height);
            if (angleDiff > 20 || lenDiff > 1.5){
                continue;
            }

            float dis = pow(pow(Bar.center.x - light[i].center.x,2)+pow(Bar.center.y -light[i].center.y,2),0.5);
            float meanLen = (Bar.size.height + light[i].size.height)/2;
            float lendiff = abs(Bar.size.height - light[i].size.height)/meanLen;
            float yDiff = abs(Bar.center.y - light[i].center.y);
            float yDiff_ratio = yDiff/meanLen;
            float xDiff = abs(Bar.center.x - light[i].center.x);
            float xDiff_ratio = xDiff/meanLen;
            float ratio = dis/ meanLen;
            if(yDiff>20||xDiff>200||xDiff<10){
                continue;
            }


            if (Bar.center.x<light[i].center.x) {
                left_bottom.x = (rect1[0].x + rect1[1].x)/2;
                left_bottom.y = rect1[0].y + abs(rect1[2].y - rect1[0].y)/2 ;
                left_top.x = (rect1[2].x + rect1[3].x)/2 ;
                left_top.y = rect1[2].y - abs(rect1[2].y - rect1[0].y)/2;
                right_bottom.x = (rect2[0].x +rect2[1].x)/2 ;
                right_bottom.y = rect2[0].y + abs(rect2[2].y - rect2[0].y)/2 ;
                right_top.x = (rect2[2].x +rect2[3].x)/2 ;
                right_top.y = rect2[2].y - abs(rect2[2].y - rect2[0].y)/2;
            }
            else{
                left_bottom.x = (rect2[0].x + rect2[1].x)/2;
                left_bottom.y = rect2[0].y + abs(rect2[2].y - rect2[0].y)/2 ;
                left_top.x = (rect2[2].x + rect2[3].x)/2 ;
                left_top.y = rect2[2].y - abs(rect2[2].y - rect2[0].y)/2 ;
                right_bottom.x = (rect1[0].x +rect1[1].x)/2 ;
                right_bottom.y = rect1[0].y + abs(rect2[2].y - rect1[0].y)/2 ;
                right_top.x = (rect1[2].x +rect1[3].x)/2 ;
                right_top.y = rect1[2].y - abs(rect1[2].y - rect1[0].y)/2 ;
            }
            cv::Point2f lights_vertices[4]= {
                    left_bottom,
                    left_top,
                    right_top,
                    right_bottom,
            };

//            line(pre,left_bottom,left_top,Scalar(0,0,255),2);
//            line(pre,left_top,right_top,Scalar(0,0,255),2);
//            line(pre, right_top,right_bottom,Scalar(0,0,255),2);
//            line(pre,right_bottom,left_bottom,Scalar(0,0,255),2);
            const int top_light_y = (warp_height - light_length) / 2 - 1;
            const int bottom_light_y = top_light_y + light_length;
            cv::Point2f target_vertices[4] = {
                    cv::Point(0,bottom_light_y),
                    cv::Point(0,top_light_y),
                    cv::Point(warp_width-1,top_light_y),
                    cv::Point(warp_width-1,bottom_light_y),


            };
            auto rotation_matrix = cv::getPerspectiveTransform(lights_vertices, target_vertices);
            cv::warpPerspective(pre, number_image, rotation_matrix, cv::Size(warp_width,warp_height));
            imshow("number_",number_image);
            number_image = number_image(cv::Rect(cv::Point((warp_width - roi_size.width) / 2, 0), roi_size));
            cv::cvtColor(number_image, number_image, cv::COLOR_RGB2GRAY);
            Scalar tempVal = cv::mean( number_image );
            cv::threshold(number_image, number_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
            num = number_image /255.0;


           double gama = 0.1;
           cv::Mat lookUpTable(1, 256, CV_8U);
           uchar* p = lookUpTable.ptr();
           for (int i = 0; i < 256; i++) {
               p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gama) * 255.0);
           }
            cv::LUT(num, lookUpTable, num);
            cv::dnn::blobFromImage(num, blob, 1., cv::Size(28,20));
            cv::dnn::Net net_ = cv::dnn::readNetFromONNX(model_path);
            net_.setInput(blob);
            cv::Mat outputs = net_.forward();
            float max_prob = *std::max_element(outputs.begin<float>(), outputs.end<float>());
            cv::exp(outputs - max_prob, softmax_prob);
            float sum = static_cast<float>(cv::sum(softmax_prob)[0]);
            softmax_prob /= sum;
            double confidence;
            cv::Point class_id_point;
            minMaxLoc(softmax_prob.reshape(1, 1), nullptr, &confidence, nullptr, &class_id_point);
            int label_id = class_id_point.x;
            armorClass.label_id = numClasses[label_id];
            armorClass.confidence = confidence;
            if(numClasses[label_id] =="1" || Bar.size.width/Bar.size.height >3.75){
                armorClass.armor_type = "BIG";
            }
            else if(numClasses[label_id] == "Outpost" || numClasses[label_id] == "2"){
                armorClass.armor_type = "SMALL";
            }
            else{
                armorClass.armor_type = "SMALL";
            }
            if(confidence > 0 and numClasses[label_id] =="1" ){
                armorClass.left_top = left_top;
                armorClass.left_bottom = left_bottom;
                armorClass.right_top = right_top;
                armorClass.right_bottom = right_bottom;
                armorClass.rect_center = (left_bottom+left_top+right_bottom+right_top)/4;
                armorPoint.push_back(armorClass);
                string num = armorClass.label_id+":"+to_string(armorClass.confidence);
                cv::putText(pre, num, Point(50,50),cv::FONT_HERSHEY_SIMPLEX, 1,cv::Scalar(0,0,255), 2);
                list ++;
                line(pre, lights_vertices[0], lights_vertices[1], Scalar(0,  255,0), 2);
                line(pre, lights_vertices[1], lights_vertices[2], Scalar(0,  255,0), 2);
                line(pre, lights_vertices[2], lights_vertices[3], Scalar(0,  255,0), 2);
                line(pre, lights_vertices[3], lights_vertices[0], Scalar(0,  255,0), 2);
            }
            else{
                list = 0;
            }

        }
    }


}
