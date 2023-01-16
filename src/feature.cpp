#include "../include/feature.h"
namespace SVO{
void Feature::detectFeatures(){
    if(useORB){
    // ORB DETECTOR
    cv::Ptr<cv::ORB>ditector=cv::ORB::create();
    ditector->setMaxFeatures(1000);
    ditector->setScaleFactor(1.2f);
    ditector->setNLevels(8);
    ditector->setEdgeThreshold(31);
    ditector->setFirstLevel(0);
    ditector->setWTA_K(2);
    ditector->setScoreType(cv::ORB::HARRIS_SCORE);
    ditector->setPatchSize(31);
    ditector->setFastThreshold(20);
    ditector->detect(current.leftImage,current.keypoints);
    }
    else{
    //FAST DETECTOR
        cv::Ptr<cv::FastFeatureDetector> detector=cv:: FastFeatureDetector::create();
        detector->setThreshold(20);
        detector->descriptorSize();
        detector->setNonmaxSuppression(true);
        detector->detect(current.leftImage,current.keypoints);    
    }  
}
void Feature::deleteBadMatchFeatures(std::vector<cv::Point2f> &points0, std::vector<cv::Point2f> &points1,
                                      std::vector<cv::Point2f> &points2, std::vector<cv::Point2f> &points3,
                                      std::vector<cv::Point2f> &points0_return,
                                      std::vector<uchar> &status0, std::vector<uchar> &status1,
                                      std::vector<uchar> &status2, std::vector<uchar> &status3)
{
    //getting rid of points for which the KLT tracking failed or those who have gone outside the frame
    int indexCorrection = 0;
    // int removed=0;
    for (size_t i = 0; i < status3.size(); i++)
    {
        cv::Point2f pt0 = points0.at(i - indexCorrection);
        cv::Point2f pt1 = points1.at(i - indexCorrection);
        cv::Point2f pt2 = points2.at(i - indexCorrection);
        cv::Point2f pt3 = points3.at(i - indexCorrection);
        cv::Point2f pt0_r = points0_return.at(i - indexCorrection);

        bool outsideframe = ((pt3.x < 0) || (pt3.y < 0) ||
                             (pt2.x < 0) || (pt2.y < 0) ||
                             (pt1.x < 0) || (pt1.y < 0) ||
                             (pt0.x < 0) || (pt0.y < 0) ||
                             (pt0_r.x < 0) || (pt0_r.y < 0));
        bool badstatus = ((status2.at(i) == 0) || (status1.at(i) == 0) ||
                          (status0.at(i) == 0) || (status3.at(i) == 0));

        bool NoStereoEpipolarConstrain = ((std::abs(pt0.y - pt1.y) > featureMatchError) ||
                                          (std::abs(pt2.y - pt3.y) > featureMatchError));
        if (outsideframe || badstatus || NoStereoEpipolarConstrain)
        {
            points0.erase(points0.begin() + (i - indexCorrection));
            points1.erase(points1.begin() + (i - indexCorrection));
            points2.erase(points2.begin() + (i - indexCorrection));
            points3.erase(points3.begin() + (i - indexCorrection));
            points0_return.erase(points0_return.begin() + (i - indexCorrection));

            indexCorrection++;
        }
    }
}
int Feature::trackMultiImageFeatures(std::vector<cv::Point2f> &currenrLeftPoints,std::vector<cv::Point2f> &currenrRightPoints,
                                    std::vector<cv::Point2f> &previousLeftPoints,std::vector<cv::Point2f> &previousRightPoints){
    std::vector<cv::Point2f> newPreviousLeftPoints;

    std::vector<uchar> status1, status2, status3, status4;
    cv::Mat error1, error2, error3, error4;
    cv::calcOpticalFlowPyrLK(
        last.leftImage, last.rightImage, previousLeftPoints,
        previousRightPoints, status1, error1, cv::Size(21, 21), 3,
        cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30,
                         0.01),
        0, 0.001);

    cv::calcOpticalFlowPyrLK(
        last.rightImage, current.rightImage, previousRightPoints,
        currenrRightPoints, status2, error2, cv::Size(21, 21), 3,
        cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30,
                         0.01),
        0, 0.001);

    cv::calcOpticalFlowPyrLK(
        current.rightImage, current.leftImage, currenrRightPoints,
        currenrLeftPoints, status3, error3, cv::Size(21, 21), 3,
        cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30,
                         0.01),
        0, 0.001);
    cv::calcOpticalFlowPyrLK(
        current.leftImage, last.leftImage, currenrLeftPoints,
        newPreviousLeftPoints, status4, error4, cv::Size(21, 21), 3,
        cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30,
                         0.01),
        0, 0.001);
    deleteBadMatchFeatures(previousLeftPoints, previousRightPoints, currenrRightPoints, currenrLeftPoints, newPreviousLeftPoints,
                           status1, status2, status3, status4);
    return previousLeftPoints.size();
}
    void Feature::displayTracking(cv::Mat &currentLeftImage,std::vector<cv::Point2f> &previousLeftPoints,std::vector<cv::Point2f> &currentLeftPoints){
        // -----------------------------------------
        // DISPLAY TRACKING FEATURE
        // -----------------------------------------
        int radius = 2;
        cv::Mat visualize;

        cv::cvtColor(currentLeftImage, visualize, cv::COLOR_GRAY2BGR, 3);

        for (size_t i = 0; i < previousLeftPoints.size(); i++)
        {
            cv::circle(visualize, cv::Point(previousLeftPoints[i].x, previousLeftPoints[i].y), radius, CV_RGB(0, 255, 0));
        }

        for (size_t i = 0; i < currentLeftPoints.size(); i++)
        {
            cv::circle(visualize, cv::Point(currentLeftPoints[i].x, currentLeftPoints[i].y), radius, CV_RGB(255, 0, 0));
        }

        for (size_t i = 0; i < currentLeftPoints.size(); i++)
        {
            cv::line(visualize, previousLeftPoints[i], currentLeftPoints[i], CV_RGB(0, 255, 0));
        }

        cv::imshow("Real Time Tracking", visualize);
        if(cv::waitKey(1)==27){
            cv::destroyAllWindows();
            exit(1);
        }
    }
}
 