//
// Created by anne on 10/26/23.
//
#include "opencv2/opencv.hpp"
#include "iostream"
#include <chrono>
#include <thread>
#include "main.hpp"
#include "Detect/detect.hpp"
#include "Pnp/pnp.hpp"
#include "hik_camera/include/HikCam.hpp"
#include "Serial/serial.hpp"


    int main() {
        detect detector;
        pnp pnpSolve;
        serial serial(detector,pnpSolve);
        HikCam hikCam;

        std::thread senderThread(&serial::send, &serial);
        std::thread receiverThread(&serial::receive, &serial);

        senderThread.detach();
        receiverThread.detach();




        std::string videoPath = "../38324.avi";  // 视频文件路径
        std::string modelPath = "../model/fc.onnx";  // 模型文件路径

        detector.readVideo(videoPath);  // 读取视频

//        while (true) {
//            cv::Mat frame;
//            detector.video >> frame;  // 从视频中读取一帧图像
//
//            if (frame.empty()) {
//                // 视频结束或读取失败，退出循环
//                break;
//            }

        Mat video;

        if(hikCam.StartDevice(0) != 0) return false;
        hikCam.SetResolution(1289,1024);
        hikCam.SetPixelFormat(173011514);
        hikCam.SetExposureTime(5000);
        hikCam.SetGAIN(10.0);
        hikCam.SetFrameRate(80);
        hikCam.SetStreamOn();
        string  CamFPS = to_string(hikCam.GetFrameRate());
        cout<<"CamFPS"+ CamFPS<<endl;
        while(true)
        {
            hikCam.GetMat(video);





            detector.img = video.clone();
            detector.imgProcess();

            detector.pre = video.clone();
            detector.findLightBar();
            detector.number_image = video.clone();
            detector.numClassify(modelPath);

            for (auto &armor : detector.armorPoint) {
                    pnpSolve.pnpSolve(armor);
                    pnpSolve.offSet(armor);

            }





//             在图像上显示或执行其他操作
           cv::namedWindow("num", cv::WINDOW_NORMAL);
           cv::resizeWindow("num", 800, 600); // 设置 "Frame" 窗口的大小为 800x600

            cv::namedWindow("pre", cv::WINDOW_NORMAL);
            cv::resizeWindow("pre", 800, 600);
           cv::imshow("Frame", detector.number_image);
            cv::imshow("pre",detector.pre);
            cv::waitKey(10);  // 显示图像并等待按键


        }

        cv::destroyAllWindows();  // 关闭显示窗口

        return 0;
    }

