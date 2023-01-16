#include"utils.h"
#define FILENAME 11
namespace SVO{
    bool ReadFrame::readKITTI(cv::Mat &imagel,cv::Mat &imager,int number){
        std::string finalPathl,finalPathr;

        char p[FILENAME];
        sprintf(p, "%010d", number);
        finalPathl = path + "/image_00/data/" + p + ".png";
        finalPathr = path + "/image_01/data/" + p + ".png";
        cv::Mat left=cv::imread(finalPathl,0);
        cv::Mat right=cv::imread(finalPathr,0);
        imagel=left;
        imager = right;
        // TO RESIZE THE IMAGE
        // cv::resize(left, imagel, cv::Size(), 0.5, 0.5,cv::INTER_NEAREST);
        // cv::resize(right, imager, cv::Size(), 0.5, 0.5,cv::INTER_NEAREST);
        return !(imagel.empty());
    }
}