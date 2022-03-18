#pragma once
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
using namespace cv;
struct contour {
	vector<cv::Point> contourPoint;
	float size;
};
const float pixelSize = 0.075;
class PointsReading
{
public:
	PointsReading(string filePath);
	vector<vector<vector<cv::Point>>>* GetModel() { return allPoints; }
private:
	vector<vector<vector<cv::Point>>>* allPoints;
};

