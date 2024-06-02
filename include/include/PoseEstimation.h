// PoseEstimation.h
#ifndef POSE_ESTIMATION_H
#define POSE_ESTIMATION_H

#include <opencv2/core.hpp>
#include <vector>

class Pose_Estimation {
public:
    static bool estimatePose(const std::vector<cv::Point2f>& imagePoints,
        const std::vector<cv::Point3f>& objectPoints,
        cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
        cv::Mat& rvec, cv::Mat& tvec);
};

#endif// POSE_ESTIMATION_H