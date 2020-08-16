/*
*/


#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>

using namespace std;
using namespace cv;

//声明全局变量
Mat src;
Mat dst;
int alpha; 					//亮度缩放因子。

//灰度放大的回调函数
void on_brightnessZoom(int, void*)
{
	double beta = double(alpha)/100.0;
	src.convertTo(dst, src.type(), beta);
	imshow("opeated image",dst);
	cout << "当前亮度缩放" << alpha << "%" << endl;
}

// test1: convertTo()实现的灰度放大。———— 数学表示：s = r * alpha
void test1()
{
	cout << "test1: convertTo()实现的亮度缩放。" << endl << endl;
	src = imread("lena.jpg");

	namedWindow("original image");
	imshow("original image", src);

	namedWindow("operated image");
	createTrackbar("brightness zoom", "operated image", &alpha, 200, on_brightnessZoom);
	on_brightnessZoom(100,nullptr);

	while(char(waitKey(1)) != 'q') {}				//按下q键退出窗口。

}

/* test2: 灰度拉伸（对比度拉伸）———— 分段灰度线性变换；将灰度跨度很小的低对比度图片，拉伸到灰度跨越所有灰度级。
 * 			数学表示：(1) r1,r2,s1,s2是选择的转折点。
 * 						T(r) = s1/r1 * r						r > r1
 * 						T(r) = (s2-s1)/(r2-r1)*(r-r1) + s1;		r1 <= r <= r2
 * 						T(r) = (L-1-r2)/(r-r2)*(r-r2) + s2;		r > r2
 * 						8bit灰度图中L = 256
 * 					(2) 若直接全局拉伸，则直接使用灰度线性变化，而不是分段线性变换：
 * 							即选取r1 = rmin, r2 = rmax, s1 = 0, s2 = L-1;
 * 							T(r) = (L-1)*(r-rmin)/(rmax-rmin);
 */
void test2()
{
	Mat src,dst;
	double rmin,rmax;
	uchar *p, *q;

	src = imread("/Users/wuhan/Downloads/lowContrastImage.jpg",0);
	dst = src.clone();
	cv::minMaxIdx(src,&rmin,&rmax);

	if(!src.data)
	{
		cout << " input image is empty!" << endl;
		return ;
	}

	// for循环遍历所有像素，进行灰度变换。
	for (int i = 0;i < src.rows; i++)
	{
	     for (int j = 0; j < src.cols; j++)
	     {
	    	 p = src.ptr<uchar>(i,j);
	    	 q = dst.ptr<uchar>(i,j);
	    	 *q = saturate_cast<uchar>(255*(double(*p)-rmin)/(rmax-rmin));  // 饱和转换，限定输出类型是uchar，且防止数据溢出。
	    	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  // 算式中应该是浮点数的计算，不能是整型的计算。
	     }
	}

	imshow("input",src);
	imshow("output",dst);
	waitKey(0);
}












int main()
{
	//test1();
	test2();

	return 0;
}
