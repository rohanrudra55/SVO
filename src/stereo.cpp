
#include"stereo.h"
namespace SV{

#ifdef ELAS
    void Stereo::disparityCalculate(cv::Mat &image_left, cv::Mat &image_right)
    {
        cv::Mat l_image, r_image, l_disparity, r_disparity;

        cv::Mat filtered_disparity;
        cv::Ptr<cv::ximgproc::DisparityWLSFilter> wls_filter;
        cv::Mat conf_map;
        conf_map = cv::Mat(image_left.rows, image_right.cols, CV_8U);
        conf_map = cv::Scalar(255);
        cv::Rect ROI;

        max_disp /= 2;
        if (max_disp % 16 != 0)
        {
            max_disp += 16 - (max_disp % 16);
        }
        vis_mult = 3.0;

        cv::resize(image_left, l_image, cv::Size(), 0.5, 0.5);
        cv::resize(image_right, r_image, cv::Size(), 0.5, 0.5);
        image_left = l_image;
        image_right = r_image;
        wls_filter = cv::ximgproc::createDisparityWLSFilter(sgbm);
        cv::Ptr<cv::StereoMatcher> right_matcher = cv::ximgproc::createRightMatcher(sgbm);
        right_matcher->compute(r_image, l_image, r_disparity);
        wls_filter->setLambda(lambda);
        wls_filter->setSigmaColor(sigma);
        wls_filter->filter(l_disparity, image_left, filtered_disparity, r_disparity);
        conf_map = wls_filter->getConfidenceMap();
        ROI = wls_filter->getROI();
        resize(l_disparity, l_disparity, cv::Size(), 2.0, 2.0);
        l_disparity = l_disparity * 2.0;
        ROI = cv::Rect(ROI.x * 2, ROI.y * 2, ROI.width * 2, ROI.height * 2);

        cv::ximgproc::getDisparityVis(filtered_disparity, disparity, vis_mult);
    }
#else
    void Stereo::disparityCalculate(cv::Mat &image_left, cv::Mat &image_right)
    {

        int sad_window = 3;
        int num_diaparities = sad_window * 16;
        int block_size = 11;
        int max_disp = 160;
        double lambda = 8000.0;
        double sigma = 3.5;
        double vis_mult;

        cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create();
        sgbm->setBlockSize(15);
        sgbm->setDisp12MaxDiff(16000);
        sgbm->setMinDisparity(0);
        sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);
        sgbm->setNumDisparities(4 * 16);
        sgbm->setPreFilterCap(0);
        sgbm->setP1(8 * 3 * sad_window * sad_window);
        sgbm->setP2(32 * 3 * sad_window * sad_window);
        sgbm->setSpeckleRange(0);
        sgbm->setSpeckleWindowSize(0);
        sgbm->setUniquenessRatio(0);

        cv::Mat disparity_i;
        sgbm->compute(image_left, image_right, disparity_i);
        disparity_i.convertTo(disparity, CV_32F, 1.0 / 16.0f);
    }
    void Stereo::depthCalculate(cv::Mat &depthMap)
    {
        depthMap = cv::Mat::zeros(disparity.size(), disparity.type());
        if (useReprojectionMatrix)
            cv::reprojectImageTo3D(disparity, depthMap, reprojectionMatrix, true);
        else
        {
            for (int _row = 0; _row < (int)disparity.rows; _row++)
            {
                for (int _col = 0; _col < (int)disparity.cols; _col++)
                {
                    double pixel = disparity.at<double>(_row, _col);
                    double depth = 0.1;
                    if (pixel > 0 || pixel < 96)
                        depth = (focalLength * baseline) / (pixel + 0.0001);
                    depthMap.push_back(depth);
            }
        }
        }
    }
#endif
}
namespace SVO{
    cv::Mat Stereo::triangulateFeatures(std::vector<cv::Point2f>&leftFeatures,std::vector<cv::Point2f>& rightFeatures){
        cv::Mat points4d,points3d;
        cv::triangulatePoints(projMatL,projMatR,leftFeatures,rightFeatures,points4d);
        cv::convertPointsFromHomogeneous(points4d.t(), points3d);
        return points3d;
    }
}

