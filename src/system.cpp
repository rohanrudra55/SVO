#include "../include/system.h"

namespace SVO{
    int System::imageCount=0;
    void System::runSVO(){
        int count;
        std::cout<<"Welcome to Tivra Ai\nStereo Visual Odometry"<<std::endl;
        while(nextStep()){
            count++;
        }
        std::cout<<"Processed data: "<<count<<std::endl;
    }
    bool System::nextStep(){
        cv::Mat leftimage,rightimage;
        std::vector<cv::Point2f> matched_t2_left, matched_t1_left, matched_t2_right, matched_t1_right;
        cv::Mat points3D;
        cv::Mat intrinsicMat;
        bool status1=true;
        readImage.setPath("/Users/alpha/Downloads/2011_09_26/2011_09_26_drive_0001_sync");
        // readImage.setPath(dataPath);
        // stereoTriangulate.setLeftProjectionMatrix((cv::Mat_<double>(3,4)<<718.856, 0, 607.193, 0,0, 718.856, 185.216, 0,0, 0, 1, 0));
        // stereoTriangulate.setRightProjectionMatrix((cv::Mat_<double>(3,4)<<718.856, 0, 607.193, -386.02567,0, 718.856, 185.216, 0,0, 0, 1, 0));
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
} //Namespace