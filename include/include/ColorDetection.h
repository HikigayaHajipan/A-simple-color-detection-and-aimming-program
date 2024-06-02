#ifndef COLORDETECTION_H
#define COLORDETECTION_H

#include <opencv2/opencv.hpp>
#include <vector>

struct PointColor {
    cv::Point2f point;
    int colorIndex;

    PointColor(cv::Point2f p, int index);
};

class ColorDetection {
public:
    ColorDetection();
    static std::vector<PointColor> findColor(cv::Mat img);
    static std::vector<PointColor> getContours(cv::Mat imgDil, cv::Mat& img, int colorIndex);
    static std::vector<std::vector<PointColor>> groupByYCoordinate(std::vector<PointColor> pointColors, int y_threshold);
    static void sortGroupByXCoordinate(std::vector<PointColor>& group);
    static void sortImagePoints(std::vector<cv::Point2f>& imagePoints);
    static bool comparePointsX(const cv::Point2f& a, const cv::Point2f& b);
    static bool comparePointsY(const cv::Point2f& a, const cv::Point2f& b);
private:
    static std::vector<std::vector<int>> myColors;
    static std::vector<cv::Scalar> myColorValues;
};

#endif //COLORDETECTION_H