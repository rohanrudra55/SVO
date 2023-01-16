#pragma once
#include<iostream>
#ifndef UTILS
    #include<opencv2/opencv.hpp>
    #include<opencv2/ximgproc/disparity_filter.hpp>
#endif

namespace SVO{
    class Stereo{
        private:
        cv::Mat projMatL=cv::Mat::zeros(3, 4, CV_64F);
        cv::Mat projMatR=cv::Mat::zeros(3, 4, CV_64F);
        public:
        Stereo(){
            projMatL=(cv::Mat_<double>(3,4)<<718.856, 0, 607.193, 0,0, 718.856, 185.216, 0,0, 0, 1, 0);
            projMatR=(cv::Mat_<double>(3,4)<<718.856, 0, 607.193, -386.02567,0, 718.856, 185.216, 0,0, 0, 1, 0);
        }
        void setLeftProjectionMatrix(cv::Mat inputArray){
            projMatL=inputArray;
        }
        void setRightProjectionMatrix(cv::Mat inputArray){
            projMatR=inputArray;
        }
        cv::Mat triangulateFeatures(std::vector<cv::Point2f>&,std::vector<cv::Point2f>&);
        void getIntrinsicMatrix(cv::Mat &outputArray){
            outputArray=(cv::Mat_<double>(3, 3) << projMatL.at<double>(0, 0), projMatL.at<double>(0, 1), projMatL.at<double>(0, 2), projMatL.at<double>(1, 0), projMatL.at<double>(1, 1), projMatL.at<double>(1, 2),
                                projMatL.at<double>(2, 0), projMatL.at<double>(2, 1), projMatL.at<double>(2, 2));
        }

    };
}
namespace SV{
    class Stereo{
        private:
        cv::Mat disparity;
        cv::Mat reprojectionMatrix;
        bool useReprojectionMatrix=false;
        cv::Mat projMatL,projMatR;
        void setLeftProjectionMatrix(cv::Mat inputArray){
            projMatL=inputArray;
        }
        void setRightProjectionMatrix(cv::Mat inputArray){
            projMatR=inputArray;
        }
        void setReprojectionMatrix(cv::Mat input){
            reprojectionMatrix=input;
            useReprojectionMatrix=true;
        }
        double focalLength=0;
        double baseline=0;
        double cx=0;
        double cy=0;
        double fx=0;
        double fy=0;
        public:
        Stereo(){
            
        }
        cv::Mat getDisparity(){
            return disparity;
        }
        void disparityCalculate(cv::Mat&,cv::Mat&);
        void depthCalculate(cv::Mat&);
    };
}
