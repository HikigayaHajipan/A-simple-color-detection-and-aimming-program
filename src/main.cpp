#include "../include/ColorDetection.h"
#include "../include/PoseEstimation.h"
#include "../include/SerialPortSender.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img;
vector<PointColor> newPoints;

int main() {
    // 加载图片
    img = imread("颜色识别测试图/init.jpg"); // 确保指定正确的图片文件路径

    // 检查图片是否正确加载
    if (img.empty()) {
        cerr << "无法读取图片" << endl;
        return 1;

    }

    // 存储带有颜色索引的所有点
    vector<PointColor> allPointColors = ColorDetection::findColor(img);

    // 根据 y 轴上的阈值对点进行分组
    vector<vector<PointColor>> groupedPointColors = ColorDetection::groupByYCoordinate(allPointColors, 20);

    // 暂存标准区和目标区的点
    vector<PointColor> standardArea;
    vector<PointColor> targetArea;

    // 选取第一个有5个点的组作为标准区
    for (auto& group : groupedPointColors) {
        if (group.size() == 5) {
            ColorDetection::sortGroupByXCoordinate(group);
            standardArea = group;
            break; // 找到标准区就跳出循环
        }
    }

    // 将其他所有点视作目标区
    for (auto& pointColor : allPointColors) {
        bool isStandard = false;
        for (auto& stdPointColor : standardArea) {
            if (pointColor.point == stdPointColor.point) {
                isStandard = true;
                break;
            }
        }
        if (!isStandard) {
            targetArea.push_back(pointColor);
        }
    }

    // 输出标准区和目标区的点与颜色索引
    cout << "Standard Area Points and Color Index:" << endl;
    for (const auto& pc : standardArea) {
        cout << "Point: " << pc.point << " Color Index: " << pc.colorIndex << endl;
    }

    cout << "Target Area Points and Color Index:" << endl;
    for (const auto& pc : targetArea) {
        cout << "Point: " << pc.point << " Color Index: " << pc.colorIndex << endl;
    }

    // 对标准区的每一个点，寻找目标区相同颜色索引的点
    cout << "Matching Points:" << endl;
    for (const auto& stdPc : standardArea) {
        for (const auto& tgtPc : targetArea) {
            if (stdPc.colorIndex == tgtPc.colorIndex) {
                cout << "Standard Point: " << stdPc.point << ", Target Point: " << tgtPc.point
                    << ", Color Index: " << stdPc.colorIndex << endl;
            }
        }
    }

    destroyAllWindows();

    return 0;
}
