#pragma once
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<opencv2/opencv.hpp>
#define UTILS
#define CSV true
namespace SVO{
    class ReadFrame{
        private:
        std::string path;
        public:
        void setPath(std::string dir){
                path=dir;
            }
        bool readKITTI(cv::Mat&,cv::Mat&,int);
    };
}

