/*
 */

#include "cMat.h"
#include <iostream>
#include <fstream>

#ifndef SRC_GISYSTEM_H_
#define SRC_GISYSTEM_H_

class GIsystem
{public:
	//构造、析构函数
	GIsystem(cv::Mat_<double> obj);

	//get/set方法
	int getMD();
	int getND();
	cv::Mat_<double> getX();
	cv::Mat_<double> getA();
	cv::Mat_<double> getY();

	//输出、保存数据的方法
	void systemInfo();							//输出成像系统信息。
	cv::Mat_<double> generateG2();
	void saveA();
	void saveX();
	void saveY();

protected:
	//用户自己输入的数据，和可以自己可以设置的参数：
	cv::Mat_<double> obj;
	double beta;
	double LS;
	double dS;
	double dD;



	//从属于自设定系统参数，或static成员数据的成员数据：
	int MS;
	int NS;
	double deltaX;                         		//散斑平均尺寸：deltaX = lambda*z/LS;
	double Lp;                            		//有效成像周期，物面尺寸应该小于此尺寸。Lp = lambda/dS*z;
	int MD;
	int ND;
	double width_D;
	double height_D;
	int	N_pixel;                         		//物面（Dr面）像素数：N_pixel = MD*ND;
	int M_speckle;           					//物面y方向上的散斑数：M_speckle = round(height/deltaX);
	int N_speckle;           				    //物面x方向上的散斑数：N_speckle = round(width/deltaX);
	int num_speckle;                  			//物面散斑总数：num_speckle = M_speckle*N_speckle;
	int K;             							//采样数：K = round(num_speckle*beta);
	cv::cMat h11;
	cv::cMat h12;
	cv::Mat_<double> x;
	cv::Mat_<double> A;
	cv::Mat_<double> y;

	//static成员数据：
	static double lambda;
	static double k;
	static double z;							//光源到物面的距离，要保证是远场。

};



//实现部分：


//static成员数据初始化：
double GIsystem::lambda = 550e-9;
double GIsystem::k = 2*pi/lambda;
double GIsystem::z = 10;


//构造、析构方法
GIsystem::GIsystem(cv::Mat_<double> obj)
{
	this->obj = obj;
	this->beta = 5;
	this->LS = 5e-3;
	this->dS = 1e-4;
	this->dD = 5e-5;
	this->MS = round(LS/dS);
	this->NS = MS;
	this->deltaX = lambda*z/LS;                         		//散斑平均尺寸
	this->Lp = lambda*z/dS;                            			//有效成像周期，物面尺寸应该小于此尺寸。
	this->MD = obj.rows;
	this->ND = obj.cols;
	this->width_D = MD*dD;
	this->height_D = ND*dD;
	this->N_pixel = MD*ND;                         				//物面（Dr面）像素数：
	this->M_speckle = round(height_D/deltaX);          			//物面y方向上的散斑数：
	this->N_speckle = round(width_D/deltaX);          			//物面x方向上的散斑数：
	this->num_speckle = M_speckle*N_speckle;                  	//物面散斑总数：
	this->K = round(num_speckle*beta);             				//采样数：

	std::complex<double> a,c;

	this->h11 = cv::cMat(MD,MS);
	for(double m = 0; m<= MD-1; m++)
	{
		for(double n = 0; n<=MS-1; n++)
		{
			a = std::complex<double>(0,(pi/(lambda*z))*pow(((m-round(MD/2))*dD-((n-round(MS/2))*dS)),2));
			c = std::exp(a);
			this->h11.assign(m,n,c);
		}
	}

	this->h12 = cv::cMat(NS,ND);
	for(double m = 0; m<=NS-1; m++)
	{
		for(double n = 0; n<=ND-1; n++)
		{
			a = std::complex<double>(0,(pi/(lambda*z))*pow(((m-round(NS/2))*dS-((n-round(ND/2))*dD)),2));
			c = std::exp(a);
			this->h12.assign(m,n,c);
		}
	}

	this->x = obj.reshape(0,N_pixel);

	this->A = cv::Mat_<double>();
	std::vector<cv::Mat> v;
	for(int k = 1;k<=(this->K);k++)
	{
		cv::Mat_<double> temp(MS,NS);
		cv::randu(temp,0,1);

		cv::cMat e(MS,NS);
		cv::exp_i2pi(temp,e);

		cv::cMat S = cv::cMat::ones(MS,NS);						//光源面的光场复振幅分布。
		cv::randu(S,0,1);
		S = S.mul(e);

		cv::cMat Er = (this->h11)*S*(this->h12);			//物面(Dr面)的光场复振幅分布。
		cv::cMat cEr = cv::conj(Er);
		cv::cMat cIr_k = Er.mul(cEr);
		cv::Mat_<double> Ir_k = cIr_k.REAL;		     	//物面(Dr面)的光场强度分布。

		Ir_k = Ir_k.reshape(0,1);						//拉成行向量。1*N_pixel
		v.push_back(Ir_k);
	}
	cv::vconcat(v,this->A);									//K次采样积累的Ir_k行向量串联成A矩阵。K*N_pixel

	this->y = this->A*this->x;
}

//get/set方法
int GIsystem::getMD()
{
	return this->MD;
}

int GIsystem::getND()
{
	return this->ND;
}

cv::Mat_<double> GIsystem::getX()
{
	return this->x;
}

cv::Mat_<double> GIsystem::getA()
{
	return this->A;
}

cv::Mat_<double> GIsystem::getY()
{
	return this->y;
}

//输出数据的方法
void GIsystem::systemInfo(){}

void GIsystem::saveA()
{
	std::ofstream outfile("/Users/wuhan/Downloads/A",std::ios::binary);
	outfile.write(reinterpret_cast<char*>(&this->A),sizeof(this->A));
	outfile.close();
}

void GIsystem::saveX()
{
	std::ofstream outfile("/Users/wuhan/Downloads/x",std::ios::binary);
	outfile.write(reinterpret_cast<char*>(&this->x),sizeof(this->x));
	outfile.close();
}

void GIsystem::saveY()
{
	std::ofstream outfile("/Users/wuhan/Downloads/y",std::ios::binary);
	outfile.write(reinterpret_cast<char*>(&this->y),sizeof(this->y));
	outfile.close();
}


#endif /* SRC_GISYSTEM_H_ */
