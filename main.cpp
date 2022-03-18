#include"ImageTrans.h"
#include"PointsReading.h"
int main() {
	PointsReading* pointsReading = new PointsReading("./Input/Perlin_TPMS.data");
	ImageTrans* imageTrans = new ImageTrans(pointsReading->GetModel(), "./OUT2/");
}