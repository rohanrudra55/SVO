#pragma once
#include <iostream>
#include <vector>
#ifndef UTILS
#include<opencv2/opencv.hpp>
#endif

namespace SVO{
	class Feature{
		private:
		struct Frame{
			cv::Mat leftImage;
			cv::Mat rightImage;
			std::vector<cv::KeyPoint> keypoints;
		};
		Frame last,current;
		bool useORB=false;
		int featureMatchError=0;
		public:
		Feature(){
			featureMatchError=3;
		}
		void setFrame(cv::Mat &leftInput,cv::Mat &rightInput){
			current.leftImage=leftInput;
			current.rightImage=rightInput;
		}
		void alterFrame(){
			last=current;
		}
		void setORB(bool input){
			useORB=true;
		}
		void detectFeatures();
		void deleteBadMatchFeatures(std::vector<cv::Point2f> &, std::vector<cv::Point2f> &,
                                      std::vector<cv::Point2f> &, std::vector<cv::Point2f> &,
									  std::vector<cv::Point2f> &,std::vector<uchar> &, std::vector<uchar> &,
									  std::vector<uchar> &, std::vector<uchar> &);
		int  trackMultiImageFeatures(std::vector<cv::Point2f> &,std::vector<cv::Point2f> &,std::vector<cv::Point2f> &,std::vector<cv::Point2f>&);
		void displayTracking(cv::Mat &,std::vector<cv::Point2f> &,
									std::vector<cv::Point2f> &);
		void getLastPoints(std::vector<cv::Point2f>&matchedPoints){
			for (auto &kp : last.keypoints){
        		matchedPoints.push_back(kp.pt);
   			 }
		}

	};
}