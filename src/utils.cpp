#include"utils.h"

namespace SVO{
    bool ReadFrame::readKITTI(cv::Mat &imagel,cv::Mat &imager,int number){
        std::string finalPathl,finalPathr;
        // std::cout<<number;
        char p[7];
        sprintf(p,"%06d",number);
        finalPathl=path+"image_0/"+p+".png";
        finalPathr=path+"image_1/"+p+".png";
        cv::Mat left=cv::imread(finalPathl,0);
        cv::Mat right=cv::imread(finalPathr,0);
        imagel=left;
        imager=right;
        // cv::resize(left, imagel, cv::Size(), 0.5, 0.5,cv::INTER_NEAREST);
        // cv::resize(right, imager, cv::Size(), 0.5, 0.5,cv::INTER_NEAREST);
        return !(imagel.empty());
    }
}