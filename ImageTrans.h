#pragma once
#include <random>
#include <functional>
#include <iostream>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include "PointsReading.h"
using namespace std;
using namespace cv;
//行也就是rows, 对应的是y，矩形的height信息就是在y方向；
//列也就是cols, 对应的是x，矩形的width信息就是在x方向；
const int DLPImageRow = 1080;
const int DLPImageCol = 1920;
class ImageTrans
{
public:
	bool IsConterClockwise(vector<cv::Point> currContour);
	ImageTrans(vector<vector<vector<cv::Point>>>* inputPoints, string outputFilePath);
private:
	vector<vector<vector<cv::Point>>>* allPoints;
};

