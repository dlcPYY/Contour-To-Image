#include "PointsReading.h"
PointsReading::PointsReading(string filePath) {
	allPoints = new vector<vector<vector<Point>>>;
	int minX = 100000, minY = 100000;
	ifstream in(filePath);
	if (!in.is_open())
	{
		std::cout << "File opening error: " << filePath << endl;
	}
	int layerNumber;
	in >> layerNumber;
	for (int i = 0; i < layerNumber; i++) {
		int contourNumber;
		in >> contourNumber;
		vector<vector<Point>> allContour;
		for (int j = 0; j < contourNumber; j++) {
			int pointsNumber;
			in >> pointsNumber;
			vector<Point> allPointss;
			for (int k = 0; k < pointsNumber; k++) {
				Point nowPoint;
				float xx, yy;
				in >> xx >> yy;
				nowPoint.x = xx / pixelSize;
				nowPoint.y = yy / pixelSize;
				minX = min(minX, nowPoint.x);
				minY = min(minY, nowPoint.y);
				allPointss.push_back(nowPoint);
			}
			allContour.push_back(allPointss);
		}
		allPoints->push_back(allContour);
	}
	for (int i = 0; i < allPoints->size(); i++) {
		for (int j = 0; j < allPoints->at(i).size(); j++) {
			for (int k = 0; k < allPoints->at(i).at(j).size(); k++) {
				
				allPoints->at(i).at(j).at(k).x -= minX;
				allPoints->at(i).at(j).at(k).y -= minY;
			}
		}
	}
	in.close();
}