#include "../include/system.h"

namespace SVO{
    int System::imageCount=0;
    void System::runSVO(){
        int count;
        std::cout<<BLUE<<"Stereo Visual Odometry\n"<<RESET<<std::endl;
        while(nextStep()){
            count++;
        }
        std::cout<<BLUE<<"Processed data: "<<RESET<<count<<std::endl;
    }
    bool System::nextStep(){
        cv::Mat leftimage,rightimage;
        std::vector<cv::Point2f> matched_t2_left, matched_t1_left, matched_t2_right, matched_t1_right;
        cv::Mat points3D;
        cv::Mat intrinsicMat;
        bool status1=true;
        readImage.setPath(dataPath);
         stereoTriangulate.getIntrinsicMatrix(intrinsicMat);
        if (readImage.readKITTI(leftimage, rightimage, imageCount))
        {
            trackFeatures.setFrame(leftimage,rightimage);
            if(initialStep){
                trackFeatures.detectFeatures();
                initialStep=false;
            }

            else{
                trackFeatures.detectFeatures();
                trackFeatures.getLastPoints(matched_t1_left);
                int tracked=trackFeatures.trackMultiImageFeatures(matched_t2_left, matched_t2_right, matched_t1_left, matched_t1_right);
                // TO SHOW NUMBER OF TRACKED POINTS
                // std::cout<<"Tracked:"<<tracked<<std::endl;
                if(showTracking)
                    trackFeatures.displayTracking(leftimage,matched_t2_left,matched_t1_left);
                points3D=stereoTriangulate.triangulateFeatures(matched_t1_left,matched_t1_right);
                poseEstimator.set3Dpoints(points3D);
                poseEstimator.setCurrentTrackedPoints(matched_t2_left);
                poseEstimator.setInrinsicMatrix(intrinsicMat);
                status1= poseEstimator.stereoPNPtrack();
            }
            trackFeatures.alterFrame();
            imageCount++;
        }
    else
        return false;

    return true;
    }
}