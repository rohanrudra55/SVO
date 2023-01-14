#pragma once
#include<iostream>
#ifndef UTILS
    #include<opencv2/opencv.hpp>
    #include<opencv2/ximgproc/disparity_filter.hpp>
#endif

class Stereo{
    public:
    static cv::Mat disparity;
    static cv::Mat reprojection_matrix;
    static double focal_length;
    static double baseline;
    static std::string channel;
    static void setChannel(std::string input){
        channel=input;
    }
    static void setChannel(std::string input,cv::Mat inputMat){
        channel=input;
        reprojection_matrix=inputMat;
    }
    static void setFocalLength(double input){
        focal_length=input;
    }
    static void setBaseline(double input){
        baseline=input;
    }
    static void setReprojectionMatrix(cv::Mat input){
        reprojection_matrix=input;
    }
    static cv::Mat getDisparity(){
        return disparity;
    }
    static void disparityCalculate(cv::Mat&,cv::Mat&);
    static void depthCalculate(cv::Mat&);
};