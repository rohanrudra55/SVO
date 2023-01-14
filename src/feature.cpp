#include "../include/feature.h"
std::vector<cv::KeyPoint> Feature::detected_features;
std::vector<cv::Point2f> Feature::tracked_features,Feature::tracked_features_prv,Feature::detected_points;
cv::Mat Feature::error,Feature::consistencyMat;
std::vector<uchar> Feature::status;
void Feature::detectFeatures(cv::Mat &image){
    //ORB DETECTOR
    // cv::Ptr<cv::ORB>ditector=cv::ORB::create();
    // ditector->setMaxFeatures(1000);
    // ditector->setScaleFactor(1.2f);
    // ditector->setNLevels(8);
    // ditector->setEdgeThreshold(31);
    // ditector->setFirstLevel(0);
    // ditector->setWTA_K(2);
    // ditector->setScoreType(cv::ORB::HARRIS_SCORE);
    // ditector->setPatchSize(31);
    // ditector->setFastThreshold(20);
    // ditector->detect(image,detected_features);

    //FAST DETECTOR
    // std::vector<cv::KeyPoint> keypoints;
    cv::Ptr<cv::FastFeatureDetector> detector=cv:: FastFeatureDetector::create();
    detector->setThreshold(40);
    detector->descriptorSize();
    detector->detect(image,detected_features);
    // cv::KeyPoint::convert(keypoints, points);
    cv::KeyPoint::convert(detected_features,detected_points);
    tracked_features=detected_points;       
}

void Feature::trackFeatures(cv::Mat &image,cv::Mat &image_t){
    // cv::Mat imagePyramid,imagePyramid_t;
    cv::Size winSize(10,10);
    // CREATING PYRAMID OF IMAGES
    // cv::buildOpticalFlowPyramid(image,imagePyramid,winSize,8,false,4,0,true);
    // cv::buildOpticalFlowPyramid(image_t,imagePyramid_t,winSize,8,false,4,0,true);
    tracked_features_prv=tracked_features;
    cv::calcOpticalFlowPyrLK(image,image_t,tracked_features_prv,tracked_features,status,error);
    // std::cout<<tracked_feature<<std::endl;
    //Filtering out valid points
    //eleTo --> element to
    auto eleTo_1 = tracked_features_prv.begin();
    auto eleTo_2 = tracked_features.begin();
    for(size_t i = 0; i < status.size(); i++){
        //cout << status[i] ;
        if(status[i]){
            eleTo_1++;
            eleTo_2++;
        }
        else{
            tracked_features_prv.erase(eleTo_1);
            tracked_features.erase(eleTo_2);
        }
    }
}
void Feature::validateFeatures(cv::Mat &depth,cv::Mat &depth_t){
    // DIFFERENCE BETWEEEN WORLD COORDINATES SHOULD MATCH FEATURES
    for(int i=0;i<depth.rows;i++){
        for(int j=0;j<depth.cols;j++){
            // if(depth.at(tracked_features_prv.at(0)))           
            std::cout<<"Depth value:"<<depth.at<cv::Vec3f>(tracked_features.at(0));
            exit(1);
        }
        // exit(1);
    }
}
void Feature::drawPoints(cv::Mat &image){
    cv::Mat result;
    cv::drawKeypoints(image,detected_features,result,cv::Scalar::all(-1));
    cv::imshow("Features",result);
    // if(cv::waitKey(0)==27)
    //     cv::destroyAllWindows();
}
// void co

// }
// int main(){
//     cv::Mat image=cv::imread("../data/mini/cam0/data/1403636579763555584.png",0);
//     Feature::detectFeatures(image);
//     std::vector<cv::Point2f> keys;
//     cv::KeyPoint::convert(Feature::getKeypoint(),keys);
//     std::cout<<keys[0].x;
//     Feature::drawPoints(image);

// }
 