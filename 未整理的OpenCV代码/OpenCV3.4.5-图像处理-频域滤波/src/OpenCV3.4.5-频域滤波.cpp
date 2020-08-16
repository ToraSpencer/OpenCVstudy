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


//test1(): 离散傅里叶变换和逆变换————网络上的教学代码。
void test1()
{
	cout << "test1(): 离散傅里叶变换和逆变换————网络上的教学代码。" << endl << endl;
	Mat input = imread("lena.jpg",CV_LOAD_IMAGE_GRAYSCALE);

	 	imshow("input",input);//显示原图
	 	waitKey(0);

		int w=getOptimalDFTSize(input.cols);
		int h=getOptimalDFTSize(input.rows);//获取最佳尺寸，快速傅立叶变换要求尺寸为2的n次方
		Mat padded;
		copyMakeBorder(input,padded,0,h-input.rows,0,w-input.cols,BORDER_CONSTANT,Scalar::all(0));//填充图像保存到padded中
		Mat plane[]={Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F)};//创建通道
		Mat complexIm;
		merge(plane,2,complexIm);		//合并通道
		dft(complexIm,complexIm);		//进行傅立叶变换，结果保存在自身
		split(complexIm,plane);			//分离通道
		magnitude(plane[0],plane[1],plane[0]);//获取幅度图像，0通道为实数通道，1为虚数，因为二维傅立叶变换结果是复数
		int cx=padded.cols/2;int cy=padded.rows/2;//一下的操作是移动图像，左上与右下交换位置，右上与左下交换位置
		Mat temp;
		Mat part1(plane[0],Rect(0,0,cx,cy));
		Mat part2(plane[0],Rect(cx,0,cx,cy));
		Mat part3(plane[0],Rect(0,cy,cx,cy));
		Mat part4(plane[0],Rect(cx,cy,cx,cy));


		part1.copyTo(temp);
		part4.copyTo(part1);
		temp.copyTo(part4);

		part2.copyTo(temp);
		part3.copyTo(part2);
		temp.copyTo(part3);


		//Mat _complexim(complexIm,Rect(padded.cols/4,padded.rows/4,padded.cols/2,padded.rows/2));
		//opyMakeBorder(_complexim,_complexim,padded.rows/4,padded.rows/4,padded.cols/4,padded.cols/4,BORDER_CONSTANT,Scalar::all(0.75));
		Mat _complexim;
		complexIm.copyTo(_complexim);//把变换结果复制一份，进行逆变换，也就是恢复原图
		Mat iDft[]={Mat::zeros(plane[0].size(),CV_32F),Mat::zeros(plane[0].size(),CV_32F)};//创建两个通道，类型为float，大小为填充后的尺寸
		idft(_complexim,_complexim);//傅立叶逆变换
		split(_complexim,iDft);//结果貌似也是复数
		magnitude(iDft[0],iDft[1],iDft[0]);//分离通道，主要获取0通道
		normalize(iDft[0],iDft[0],1,0,CV_MINMAX);//归一化处理，float类型的显示范围为0-1,大于1为白色，小于0为黑色
		imshow("idft",iDft[0]);//显示逆变换
		waitKey(0);


		plane[0]+=Scalar::all(1);//傅立叶变换后的图片不好分析，进行对数处理，结果比较好看
		log(plane[0],plane[0]);
		normalize(plane[0],plane[0],1,0,CV_MINMAX);

		imshow("dft",plane[0]);
		waitKey(0);
}

//test2(): 离散傅里叶变换和逆变换
void test2()
{
	cout << "test1(): 离散傅里叶变换和逆变换。" << endl << endl;

	cout << "数值矩阵的DFT，以及IDFT复原演示：" << endl;
	Mat_<float> temp[2];
	temp[0] = (Mat_<float>(3,4) << 1,2,3,4,5,6,7,8,9,10,11,12);
	temp[1] = Mat_<float>::zeros(temp[0].rows, temp[0].cols);
	Mat f;
	Mat F;
	merge(temp,2,f);
	dft(f,F);
	split(F,temp);
	cout << "f = \n" << f << endl;
	cout << "f的频谱的实部：\n" << temp[0] << endl;
	cout << "f的频谱的虚部：\n" << temp[1] << endl;
	Mat f_restored;
	idft(F,f_restored);
	f_restored = f_restored/(f_restored.rows*f_restored.cols);			//!!!!!!
	cout << "傅里叶逆变换复原的矩阵：\n" << f_restored << endl;


	cout << "图片的DFT，以及IDFT复原演示：" << endl;
	Mat src = imread("lena.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("original image",src);
	waitKey(0);

	temp[0] = src;
	temp[1] = Mat::zeros(src.rows,src.cols,CV_8UC1);
	Mat space;
	Mat frequency;
	Mat space_res;
	merge(temp,2,space);
	dft(space,frequency);
	idft(frequency,space_res);
	space_res = space_res/(space_res.rows*space_res.cols);

	split(frequency,temp);
	Mat real_frequency = temp[0];
	imshow("real frequency", real_frequency);
	waitKey(0);

	split(space_res,temp);
	Mat dst = temp[0];
	dst = Mat_<double>(dst);
	double minVal;
	double maxVal;
	int minIdx[2];
	int maxIdx[2];
	minMaxIdx(dst,&minVal,&maxVal,minIdx,maxIdx);
	dst = dst/maxVal;
	imshow("restored image",dst);		//原图→dft→idft
	waitKey(0);



}


int main()
{
	//test1();
	test2();
	//test3();


	return 0;
}
