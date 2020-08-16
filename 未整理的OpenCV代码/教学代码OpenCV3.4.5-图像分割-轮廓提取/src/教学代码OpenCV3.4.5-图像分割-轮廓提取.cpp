#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

void test1()
{
	Mat src,mid,dst;

	src = imread("/Users/wuhan/Downloads/contours.jpg",0);
	if(!src.data)
	{
		printf("src is empty!");
		return ;
	}
	mid = src.clone();

	// 初始化结果图
	dst  = Mat::zeros(src.rows, src.cols, CV_8UC3);

	// srcImage取大于阈值119的那部分
	mid = mid > 119;

	// 定义轮廓和层次结构
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// 查找轮廓
	findContours( mid, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE );
	// 			hierarchy为一个vector,里面存储的是point对象，每一个point对象表示一个轮廓

	// 遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		Scalar color( rand()&255, rand()&255, rand()&255 );

		drawContours( dst, contours, index, color, FILLED, 8, hierarchy );
	}

	// 显示最后的轮廓图
	imshow("original image",src);
	imshow("after threshold operation", mid);
	imshow( "contourse", dst );

	waitKey(0);
}


int main( )
{
	test1();



	return 0;


}
