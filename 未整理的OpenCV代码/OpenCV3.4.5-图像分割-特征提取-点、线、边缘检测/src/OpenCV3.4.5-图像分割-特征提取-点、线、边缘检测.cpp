#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

/* 孤立点的检测————二阶微分滤波：拉普拉斯算子
 *		1 1 1
 *		1 -8 1
 *		1 1 1
 */
void test1()
{
	Mat src = imread("/Users/wuhan/Downloads/isolated point.bmp",0);			// 球体东北象限有一个几乎不可见的黑点，是孤立点。
	Mat dst1,dst2;

	if(!src.data)
	{
		printf("src image load error!");
		return;
	}

	// 直接使用库函数Laplacian()实现拉普拉斯滤波
	Laplacian(src,dst1,src.depth());		//void cv:: Laplacian (src, dst, int ddepth, int ksize = 1, double scale = 1, double delta = 0, int borderType = BORDER_DEFAULT)

	// 使用filter2D()配合上自制滤波模板实现拉普拉斯滤波：
	Mat_<double> kernel = (Mat_<double>(3,3) << 1,1,1,1,-8,1,1,1,1);
	filter2D(src,dst2,src.depth(),kernel);

	imshow("original image",src);
	imshow("Laplacian()",dst1);
	imshow("home-made kernel filtering",dst2);
	waitKey(0);
}



//  线检测————二阶微分滤波：拉普拉斯算子————各向同性地检测线
void test2()
{
	Mat src,dst;
	src = imread("/Users/wuhan/Downloads/house.jpeg",0);
	Laplacian(src,dst,src.depth());
	imshow("original image", src);
	imshow("Laplacian()",dst);
	waitKey(0);
}



// 线检测————一阶微分滤波算子(梯度算子)————prewitt算子检测特定方向的线。
void test3()
{
	Mat src,dst1,dst2,dst3,dst4;
	Mat_<double> kernel1,kernel2,kernel3,kernel4;
	src = imread("/Users/wuhan/Downloads/house.jpeg",0);

	// 不同方向的梯度算子————Prewitt算子
	kernel1 = (Mat_<double>(3,3)<< -1,-1,-1,0,0,0,1,1,1);		// 竖直方向梯度prewitt算子
	kernel2 = (Mat_<double>(3,3)<< -1,0,1,-1,0,1,-1,0,1);		// 水平方向梯度prewitt算子
	kernel3 = (Mat_<double>(3,3)<< 0,1,1,-1,0,1,-1,-1,0);		// -45°方向梯度prewitt算子
	kernel4 = (Mat_<double>(3,3)<< -1,-1,0,-1,0,1,0,1,1);		// +45°方向梯度prewitt算子
	filter2D(src,dst1,src.depth(),kernel1);
	filter2D(src,dst2,src.depth(),kernel2);
	filter2D(src,dst3,src.depth(),kernel3);
	filter2D(src,dst4,src.depth(),kernel4);
	imshow("original image", src);
	imshow("vertical gradient prewitt operator", dst1);
	imshow("horizontal gradient prewitt operator",dst2);
	imshow("-45 gradient prewitt operator",dst3);
	imshow("+45 gradient prewitt operator",dst4);
	waitKey(0);
}



// 线检测————平滑+梯度的复合算子————Sobel算子
void test4()
{
	Mat src,dst01,dst02,dst1,dst2,dst3,dst4;
	Mat_<double> kernel1,kernel2,kernel3,kernel4;
	src = imread("/Users/wuhan/Downloads/house.jpeg",0);

	// 直接使用Sobel()库函数进行sobel算子滤波：
	Sobel(src,dst01,src.depth(),1,0);
	Sobel(src,dst02,src.depth(),0,1);


	kernel1 = (Mat_<double>(3,3)<< -1,-2,-1,0,0,0,1,2,1);		// y方向梯度sobel算子
	kernel2 = (Mat_<double>(3,3)<< -1,0,1,-2,0,2,-1,0,1);		// x方向梯度sobel算子
	kernel3 = (Mat_<double>(3,3)<< 0,1,2,-1,0,1,-2,-1,0);		// -45°方向梯度sobel算子
	kernel4 = (Mat_<double>(3,3)<< -2,-1,0,-1,0,1,0,1,2);		// +45°方向梯度sobel算子
	filter2D(src,dst1,src.depth(),kernel1);
	filter2D(src,dst2,src.depth(),kernel2);
	filter2D(src,dst3,src.depth(),kernel3);
	filter2D(src,dst4,src.depth(),kernel4);

	imshow("original image",src);
	imshow("Sobel(),x direction gradient",dst01);
	imshow("Sobel(),y direction gradient",dst02);
	imshow("vertical gradient sobel operator", dst1);
	imshow("horizontal gradient sobel operator",dst2);
	imshow("-45 gradient sobel operator",dst3);
	imshow("+45 gradient sobel operator",dst4);


	waitKey(0);

}

/* 线检测————最优秀的复合算子————Canny算子
 * 		缺点：运算量大，效率低。
 * 		步骤：1. 平滑图像降噪。
 * 			 2. 计算梯度幅值和方向。
 * 			 3. 非极大值抑制————仅保留一些细线条。
 * 			 4. 双阈值处理。
 */
void test5()
{
	Mat src,dst1,dst2,dst3,dst4;
	Mat_<double> kernel1,kernel2,kernel3,kernel4;
	src = imread("/Users/wuhan/Downloads/house.jpeg",0);

	Canny(src,dst1,50,150);
	Laplacian(src,dst2,src.depth());

	imshow("original image",src);
	imshow("Canny()", dst1);
	imshow("Laplacian()",dst2);

	waitKey(0);
}

int main(int argc, char** argv)
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();

    return 0;
}
