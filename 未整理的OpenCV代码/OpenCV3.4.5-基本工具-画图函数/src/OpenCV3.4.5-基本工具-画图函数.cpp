#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void test1()
{

	Mat image;
	Point pt1,pt2;

	// 创建空白的8位位深RGB图片：
	image = Mat::zeros(300,300,CV_8UC3);

	// 确定直线的两个点：
	pt1 = Point(100,100);
	pt2 = Point(200,150);

	// 使用line()画直线：
	line(image,pt1,pt2,Scalar(255,0,0,0));

	imshow("line",image);
	waitKey(0);
}


int main()
{
	test1();



	return 0;
}
