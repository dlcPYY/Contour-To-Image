#include "ImageTrans.h"


bool cmp(contour xi, contour yi) {
	return xi.size > yi.size;
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
	
	



	for (int i = 21; i < allPoints->size(); i++) {
		contour everyContour[50];
		string filePath = outputFilePath + std::to_string(i) + ".png";
		Mat mat(DLPImageRow, DLPImageCol, CV_8UC1, Scalar(0));
		vector<vector<cv::Point>> allContour;
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			everyContour[j].contourPoint = allPoints->at(i).at(j);
			if (everyContour[j].contourPoint.size() <= 3)everyContour[j].size = 0;
			else 
				everyContour[j].size = contourArea(allPoints->at(i).at(j));
		}
		sort(everyContour, everyContour + allPoints->at(i).size(), cmp);
	
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			vector<cv::Point > nowContour;
			for (int k = 0; k < everyContour[j].contourPoint.size(); k++) {
				int nowCol = everyContour[j].contourPoint.at(k).y;// / pixelSize;//allPoints->at(i).at(j).at(k).y / pixelSize;
				int nowRow = everyContour[j].contourPoint.at(k).x;// / pixelSize;
				cv::Point nowPoint;
				nowPoint.x = nowRow;
				nowPoint.y = nowCol;
				nowContour.push_back(nowPoint);
			}
			allContour.push_back(nowContour);
		}
		for (int j = 0; j < allContour.size(); j++) {
			int color = -1;
			if (allContour.at(j).size() <= 3) continue;
			for (int ii = 0; ii < mat.rows; ii++) {
				if (color >= 0) break;
				for (int jj = 0; jj < mat.cols; jj++) {
					double distance = pointPolygonTest(allContour[j], Point2f(jj, ii), true);
					if (distance > 0.1) {
						color = mat.at<uchar>(ii, jj);
						break;
					}
				}
			}
			cv::drawContours(mat, allContour, j, Scalar(255-color ), -1);
			cout << color << endl;
		}
		cout << "Fin\t" << i << endl;
		cv::imwrite(filePath, mat);
	}
}