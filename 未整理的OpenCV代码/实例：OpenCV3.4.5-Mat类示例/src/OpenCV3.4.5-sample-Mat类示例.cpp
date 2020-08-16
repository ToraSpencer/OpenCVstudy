#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;



int main(int,char**)
{
	//改变控制台的前景色和背景色
	system("color 8F");


	Mat I = Mat::eye(4, 4, CV_64F);
	I.at<double>(1,1) = CV_PI;
	cout << "\nI = " << I << ";\n" << endl;

	getchar();

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));


	Point2f p(6, 2);
	cout << "【2维点】p = " << p << ";\n" << endl;




	Point3f p3f(8, 2, 0);
	cout << "【3维点】p3f = " << p3f << ";\n" << endl;

	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	cout << "【基于Mat的vector】shortvec = " << Mat(v) << ";\n"<<endl;

	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));

	cout << "【二维点向量】points = " << points<<";";

	getchar();//按任意键退出

	return 0;

}
