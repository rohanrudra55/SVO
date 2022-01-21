// #include<iostream>
// #include<opencv2/opencv.hpp>


// struct extrinct{
//     cv::Mat rotational_matrix_1;
//     cv::Mat rotational_matrix_2;
//     cv::Mat transversal_matrix;
// };
// struct instirnct{
//     cv::Mat camera_matrix;
//     double focal_length;
//     double c_x;
//     double c_y;
// };
// struct stereo{
//     cv::Mat left;
//     cv::Mat right;
// };
// struct features{
//     cv::Mat descriptor;
//     std::vector<cv::KeyPoint> keypoints;
// };

// void detect_features(cv::Mat,features);
// void track_features(features);
// void calculate_extrinct_parameters(extrinct,features);
// void read_parameters(instirnct,extrinct,char);
// void draw_feature_points(stereo,features,features);


// std::ostream& operator<<(std::ostream& out,stereo& camera){
//     cv::namedWindow("Left Image",cv::WINDOW_AUTOSIZE);
//     cv::imshow("Left Image",camera.left);
//     cv::namedWindow("Right Image",cv::WINDOW_AUTOSIZE);
//     cv::imshow("Right Image",camera.right);
//     // cv::waitKey(50);
//     out<<"\r";
//     return out;
// }