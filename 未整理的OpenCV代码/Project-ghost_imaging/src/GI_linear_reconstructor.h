/*
 */

#include "cMat.h"
#include <iostream>
#include <fstream>

#ifndef SRC_GI_LINEAR_RECONSTRUCTOR_H_
#define SRC_GI_LINEAR_RECONSTRUCTOR_H_

class GI_linear_reconstructor
{
public:
	// 构造、析构函数
	GI_linear_reconstructor(int, int);		// 输入参数为MD,ND

	// get、set方法
	cv::Mat_<double> getImage();

	// 图像重构方法。
	cv::Mat_<double> GIreconstruct(cv::Mat_<double> A, cv::Mat_<double> y);

	// 保存数据的方法。
	void saveImage();

protected:
	int MD,ND;								// 重构图像的横纵像素数。
	cv::Mat_<double> image;					// 重构出的图像

};





//实现部分：
GI_linear_reconstructor::GI_linear_reconstructor(int MD, int ND)
{
	this->MD = MD;
	this->ND = ND;
	this->image = cv::Mat_<double>::zeros(MD,ND);
}

cv::Mat_<double> GI_linear_reconstructor::getImage()
{
	return this->image;
}

cv::Mat_<double> GI_linear_reconstructor::GIreconstruct(cv::Mat_<double> A, cv::Mat_<double> y)
{
	int K = A.rows;

	cv::transpose(y,y);									//1*K

	cv::Mat_<double> A_avg;								//1*N_pixel
	cv::reduce(A,A_avg,0,1);

	double y_avg = sum(y)(0)/y.cols;

	cv::Mat_<double> GI = y*A/K-y_avg*A_avg;			//1*N
	GI = GI.reshape(0,MD);							//MD*MD

	double maxGI,minGI;
	minMaxIdx(GI,&minGI,&maxGI);
	GI = GI/maxGI;

	this->image = GI.clone();
	return GI;									//return GI;
}

void GI_linear_reconstructor::saveImage()
{
	cv::Mat temp = this->image.clone();
	temp = abs(temp);
	double max,min;
	minMaxIdx(temp,&min,&max);
	temp = temp/max*255;
	temp.convertTo(temp,CV_8UC1);
	imwrite("/Users/wuhan/Downloads/GI_linear_reconstruct_result.bmp",temp);
}




#endif /* SRC_GI_LINEAR_RECONSTRUCTOR_H_ */
