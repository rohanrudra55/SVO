#include "../include/utils.h"
#include "../include/stereo.h"
#include "../include/feature.h"
#define START 0
#define END 90
#define FOCAL 781
#define BASELINE 0.4
int main(){
    cv::Mat leftimage,leftimage_t,rightimage,rightimage_t,disp,disp_t,depth,depth_t;
    // Utils left;
    // Utils right;
    Utils::setPath("../data/mini/");
    // Utils::setPath("../data/Kitti_small/");
    Utils::readRectifyData();
    cv::Mat rep=Utils::getReprojectMat();
    Stereo::setBaseline(0.4);
    Stereo::setChannel("Multi");
    Stereo::setFocalLength(2123.5);
    Stereo::setReprojectionMatrix(rep);
    for(int i=START;i<END;i++){
        // if(Utils::readKITTI(leftimage,rightimage,i) && Utils::readKITTI(leftimage_t,rightimage_t,i+1)){
        if(Utils::readERoC(leftimage,rightimage) && Utils::readERoC(leftimage_t,rightimage_t)){
        Utils::display(leftimage,"Left");
        // std::cout<<i<<std::endl;
        // Utils::rectifyImage(leftimage,rightimage);
        // Utils::rectifyImage(leftimage,rightimage);
        Stereo::disparityCalculate(leftimage,rightimage);
        Stereo::depthCalculate(depth);
        // Stereo::disparityCalculate(leftimage_t,rightimage_t);
        // Stereo::depthCalculate(depth_t);
        // cv::imwrite("data.png",depth);
        cv::Mat dispL=Stereo::getDisparity();
        Utils::display(depth,"Depth");
        // std::cout<<depth;
        Feature::detectFeatures(leftimage);
        // Feature::detectFeatures(leftimage_t);
        // Feature::drawPoints(leftimage);
        Feature::trackFeatures(leftimage,leftimage_t);
        Feature::validateFeatures(depth,depth_t);
        // Feature::
        // Stereo::disparityCalculate(leftimage_t,rightimage_t);
        // cv::Mat dispR=Stereo::getDisparity();
        // Utils::display(dispR,"Right");
        // depth_calculate(disp,FOCAL,BASELINE,reqM,"single",depth);
        // Utils::display(depth);
        }
    }
}



// int main(){

//     // double focal_length = 718.8560;
//     // Point2d Cx_Cy(607.1928, 185.2157);
//     cv::Mat E;

//     std::string left_folder_path = "/home/maaitrayo/Autonomous Vehicle/data_odometry_gray/dataset/sequences/00/image_0/*.png";
//     std::string right_folder_path = "/home/maaitrayo/Autonomous Vehicle/data_odometry_gray/dataset/sequences/00/image_1/*.png";
//     std::vector<cv::String> left_image_arr, right_image_arr;
//     cv::glob(left_folder_path, left_image_arr);
//     cv::glob(right_folder_path, right_image_arr);
//     for (size_t frame_num = 0; frame_num < left_image_arr.size();frame_num++){
         
//         cv::Mat image_left = cv::imread(left_image_arr[frame_num]);
//         cv::Mat image_right = cv::imread(right_image_arr[frame_num]);

//         //Detecting features
//         detect_features(image_left, left_pts_prev, image_right, right_pts_prev);

//         //Tracking the detected features
//         track_features(image_left, image_left_curr, left_pts_prev, left_pts_curr, status_left,
//                         image_right, image_right_curr, right_pts_prev, right_pts_curr, status_right);

//         E = findEssentialMat(image_left_curr, left_pts_prev, focal_length, Cx_Cy,RANSAC, 0.999, 1.0, mask);

//         // Calculating disparity
//         disparity_calculate( image_left, image_right);
        
//         //Calculating depth
//         depth_calculate(final_disparity, data, baseline, depth_map)

//         //cv::imshow("Image left" , image_left);
//         //cv::imshow("Image right" , image_right);

//         cv::waitKey(30);


//     	}
//     	cv::destroyAllWindows();

// }