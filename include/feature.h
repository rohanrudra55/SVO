#pragma once
#include <iostream>
#include <vector>
#ifndef UTILS
#include<opencv2/opencv.hpp>
// #include <opencv2/features2d.hpp>
// #include <opencv2/core.hpp>
// #include <opencv2/highgui.hpp>
// #include <opencv2/imgproc.hpp>
// #include <opencv2/videoio.hpp>
// #include <opencv2/video.hpp>
#endif
#define THRESHOLD 10
class Feature{
	public:
	static std::vector<cv::KeyPoint> detected_features;
	static std::vector<cv::Point2f> tracked_features;
	static std::vector<cv::Point2f> tracked_features_prv;
	static std::vector<cv::Point2f> detected_points;
	static std::vector<uchar> status;
	static cv::Mat error;
	static cv::Mat consistencyMat;
	static std::vector<cv::KeyPoint> getKeypoint(){
		return detected_features;
	}
	static void drawPoints(cv::Mat&);
	static bool checkDetectedFeatures(){
		if(tracked_features.size()<20)
		return false;
		return true;
	}
	static void detectFeatures(cv::Mat&);
	static void validateFeatures(cv::Mat&,cv::Mat&);
	static void trackFeatures(cv::Mat&,cv::Mat&);
};