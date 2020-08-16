#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
using namespace std;
using namespace cv;

//产生高斯噪声的函数：
double generateGaussianNoise(double mu, double sigma)
{
	//定义小值
	const double epsilon = numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假构造高斯随机变量X
	if (!flag)
		return z1 * sigma + mu;

	double u1, u2;
	//构造随机变量
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	}
	while (u1 <= epsilon);
	//flag为真构造高斯随机变量
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
	return z0*sigma + mu;
}


//test1():线性空域滤波——算数均值滤波、加权均值滤波
//				均值滤波器可以平滑图像，起到去噪的作用。
void test1()
{
	Mat src = imread("lena.jpg");

		cout << "src.channels() = " << src.channels() << endl;
		cout << "src.depth() = " << src.depth() << endl;
		imshow("original image",src);
		waitKey(0);

		cout << "添加高斯噪声：" << endl;
		Mat dst = src.clone();
			int channels = dst.channels();
			int rowsNumber = dst.rows;
			int colsNumber = dst.cols*channels;
			//？？？判断图像的连续性
			if (dst.isContinuous())
			{
				colsNumber *= rowsNumber;
				rowsNumber = 1;
			}
			for (int i = 0; i < rowsNumber; i++)
			{
				for (int j = 0; j < colsNumber; j++)
				{
					//添加高斯噪声
					int val = dst.ptr<uchar>(i)[j] +
						generateGaussianNoise(2, 0.8) * 32;
					if (val < 0)
						val = 0;
					if (val>255)
						val = 255;
					dst.ptr<uchar>(i)[j] = (uchar)val;
				}
			}

		imshow("added gaussian noise",dst);
		waitKey(0);

		cout << "boxFilter()实现的算数均值滤波：" << endl;
		Mat dst_box;
		//void cv::boxFilter(src, dst, int ddepth, Size ksize, Point anchor = Point(-1,-1), bool normalize = true, int borderType = BORDER_DEFAULT )

		boxFilter( dst, dst_box, -1,Size(5, 5));
		imshow("filtered by boxFilter()",dst_box);
		waitKey(0);

		cout << "blur()函数实现的均值滤波" << endl;
		Mat dst_blur;
		//void blur( src, dst, Size ksize, Point anchor = Point(-1,-1), int borderType = BORDER_DEFAULT );
		blur( dst, dst_blur, Size(7, 7));
		imshow("filtered by blur()",dst_blur);
		waitKey(0);

		cout << "filter2D()普适滑动邻域操作实现的均值滤波" << endl;
		//普适滑动领域操作，即二维离散卷积
		//void cv::filter2D	(src, dst, int ddepth, InputArray kernel, Point anchor = Point(-1,-1), double delta = 0, borderType = BORDER_DEFAULT)
		Mat dst_fil;
		Mat kernel = Mat::ones(5,5,CV_8UC1);
		kernel = (Mat_<double>)kernel;
		kernel = kernel/25;
		filter2D(dst,dst_fil,src.depth(),kernel);
		imshow("filtered by filter2D()", dst_fil);
		waitKey(0);

		cout << "blur(),boxFilter()的底层实现：" << endl;
		Mat_<double> f = (Mat_<double>(3,4) << 1,2,3,4,5,6,7,8,9,10,11,12);
		cout << "f = \n" << f << endl;
		Mat_<double> g;
		boxFilter(f,g,f.depth(),Size(3,3));
		cout << "boxFilter()滤波：g = \n" << g << endl;
		blur(f,g,Size(3,3));
		cout << "blur()滤波：g = \n" << g << endl;
		Mat_<double> k = Mat_<double>::ones(3,3);
		k = k/9;
		filter2D(f,g,f.depth(),k);
		cout << "filter2D()滤波：g = \n" << g << endl;
		cout << "以上三者滤波模板都是一样的。" << endl;

}

//test2():线性空域滤波——微分滤波：
//				微分滤波器可以锐化图像，可以进行边缘检测。
void test2()
{
	cout << "test2():线性空域滤波——微分滤波：" << endl;
	Mat src = imread("/Users/wuhan/Downloads/wall.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("original image", src);
	waitKey(0);

	cout << "Laplacian()实现的拉普拉斯算子滤波" << endl;
	//void cv:: Laplacian (src, dst, int ddepth, int ksize = 1, double scale = 1, double delta = 0, int borderType = BORDER_DEFAULT)
	Mat dst_lap;
	Laplacian(src,dst_lap,src.depth());
	imshow("Laplacian() filtered", dst_lap);
	waitKey(0);

	Mat_<double> dst_lap_sharp = Mat_<double>(src)+Mat_<double>(dst_lap);
	double minVal;
	double maxVal;
	int minIdx[2];
	int maxIdx[2];
	minMaxIdx(dst_lap_sharp,&minVal,&maxVal,minIdx,maxIdx);
	dst_lap_sharp = dst_lap_sharp/maxVal;
	imshow("sharpen by Laplacian()",dst_lap_sharp);
	waitKey(0);


	cout << "Sobel()实现的sobel算子滤波" << endl;
	//void cv:: Sobel (src, dst, int ddepth, int dx, int dy,
	//					int 	ksize = 3,
	//					double 	scale = 1,
	//					double 	delta = 0,
	//					int 	borderType = BORDER_DEFAULT )
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//求x方向梯度
	Sobel(src, grad_x, src.depth(), 1, 0);
	imshow("x direction soble", grad_x);
	waitKey(0);

	//求y方向梯度
	Sobel(src, grad_y, src.depth(), 0, 1);
	imshow("y direction soble", grad_y);
	waitKey(0);





	cout << "自定义线性空域滤波模板用filter2D()实现的微分滤波：" << endl;

}

//test3():最优秀的边缘检测算子canny
void test3()
{
	Mat image = imread("lena.jpg");
	Mat src = image.clone();
	Mat dst;
	cvtColor( src, src, COLOR_BGR2GRAY );
	namedWindow("original image");
	imshow("original image", image);
	namedWindow("original gray image");
	imshow("original gray image", src);

	//使用canny算法提取灰度图边缘。
	Canny(src, dst, 3, 9);
	namedWindow("edge distracted by canny");
	imshow("edge distracted by canny", dst);

	//原图像覆盖上提取出来的边缘图案，实现边缘强化。
	Mat edge = dst.clone();
	image.copyTo(dst,edge);
	namedWindow("accented edge");
	imshow("accented edge", dst);

	waitKey(0);
}

//test4():非线性空域滤波——统计排序滤波
void test4()
{
	Mat src = imread("lena.jpg");

		cout << "src.channels() = " << src.channels() << endl;
		cout << "src.depth() = " << src.depth() << endl;
		imshow("original image",src);
		waitKey(0);

		cout << "添加高斯噪声：" << endl;
		Mat dst = src.clone();
			int channels = dst.channels();
			int rowsNumber = dst.rows;
			int colsNumber = dst.cols*channels;
			//？？？判断图像的连续性
			if (dst.isContinuous())
			{
				colsNumber *= rowsNumber;
				rowsNumber = 1;
			}
			for (int i = 0; i < rowsNumber; i++)
			{
				for (int j = 0; j < colsNumber; j++)
				{
					//添加高斯噪声
					int val = dst.ptr<uchar>(i)[j] +
						generateGaussianNoise(2, 0.8) * 32;
					if (val < 0)
						val = 0;
					if (val>255)
						val = 255;
					dst.ptr<uchar>(i)[j] = (uchar)val;
				}
			}

		imshow("added gaussian noise",dst);
		waitKey(0);

		cout << "medianBlur()实现的中值滤波" << endl;
		//void medianBlur( InputArray src, OutputArray dst, int ksize );
		Mat dst_med;
		medianBlur(dst,dst_med,5);
		imshow("median filtered by medianBlur()", dst_med);
		waitKey(0);
}

int main()
{
	//test1();
	//test2();
	test3();


	return 0;
}
