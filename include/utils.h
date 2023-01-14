#pragma once
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<opencv2/opencv.hpp>
#define UTILS
#define CSV true
class Utils{
    // private:
    //     static void convert(){
    //         for (int row = 0; row < flow.rows; row++){
    //             for (int col = 0; col < flow.cols; col++){
    //                 Point2f f = flow.at<Point2f>(row, col);
    //                 mapx.at<float>(row, col) = col + f.x;
    //                 mapy.at<float>(row, col) = row + f.y;
    //             }
    //         }
    //     }

    public:
        static cv::Mat StereomapL_x;
        static cv::Mat StereomapL_y;
        static cv::Mat StereomapR_x;
        static cv::Mat StereomapR_y;
        static cv::Mat reprojection_matrix;
        static std::string path;
        static std::string  start;
        // static int limit;
        static bool foundCSV;
        static bool foundXML;
        static std::fstream fin;
        cv::Mat image;
        static void setPath(std::string dir){
            path=dir;
        }
        void setStart(std::string name){
            start=name;
        }
        static cv::Mat getReprojectMat(){
            return reprojection_matrix;
        }
        // void setLimit(int end){
        //     limit=end;
        // }
        // static void open_file(){
        //     fin.open((path+"data.csv"),std::ios::in);
        //     if ( !fin ) {
        //          std::cout << "File not found";
        //          exit(1);
        //     }
        // }
        static void display(cv::Mat&,std::string);
        static bool readERoC(cv::Mat&,cv::Mat&);
        static bool readERoC(cv::Mat&);
        static bool readKITTI(cv::Mat&,int);
        static bool readKITTI(cv::Mat&,cv::Mat&,int);
        static void readRectifyData();
        static void rectifyImage(cv::Mat&,cv::Mat&);
};

