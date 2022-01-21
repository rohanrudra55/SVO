// #include "include/rigid.h"


// namespace SVO{
//     bool Estimate::stereoPNPtrack(){
//         cv::Mat rotation = cv::Mat::eye(3, 3, CV_64F);
//         cv::Mat translation = cv::Mat::zeros(3, 1, CV_64F);
//         cv::Mat delta_translation = cv::Mat::zeros(3, 1, CV_64F);
//         cv::Mat distCoeffs = cv::Mat::zeros(4, 1, CV_64FC1);
//         cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64FC1);
//         cv::Mat inliers;

//         cv::solvePnPRansac(points3D_t1, matched_t2_left, intrinsic_matrix, distCoeffs, rvec, translation,
//                         useExtrinsicGuess, iterationsCount, reprojectionError, confidence,
//                         inliers, flags);
//         cv::Rodrigues(rvec, rotation);

//         cv::Mat rigid_body_transformation;
//         cv::Mat addup = (cv::Mat_<double>(1, 4) << 0, 0, 0, 1);
//         cv::hconcat(rotation, translation, rigid_body_transformation);
//         cv::vconcat(rigid_body_transformation, addup, rigid_body_transformation);
//         rigid_body_transformation = rigid_body_transformation.inv();
//         frame_pose_ = frame_pose_ * rigid_body_transformation;
        
//         // displayTracking(current_frame_->left_img_, matched_t1_left, matched_t2_left);

//         cv::Mat xyz = frame_pose_.col(3).clone();
//         double Px__ = xyz.at<double>(0);
//         double Pz__ = xyz.at<double>(2);
//         double Py__ = xyz.at<double>(1);

//         int x = (int)(Px__ * 1) + 400;
//         int y = (int)(Pz__ * 1) + 200;
//         circle(trajectory_, cv::Point(x, y), 1, CV_RGB(0, 0, 255), 2);
//         cv::imshow("Trajectory", trajectory_);
//         if(cv::waitKey(1)==27){
//             cv::destroyAllWindows();
//             exit(1);
//         }

//         return true;
//     }
// }