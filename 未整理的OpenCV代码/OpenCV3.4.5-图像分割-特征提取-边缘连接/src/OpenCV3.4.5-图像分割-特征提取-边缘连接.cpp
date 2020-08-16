#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

// 标准霍夫变换SHT——HoughLines()
// 全局变量
Mat src,dst,edge;
vector<Vec2f> lines;		// 存放提取出的直线矢量。
int n_threshold;			// 霍夫变换的阈值。

static void onThreshold(int n_threshold, void*)
{
	// 标准霍夫变换，从检测出的边缘中提取直线，保存在lines数组中。
	HoughLines(edge, lines, 1, CV_PI/180, n_threshold);

	// 画出提取出的直线。
	for(size_t i = 0; i< lines.size(); i++)
	{
		float rho, theta;
		Point pt1, pt2;
		double a, b, x0, y0;

		rho = lines[i][0];
		theta = lines[i][1];


	}



}

void test1()
{
	src = imread("/Users/wuhan/Downloads/buliding.jpg",0);
	if(!src.data)
	{
		printf("src is empty!");
		return ;
	}

	// 使用Canny算子检测轮廓：
	Canny(src, edge, src.depth(),50, 150);
	dst = edge.clone();



	namedWindow("SHT");
	createTrackBar("threshold:", "SHT", &n_threshold, 100, onThreshold);



}


int main()
{
	test1();

	return 0;
}

