// ColorDetection.cpp
#include "../include/ColorDetection.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

// ��ʼ����ɫ��Χ�ͻ�����ɫ
std::vector<std::vector<int>> ColorDetection::myColors = {
    {130, 70, 40, 150, 255, 255},
    {100, 40, 0, 179, 110, 60},
    {60, 60, 0, 90, 255, 255},
    {140, 0, 100, 165, 150, 255},
    {170, 130, 0, 179, 255, 255},
    {100, 80, 60, 110, 255, 255},
    {0, 110, 130, 20, 255, 255},
    {110, 180, 50, 120, 255, 255},
    {30, 50, 0, 50, 255, 255}
};

std::vector<cv::Scalar> ColorDetection::myColorValues = {
    {128, 0, 128},
    {0, 0, 255},
    {0, 165, 255},
    {0, 255, 255},
    {0, 255, 0},
    {255, 0, 0},
    {255, 255, 0},
    {0, 0, 0},
    {128, 128, 128},
    {128, 0, 0}
};

ColorDetection::ColorDetection() {
}

PointColor::PointColor(cv::Point2f p, int index) : point(p), colorIndex(index) {}

// getContours���������Ի��������������ҵ��ĵ�
std::vector<PointColor> ColorDetection::getContours(cv::Mat imgDil, cv::Mat& img, int colorIndex) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<PointColor> colorPoints;

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<cv::Rect> boundRect(contours.size());

    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > 1000) {
            boundRect[i] = boundingRect(contours[i]); // ʹ������������С��Ӿ���
            cv::Point center(boundRect[i].x + boundRect[i].width / 2,
                boundRect[i].y + boundRect[i].height / 2);
            colorPoints.push_back(PointColor(center, colorIndex));

            // ֱ�ӻ���������boundingRect��������conPoly
            cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), myColorValues[colorIndex], 2);
            cv::circle(img, center, 10, myColorValues[colorIndex], 1, -1, 0);
        }
    }
    return colorPoints;
}

// findColor������������ʶ�𵽵ĵ�ļ���
std::vector<PointColor> ColorDetection::findColor(cv::Mat img) {
    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    std::vector<PointColor> allPoints;

    for (int i = 0; i < myColors.size(); i++) {
        cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        cv::Mat mask;
        inRange(imgHSV, lower, upper, mask);
        std::vector<PointColor> points = getContours(mask, img, i);
        allPoints.insert(allPoints.end(), points.begin(), points.end());
    }

    return allPoints;
}

// ���麯�������ڸ��� y ����������Է��飬�ڷ�Χ�ڵı���Ϊһ��
std::vector<std::vector<PointColor>> ColorDetection::groupByYCoordinate(std::vector<PointColor> pointColors, int y_threshold) {
    std::vector<std::vector<PointColor>> groups;
    std::vector<bool> used(pointColors.size(), false);

    for (size_t i = 0; i < pointColors.size(); ++i) {
        if (used[i]) continue;
        std::vector<PointColor> group;
        group.push_back(pointColors[i]);
        used[i] = true;

        // Ѱ���� y_threshold ��Χ�ڵ����е�
        for (size_t j = i + 1; j < pointColors.size(); ++j) {
            if (!used[j] && abs(pointColors[i].point.y - pointColors[j].point.y) < y_threshold) {
                group.push_back(pointColors[j]);
                used[j] = true;
            }
        }

        groups.push_back(group); // ���ٸ��ݹ̶��Ĵ�С�жϣ����е��鶼����ӵ� groups ��
    }
    return groups;
}

// ���� x ����Ե����������ֻ�����ڱ�׼������Ϊ������5���㣩
void ColorDetection::sortGroupByXCoordinate(std::vector<PointColor>& group) {
    sort(group.begin(), group.end(), [](const PointColor& a, const PointColor& b) {
        return a.point.x < b.point.x;
        });
}

// �ȽϺ������ڰ�x��������
bool ColorDetection::comparePointsX(const cv::Point2f& a, const cv::Point2f& b) {
    return a.x < b.x;
}

// �ȽϺ������ڰ�y��������
bool ColorDetection::comparePointsY(const cv::Point2f& a, const cv::Point2f& b) {
    return a.y < b.y;
}

// �Ե��������
void ColorDetection::sortImagePoints(std::vector<cv::Point2f>& imagePoints) {
    // �Ȱ�y��������
    std::sort(imagePoints.begin(), imagePoints.end(), comparePointsY);

    // ����ÿ��Ӧ�еĵ���
    const int pointsPerRow = 3;

    // ��һ������Ƿ��������������һ��
    if (imagePoints.size() % pointsPerRow != 0) {
        throw std::runtime_error("The number of points in imagePoints is not a multiple of 3.");
    }

    // Ȼ�����Ƿ��飬ÿ�������㰴x����
    for (size_t i = 0; i < imagePoints.size(); i += pointsPerRow) {
        std::sort(imagePoints.begin() + i, imagePoints.begin() + i + pointsPerRow, comparePointsX);
    }
}