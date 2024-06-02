// PoseEstimation.cpp
#include "../include/PoseEstimation.h"
#include <opencv2/calib3d.hpp>

bool Pose_Estimation::estimatePose(const std::vector<cv::Point2f>& imagePoints,
    const std::vector<cv::Point3f>& objectPoints,
    cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
    cv::Mat& rvec, cv::Mat& tvec) {
    // 调用solvePnP函数进行位姿估计
    return cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);
}