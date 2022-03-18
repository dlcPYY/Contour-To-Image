#include "ImageTrans.h"


bool cmp(contour xi, contour yi) {
	return xi.size > yi.size;
}
//true:逆时针，外轮廓
bool ImageTrans::IsConterClockwise(vector<cv::Point> currContour)
{
	float d = 0;
	Point p1, p0;
	for (int pIdx = 0; pIdx < currContour.size() - 1; pIdx++)
	{
		p0 = currContour.at(pIdx);
		p1 = currContour.at(pIdx + 1);
		d += -0.5 * (p1.y + p0.y) * (p1.x - p0.x);
	}
	Point first, last;
	first = currContour.at(0);
	last = currContour.at(currContour.size() - 1); //这条边不能忘记,加上这条边，使得轮廓闭合
	d += -0.5 * (first.y + last.y) * (first.x - last.x);
	if (d > 0)
		return true;
	else
		return false;
}

ImageTrans::ImageTrans(vector<vector<vector<cv::Point>>>* inputPoints, string outputFilePath) {
	allPoints = new vector<vector<vector<cv::Point>>>(*inputPoints);

	int maxX = 0, maxY = 0;

	for (int i = 0; i < allPoints->size(); i++) {
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			for (int k = 0; k < allPoints->at(i).at(j).size(); k++) {
				maxX = max(maxX, allPoints->at(i).at(j).at(k).x);
				maxY = max(maxY, allPoints->at(i).at(j).at(k).y);
			}
		}
	}
	//rows, 对应的是y
	//cols, 对应的是x
	float deltaX = DLPImageCol / 2.0 - maxX / 2.0;
	float deltaY = DLPImageRow / 2.0 - maxY / 2.0;
	for (int i = 0; i < allPoints->size(); i++) {
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			for (int k = 0; k < allPoints->at(i).at(j).size(); k++) {
				allPoints->at(i).at(j).at(k).x += deltaX;
				allPoints->at(i).at(j).at(k).y += deltaY;
			}
		}
	}
	

	for (int i = 0; i < allPoints->size(); i++) {
		string filePath = outputFilePath + std::to_string(i) + ".png";
		Mat mat(DLPImageRow, DLPImageCol, CV_8UC1, Scalar(0));
		 bool isConterClockwise[50];
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			if (allPoints->at(i).at(j).size() == 0) continue;
			isConterClockwise[j] = IsConterClockwise(allPoints->at(i).at(j));
		}
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			if (allPoints->at(i).at(j).size() == 0) continue;
			if(isConterClockwise[j])
			cv::drawContours(mat, allPoints->at(i), j, Scalar(255 ), 3);
		}
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			if (allPoints->at(i).at(j).size() == 0) continue;
			if (!isConterClockwise[j])
				cv::drawContours(mat, allPoints->at(i), j, Scalar(155), 3);
		}
		cout << "Fin\t" << i << endl;
		cv::imwrite(filePath, mat);
	}
}