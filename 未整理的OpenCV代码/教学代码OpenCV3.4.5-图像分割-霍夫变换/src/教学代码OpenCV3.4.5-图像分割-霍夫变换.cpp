
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

// 标准霍夫变换HoughLines()

void test1()
{
	Mat src,edge,dst;

	src = imread("/Users/wuhan/Downloads/buliding.jpg");
	if(!src.data)
	{
		printf("src is empty!");
		return ;
	}

	Canny(src, edge, 50, 200, 3);
	cvtColor(edge,dst, COLOR_GRAY2BGR);		// 转化边缘检测后的图为灰度图

	// 对提取的边缘进行霍夫线变换
	vector<Vec2f> lines;					// 定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLines(edge, lines, 1, CV_PI/180, 150, 0, 0 );

	// 依次在图中绘制出每条线段
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( dst, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
	}


	imshow("original image", src);
	imshow("after canny()", edge);
	imshow("after hough transform", dst);

	waitKey(0);
}

// 累计概率霍夫变换：HoughlinesP()
void test2()
{
	Mat src,edge,dst;

	src = imread("/Users/wuhan/Downloads/buliding.jpg");
	if(!src.data)
	{
		printf("src is empty!");
		return ;
	}

	// 进行边缘检测和转化为灰度图
	Canny(src, edge, 50, 200, 3);
	cvtColor(edge,dst, COLOR_GRAY2BGR);				//转化边缘检测后的图为灰度图

	//【3】进行霍夫线变换
	vector<Vec4i> lines;						//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(edge, lines, 1, CV_PI/180, 80, 50, 10 );

	//【4】依次在图中绘制出每条线段
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];

		line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, LINE_AA);
	}


	imshow("original image", src);
	imshow("after canny()", edge);
	imshow("after hough transform", dst);

	waitKey(0);

}

// 霍夫圆变换HoughCircles()
void test3()
{
	Mat src,smoothGray,dst;

	src = imread("/Users/wuhan/Downloads/HoughCircle.jpg");
	if(!src.data)
	{
		printf("src is empty!");
		return ;
	}

	dst = src.clone();

	imshow("【原始图】", src);

	// 转为灰度图并进行图像平滑
	cvtColor(src, smoothGray, COLOR_BGR2GRAY); //转化边缘检测后的图为灰度图
	GaussianBlur( smoothGray, smoothGray, Size(9, 9), 2, 2 );

	// 进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles( smoothGray, circles, HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0 );

	// 依次在图中绘制出圆
	for( size_t i = 0; i < circles.size(); i++ )
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle( dst, center, 3, Scalar(0,255,0), -1, 8, 0 );
		//绘制圆轮廓
		circle( dst, center, radius, Scalar(155,50,255), 3, 8, 0 );
	}

	imshow("original image", src);
	imshow("smoothGray", smoothGray);
	imshow("draw circle", dst);

	waitKey(0);

}

// 对累计概率霍夫变换阈值的研究：	阈值越高，画出的线越少。
// 全局变量：
Mat SRC, MID, DST;	// 原始图、中间图和效果图
vector<Vec4i> LINES;			//定义一个矢量结构g_lines用于存放得到的线段矢量集合
int n_threshold = 100;			//变量接收的TrackBar位置参数

// 回调函数：
static void on_HoughLines(int, void*)
{
	//定义局部变量储存全局变量
	Mat dst = DST.clone();
	Mat mid = MID.clone();

	//调用HoughLinesP函数
	vector<Vec4i> mylines;
	HoughLinesP(mid, mylines, 1, CV_PI/180, n_threshold+1, 50, 10 );

	//循环遍历绘制每一条线段
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, LINE_AA);
	}
	//显示图像
	imshow("output",dst);
}

void test4()
{
	SRC = imread("/Users/wuhan/Downloads/buliding.jpg");
	if(!SRC.data)
	{
		printf("src is empty!");
		return ;
	}

	imshow("original image", SRC);

	//创建滚动条
	namedWindow("output",1);
	createTrackbar("value", "output",&n_threshold, 200, on_HoughLines);

	//进行边缘检测和转化为灰度图
	Canny(SRC, MID, 50, 200, 3);//进行一次canny边缘检测
	cvtColor(MID, DST, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图

	//调用回调函数
	on_HoughLines(n_threshold, 0);


	waitKey(0);

}



int main()
{
	//test1();
	//test2();
	//test3();
	test4();

	return 0;
}








