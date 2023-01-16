#pragma once
#include<iostream>
#ifndef UTILS
#include<opencv2/opencv.hpp>
// #include<Eigen/Dense>
#endif
// cv::Mat framePose = cv::Mat::eye(4, 4, CV_64F);
// cv::Mat trajectoryImage = cv::Mat::zeros(600, 1200, CV_8UC3);
namespace SVO{
    static cv::Mat  framePose = cv::Mat::eye(4, 4, CV_64F);
    static cv::Mat  trajectoryImage = cv::Mat::zeros(600, 1200, CV_8UC3);
    
    class Estimate{
        private:  
        cv::Mat intrinsic_matrix;
        cv::Mat prvevious3DPoints;
        std::vector<cv::Point2f> currentLeftPoints; 
        double inlier_rate_=0.0;    
        float reprojectionError = 0.0;
        float confidence = 0.0;             
        int numOfTrackedFeatures=0;
        int iterationsCount = 0; 
        int flags = 0;
        int displayScale=0;
        int xPadding=0;
        int yPadding=0;
        bool initialPosition=true;
        bool useExtrinsicGuess = true;
        bool isRotationMatrix(cv::Mat &R){
            cv::Mat Rt;
            transpose(R, Rt);
            cv::Mat shouldBeIdentity = Rt * R;
            cv::Mat I = cv::Mat::eye(3, 3, shouldBeIdentity.type());
            return norm(I, shouldBeIdentity) < 1e-6;
        }
        cv::Vec3f rotationMatrixToEulerAngles(cv::Mat &R){
            assert(isRotationMatrix(R));
            float sy = sqrt(R.at<double>(0, 0) * R.at<double>(0, 0) + R.at<double>(1, 0) * R.at<double>(1, 0));
            bool singular = sy < 1e-6;
            float x, y, z;
            if (!singular){
                x = atan2(R.at<double>(2, 1), R.at<double>(2, 2));
                y = atan2(-R.at<double>(2, 0), sy);
                z = atan2(R.at<double>(1, 0), R.at<double>(0, 0));
            }
            else{
                x = atan2(-R.at<double>(1, 2), R.at<double>(1, 1));
                y = atan2(-R.at<double>(2, 0), sy);
                z = 0;
            }
            return cv::Vec3f(x, y, z);
        }

        public:
        Estimate(){
            inlier_rate_=0.01;
            iterationsCount = 500;    // number of Ransac iterations.
            reprojectionError = 0.5; // maximum allowed distance to consider it an inlier.
            confidence = 0.99;      // RANSAC successful confidence.
            useExtrinsicGuess = true;
            flags = cv::SOLVEPNP_ITERATIVE;
            initialPosition=true;
            displayScale=1;
            xPadding=400;
            yPadding=200;
        }
        void setInrinsicMatrix(cv::Mat &inputArray){
            intrinsic_matrix=inputArray;
        }
        void setNumberOfTrackedFeatures(int inputNumber){
            numOfTrackedFeatures=inputNumber;
        }
        void set3Dpoints(cv::Mat &inputArray){
            prvevious3DPoints=inputArray;
        }
        void setCurrentTrackedPoints(std::vector<cv::Point2f> &inputArray){
            currentLeftPoints=inputArray;
        }
        // bool stereoPNPtrack();
        bool stereoPNPtrack(){
        cv::Mat rotation = cv::Mat::eye(3, 3, CV_64F);
        cv::Mat translation = cv::Mat::zeros(3, 1, CV_64F);
        // cv::Mat delta_translation = cv::Mat::zeros(3, 1, CV_64F);
        cv::Mat distCoeffs = cv::Mat::zeros(4, 1, CV_64FC1);
        cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64FC1);
        cv::Mat inliers;
        

        cv::solvePnPRansac(prvevious3DPoints, currentLeftPoints, intrinsic_matrix, distCoeffs, rvec, translation,
                        useExtrinsicGuess, iterationsCount, reprojectionError, confidence,
                        inliers, flags);
        cv::Rodrigues(rvec, rotation);

        cv::Vec3f rotationInEuler = rotationMatrixToEulerAngles(rotation);
        if (abs(rotationInEuler[1]) < 0.1 && abs(rotationInEuler[0]) < 0.1 && abs(rotationInEuler[2]) < 0.1){
            double poseNormalize = (std::pow(translation.at<double>(0), 2) + std::pow(translation.at<double>(1), 2) + std::pow(translation.at<double>(2), 2));
            if (poseNormalize < 100 && poseNormalize > 0.0005 * 0.0005){
            cv::Mat rigidBodyTransformation;
            cv::Mat addup = (cv::Mat_<double>(1, 4) << 0, 0, 0, 1);
            cv::hconcat(rotation, translation, rigidBodyTransformation);
            cv::vconcat(rigidBodyTransformation, addup, rigidBodyTransformation);
            rigidBodyTransformation = rigidBodyTransformation.inv();
            framePose = framePose * rigidBodyTransformation;
            }
            else
                return false;
        }
        else
            return false;

        if ((double)inliers.size[0] / (double)currentLeftPoints.size() < inlier_rate_){
        return false;
        }

        cv::Mat xyz = framePose.col(3).clone();
        double Px = xyz.at<double>(0);
        double Pz = xyz.at<double>(2);
        // double Py__ = xyz.at<double>(1);

        int x = (int)(Px * displayScale) + xPadding;
        int y = (int)(Pz * displayScale) + yPadding;
        circle(trajectoryImage, cv::Point(x, y), 1, CV_RGB(0, 0, 255), 1);
        cv::imshow("Trajectory", trajectoryImage);
        if(cv::waitKey(1)==27){
            cv::destroyAllWindows();
            exit(1);
        }

        return true;
    }

    };
}