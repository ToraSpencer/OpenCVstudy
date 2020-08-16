/* 读取探测信号向量y，测量矩阵A，使用GPSR_BB算法恢复原始信号向量x
 */

#include "cMat.h"

#ifndef SRC_GPSR_BB_RECONSTRUCTOR_H_
#define SRC_GPSR_BB_RECONSTRUCTOR_H_


class GPSR_BB_reconstructor
{
public:
	// 构造、析构函数
	GPSR_BB_reconstructor(int, int, double);		// 输入参数为MD,ND,tau

	// get、set方法
	cv::Mat_<double> getImage();

	// 图像重构方法。
	cv::Mat_<double> GPSR_BB_reconstruct(cv::Mat_<double> A, cv::Mat_<double> y);

	// 保存数据的方法。
	void saveImage();

protected:
	int MD,ND;								// 重构图像的横纵像素数。
	double tau;								// 无约束凸优化模型中的参数： 0.5*|| y - A x ||_2^2 + tau || x ||_1
	cv::Mat_<double> image;					// 重构出的图像

};


// 实现部分：
GPSR_BB_reconstructor::GPSR_BB_reconstructor(int MD, int ND, double tau): MD(MD),ND(ND),tau(tau)
{
	this->image = cv::Mat_<double>::zeros(MD,ND);
}

cv::Mat_<double> GPSR_BB_reconstructor::getImage()
{
	return this->image;
}

cv::Mat_<double> GPSR_BB_reconstructor::GPSR_BB_reconstruct(cv::Mat_<double> A, cv::Mat_<double> y)
{
	cv::Mat_<double> gisc, x, u, v, y_prime, temp, temp1, temp2, temp3, term, gradu, gradv, du, dv, dx, dy, old_u, old_v, uvmin, w;
	cv::Mat x_positive, x_negative;
	double dGd, lambda0, lambda, criterion, dd, tempNum;
	double* pd = nullptr;

	// 设置一些常数参量。
	int maxIter = 2000;   					// 最大迭代次数。
	double realmin = 1e-100;
	double tolerance = 1e-5;				// 截止阈值
	double alphamin = 1e-30;				// 步长alpha最小值
	double alphamax = 1e30;					// 步长alpha最大值。


	// 预先计算算法中经常要用到的中间变量：
	cv::Mat_<double> Aty = cv::transpose(A)*y;

	// 初始化输出向量x, u, v;
	x = cv::transpose(A)*cv::Mat_<double>::zeros(y.rows, y.cols);

	x_positive = x>=0;
	x_positive.convertTo(x_positive,CV_64FC1);
	x_positive = x_positive/255;
	x_negative = x<0;
	x_negative.convertTo(x_negative,CV_64FC1);
	x_negative = x_negative/255;

	u = x.mul(x_positive);
	v = -x.mul(x_negative);


	// 初始化一些中间变量：
	int iterCount = 1;
	bool keep_going = true;
	double alpha = 1;
	y_prime = A*x;

	// 迭代主体：
	while(keep_going)
	{

		if(iterCount%10 == 0)
		{
			std::printf("%d times iteration has been finished\n", iterCount);
		}

		// 计算梯度
	    temp = transpose(A) * y_prime;
	    term  =  temp - Aty;
	    gradu =  term + tau;			// gradu = A'*y_prime - Aty + tau;
	    gradv = -term + tau;			// gradv = -A'*y_prime + Aty + tau;

	    du = cv::max(u - alpha*gradu, 0, 0) - u;
	    dv = cv::max(v - alpha*gradv, 0, 0) - v;
	    dx = du-dv;
	    old_u = u;
	    old_v = v;
	    dy = A*dx;
	    dGd = cv::norm2(dy);
	    dGd = dGd*dGd;						// dy的L2范数的平方。

	    // 参数lamda的计算
	    temp = cv::transpose(gradu)*du + cv::transpose(gradv)*dv;
	    pd = temp.ptr<double>(0,0);
	    lambda0 = -*pd/(realmin+dGd);
	    lambda = std::min(lambda0,1.0);

	    // 重构信号向量x的计算
	    u = old_u + lambda * du;
	    v = old_v + lambda * dv;
	    uvmin = cv::min(u,v);
	    u = u - uvmin;
	    v = v - uvmin;
	    x = u - v;

	    y_prime = y_prime + lambda*dy;

	    // alpha的计算：
	    dd = cv::norm2(du)*cv::norm2(du)+cv::norm2(dv)*cv::norm2(dv);
	    alpha = cv::min(alphamax, cv::max(alphamin,dd/dGd));

	    // 迭代终止判断：
		temp1 = cv::min(gradu.reshape(0,1), old_u.reshape(0,1));
		temp2 = cv::min(gradv.reshape(0,1), old_v.reshape(0,1));
		cv::vconcat(temp1,temp2,w);
		tempNum = std::max(1e-6, cv::normInf(old_u.reshape(0,old_u.rows*old_u.cols)));
		tempNum = std::max(tempNum,cv::normInf(old_v.reshape(0,old_v.rows*old_v.cols)));
		criterion = cv::normInf(w.reshape(0, w.rows*w.cols))/tempNum;
		keep_going = (criterion > tolerance);

	    // 更新迭代次数，保存数据。
	    iterCount = iterCount + 1;

	    // 迭代次数超出设定最大次数时，停止循环。
	    if(iterCount > maxIter){keep_going = false;}
	}

	temp = temp.reshape(0,MD);							//MD*MD

	double maxVal,minVal;
	minMaxIdx(temp, &minVal, &maxVal);
	temp = temp/maxVal;

	this->image = temp.clone();
	return temp;									//return GI;

	std::printf("\nfinished");
}

void GPSR_BB_reconstructor::saveImage()
{
	cv::Mat temp = this->image.clone();
	temp = abs(temp);
	double max,min;
	minMaxIdx(temp,&min,&max);
	temp = temp/max*255;
	temp.convertTo(temp,CV_8UC1);
	imwrite("/Users/wuhan/Downloads/GPSR_BB_reconstruct_result.bmp",temp);
}





#endif /* SRC_GPSR_BB_RECONSTRUCTOR_H_ */
