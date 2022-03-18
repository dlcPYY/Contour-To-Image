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
//��Ҳ����rows, ��Ӧ����y�����ε�height��Ϣ������y����
//��Ҳ����cols, ��Ӧ����x�����ε�width��Ϣ������x����
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

