#include "cMat.h"

#ifndef SRC_GISYSTEM_H_
#define SRC_GISYSTEM_H_

class GIsystem
{public:
	//构造函数、析构函数
	GIsystem();

	//set/get方法。
	void setBeta(float beta);								//修改采样率beta；
	double getK();
	cMat geth11();
	cMat geth12();

	//光场采样：
	Mat_<double> detectLightFiled();						//探测光场，输出A矩阵。

	//分析光场数据：
	Mat generateSpeckleFig(Mat_<double> A);					//返回采得的第一幅散斑场矩阵，元素为unchar
	Mat_<double> generateG2(Mat_<double> A);				//由A矩阵计算出G2矩阵

	//图像重构：
	Mat_<uchar> GIreconstruction(Mat_<double> A);			//GI线性重构算法，输出GI矩阵。
	Mat_<uchar> GPSR_BBreconstruction(Mat_<double> A);		//GPSR_BB重构算法，输出GISC矩阵。


protected:
	int beta;
	int K;
	cMat h11;
	cMat h12;

	static double lamda;
	static double k;

	static double z;

	static double L;
	static int MS;
	static double dS;

	static double Lp;

	static double L_detect;
	static int MD;
	static double dD;
	static int N;

	static double deltaX;
	static int N_speckle;


};



//实现部分：

//static成员数据初始化。
double GIsystem::lamda = 660e-9;
double GIsystem::k = 2*pi/lamda;

double GIsystem::z = 10;					    //光源到探测面的距离

double GIsystem::L = 6e-3;
int GIsystem::MS = 60;
double GIsystem::dS = L/MS;                	    //划分布阵空间/光源面的步长

double GIsystem::Lp = lamda*z/dS;     	 	    //有效成像周期

double GIsystem::L_detect = 0.2*Lp;             //光场探测面/物面尺寸
int GIsystem::MD = 330;                      //光场探测面/物面一个维度上的步数
double GIsystem::dD = L_detect/MD;              //接收平面步长，取决于相机的像素尺寸。
int GIsystem::N = MD*MD;

double GIsystem::deltaX = lamda*z/L; 		    //探测面/物面上散斑平均尺寸。透镜焦距越大，光源尺寸越小，散斑尺寸越大。
int GIsystem::N_speckle = round(pow(L_detect/deltaX,2));   //探测面上散斑数。



//构造函数、析构函数
GIsystem::GIsystem():beta(1)
{
	this->K = round(N_speckle*beta);

	this->h11 = cMat(MD,MS);
	for(double m = 0; m<= MD-1; m++)
	{
		for(double n = 0; n<=MS-1; n++)
		{
			double real = cos(pi/(lamda*z)*pow(dD*(m-round(MD/2.0))-dS*(n-round(MS/2.0)),2));
			double imag = sin(pi/(lamda*z)*pow(dD*(m-round(MD/2.0))-dS*(n-round(MS/2.0)),2));
			this->h11.assign(m,n,real,imag);
		}
	}

	this->h12 = cMat(MS,MD);
	for(double m = 0; m<=MS-1; m++)
	{
		for(double n = 0; n<=MD-1; n++)
		{
			double real = cos(pi/(lamda*z)*pow(dD*(m-round(MS/2.0))-dS*(n-round(MD/2.0)),2));
			double imag = sin(pi/(lamda*z)*pow(dD*(m-round(MS/2.0))-dS*(n-round(MD/2.0)),2));
			this->h12.assign(m,n,real,imag);
		}
	}

}


//set/get方法
void GIsystem::setBeta(float beta)
{
	//当beta<=0时抛出异常。
	this->beta = beta;
	this->K = round(N_speckle*beta);

}

double GIsystem::getK()
{
	double K = this->K;
	return K;
}

cMat GIsystem::geth11()
{
	cMat temp = this->h11;
	return temp;
}

cMat GIsystem::geth12()
{
	cMat temp = this->h12;
	return temp;
}


//光场采样
Mat_<double> GIsystem::detectLightFiled()
{
	vector<Mat> v;
	for(int k = 1;k<=(this->K);k++)
	{
		Mat_<double> temp(MS,MS);
		cv::randu(temp,0,1);

		cMat e(MS,MS);
		cMat::exp_i2pi(temp,e);

		cMat S = cMat::ones(MS,MS);
		cMat::randu(S,0,1);
		S = S.mul(e);


		cMat Er = (this->h11)*S*(this->h12);
		cMat cEr = cMat::conj(Er);
		cMat cIr_k = Er.mul(cEr);
		Mat_<double> Ir_k = cIr_k.getREAL();		//MD*MD


		Ir_k = Ir_k.reshape(0,1);					//拉成行向量。1*N
		v.push_back(Ir_k);
	}
	Mat_<double> A = Mat_<double>();
	vconcat(v,A);

	return A;										//K*N
}


//分析光场数据：
Mat GIsystem::generateSpeckleFig(Mat_<double> A)
{
	Mat_<double> a = A(Range(0,1),Range::all());
	double minVal;
	double maxVal;
	minMaxIdx(a,&minVal,&maxVal);
	a = a/maxVal*255;
	Mat_<uchar> b;
	a.convertTo(b,CV_8UC1);
	b = b.reshape(0,MD);
	cout << "a.size = " << a.size << endl;
	cout << "b.size = " << b.size << endl;

	return b;
}

Mat_<double> GIsystem::generateG2(Mat_<double> A)
{
	Mat_<double> g2;
	int center = MD*round(MD/2.0)+round(MD/2.0);
	Mat_<double> Ir_0 = A(Range::all(),Range(center,center+1));				//K*1
	Ir_0 = repeat(Ir_0,1,N);												//K*N


	return g2;						//return G2;
}


//图像重构：
Mat_<uchar> GIsystem::GIreconstruction(Mat_<double> A)
{
	Mat_<uchar> X = imread("/Users/wuhan/Downloads/imagingObject.bmp",0);	//MD*MD
	X = X.reshape(0,N);				    			//N*1
	Mat_<double> x = (Mat_<double>)X;
	Mat_<double> y = A*x;							//K*1
	transpose(y,y);									//1*K

	Mat_<double> A_avg;								//1*N
	reduce(A,A_avg,0,1);
	double y_avg = sum(y)(0)/y.cols;
	double K = (double)(this->K);
	Mat_<double> GI = y*A/K-y_avg*A_avg;			//1*N
	GI = GI.reshape(0,MD);							//MD*MD
	double maxGI,minGI;
	minMaxIdx(GI,&minGI,&maxGI);
	GI = GI/maxGI*255;
	GI = (Mat_<uchar>)GI;


	return GI;									//return GI;
}

Mat_<uchar> GIsystem::GPSR_BBreconstruction(Mat_<double> A)
{
	Mat_<uchar> GISC;

	return GISC;
}





#endif /* SRC_GISYSTEM_H_ */
