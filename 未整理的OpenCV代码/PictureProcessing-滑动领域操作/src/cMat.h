//最后更新于2019.4.10下午
#include <opencv2/opencv.hpp>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;
using namespace cv;

#define pi 3.14159

#ifndef SRC_CMAT_H_
#define SRC_CMAT_H_

//复数矩阵类
class cMat
{public:
	int rows;
	int cols;
	Mat_<double> REAL;
	Mat_<double> IMAG;
	Size size;

	//构造函数、析构函数。
	cMat();
	cMat(int ro,int co);
	cMat(Mat_<double> RE, Mat_<double> IM);					//输入实部和虚部矩阵构造复数矩阵。
	cMat(int ro,int co,double real,double imag);			//生成元素全为(real,imag)的复数矩阵。
	cMat(int ro, int co, double* pa, double* pb);			//输入二维数组的指针构造复数矩阵。
	cMat(const Mat& M);										//输入普通矩阵，构造复数矩阵，虚部为0。
	cMat(const cMat& cM);									//拷贝构造函数。
	~cMat();

	//get/set方法，访问/修改矩阵元素的方法。
	complex<double> at(int ro,int co);
	void assign(int ro,int co,complex<double> z);			//元素赋值函数
	void assign(int ro,int co,double real,double imag);

	//生成特殊复数矩阵的方法。
	cMat static zeros(int ro, int co);
	cMat static ones(int ro, int co);
	cMat static eye(int ro, int co);

	//重载运算符。
	friend ostream& operator<<(ostream &os, cMat &cM);		//重载运算符<<使其可以输出复数矩阵。
	void operator=(const cMat &cM);							//重载赋值运算符。
	cMat operator+(const cMat &cM);								//重载加法
	cMat operator-(const cMat &cM);								//重载减法
	cMat operator*(const cMat &cM);								//重载乘法
	cMat operator*(const uchar &a);								//和uchar常数的乘法
	cMat operator*(const int &a);								//和int常数的乘法
	cMat operator*(const float &a);								//和float常数的乘法
	cMat operator*(const double &a);							//和double常数的乘法
	cMat operator/(const uchar &a);
	cMat operator/(const int &a);
	cMat operator/(const float &a);
	cMat operator/(const double &a);

	//重载Mat的方法。
	cMat clone() const;
	cMat mul(const cMat& cM);								//矩阵按元素相乘。
	cMat mul(const Mat& M);									//和普通Mat按元素相乘
	cMat static conj(const cMat& cM);						//！！！将复数矩阵转换为其复共轭。
	void reshape(int ro);									//矩阵整形。


protected:



};

//重载cv函数：
cMat imread(const String& filename);				//限定读取图片转为灰度数据。
void imshow(const string&, cMat&);
void transpose(cMat&, cMat&);
void dft(cMat&,cMat&);
void idft(cMat&,cMat&);
void dftshift(cMat&);								//零频移到中心：交换矩阵的一三象限、二四象限。
void idftshift(cMat&);
cMat abs(cMat&);
Mat_<double> cos(Mat&);
Mat_<double> sin(Mat&);
cMat cos(Mat&);
cMat sin(Mat&);
void randu(cMat& cM, double low, double high);
void exp(const Mat_<double>& M, cMat& cM);			//返回exp(M)的复数矩阵;
void exp(const cMat& M, cMat& cM);					//返回exp(M)的复数矩阵;
void exp_i2pi(const Mat_<double>& M, cMat& cM);		//返回exp(1j*2*pi*M)的复数矩阵;

//自定义的方便用于科学计算的矩阵函数：
Mat_<double> sqrt(const Mat_<double>&);
Mat_<double> stepVector(double,double,double);	//用于创建元素间隔相等的行向量。
Mat_<double> stepVector(double,double,int);		//用于创建元素间隔相等的行向量。
Mat_<double> circ(const Mat_<double>& r);
Mat_<double> acos(const Mat_<double>&);
void meshgrid(Mat_<double>&,Mat_<double>&,double,double,double,double,double,double);
void meshgrid(Mat_<double>&,Mat_<double>&,double,double,int,double,double,int);
void replaceInfAndNan(Mat_<double>&);





//实现部分：

//构造函数和析构函数
cMat::cMat()
{
	this->rows = 0;
	this->cols = 0;
	this->REAL = Mat_<double>();
	this->IMAG = Mat_<double>();
	this->size = (this->REAL).size();
}

cMat::cMat(int ro,int co)
{
	this->rows = ro;
	this->cols = co;
	this->REAL = Mat_<double>(ro,co);
	this->IMAG = Mat_<double>(ro,co);
	this->size = (this->REAL).size();
}

cMat::cMat(Mat_<double> RE, Mat_<double> IM)
{
	//检查RE和IM是否尺寸相等，不相等则抛出异常。
	this->rows = RE.rows;
	this->cols = RE.cols;
	this->REAL = RE;
	this->IMAG = IM;
	this->size = (this->REAL).size();
}

cMat::cMat(int ro,int co,double real,double imag)
{
	this->rows = ro;
	this->cols = co;
	Mat_<double> O = Mat_<double>::ones(ro,co);
	this->REAL = real*O;
	this->IMAG = imag*O;
	this->size = (this->REAL).size();
}

cMat::cMat(int ro, int co, double* pa, double* pb)
{
	this->rows = ro;
	this->cols = co;
	Mat_<double> REAL = Mat_<double>::zeros(ro,co);
	Mat_<double> IMAG = Mat_<double>::zeros(ro,co);
	double* pR = REAL.ptr<double>(0);
	double* pI = IMAG.ptr<double>(0);

	for(int i = 0;i<=co*ro-1;i++)
	{
		*pR = *pa;
		*pI = *pb;
		pa++;
		pb++;
		pR++;
		pI++;
	}

	this->REAL = REAL;
	this->IMAG = IMAG;
	this->size = (this->REAL).size();
}

cMat::cMat(const Mat& M)
{
	Mat MM;
	M.convertTo(MM,CV_64FC1);
	this->rows = MM.rows;
	this->cols = MM.cols;
	this->REAL = MM;
	this->IMAG = Mat_<double>::zeros(MM.size());
	this->size = MM.size();
}

cMat::cMat(const cMat& cM)
{
	this->rows = cM.rows;
	this->cols = cM.cols;
	this->REAL = cM.REAL;
	this->IMAG = cM.IMAG;
	this->size = (this->REAL).size();
}

cMat::~cMat()
{}


//get/set方法，和访问/修改矩阵元素的方法。
complex<double> cMat::at(int ro,int co)
{
	double real = this->REAL(ro,co);
	double imag = this->IMAG(ro,co);
	complex<double> z(real,imag);

	return z;
}

void cMat::assign(int ro,int co,complex<double> z)
{
	this->REAL(ro,co) = z.real();
	this->IMAG(ro,co) = z.imag();
}

void cMat::assign(int ro,int co,double real,double imag)
{
	this->REAL(ro,co) = real;
	this->IMAG(ro,co) = imag;
}



//生成特殊复数矩阵的方法。
cMat cMat::zeros(int ro, int co)
{
	cMat* p = NULL;
	p = new cMat();
	Mat_<double> REAL = Mat_<double>::zeros(ro,co);
	Mat_<double> IMAG = Mat_<double>::zeros(ro,co);
	p->rows = ro;
	p->cols = co;
	p->REAL = REAL;
	p->IMAG = IMAG;
	p->size = REAL.size();

	return *p;
}

cMat cMat::ones(int ro, int co)
{
	cMat* p = NULL;
	p = new cMat();
	Mat_<double> REAL = Mat_<double>::ones(ro,co);
	Mat_<double> IMAG = Mat_<double>::ones(ro,co);
	p->rows = ro;
	p->cols = co;
	p->REAL = REAL;
	p->IMAG = IMAG;
	p->size = REAL.size();

	return *p;
}

cMat cMat::eye(int ro, int co)
{
	//ro和co不相等时抛出异常。
	cMat* p = NULL;
	p = new cMat();
	Mat_<double> REAL = Mat_<double>::eye(ro,co);
	Mat_<double> IMAG = Mat_<double>::eye(ro,co);
	p->rows = ro;
	p->cols = co;
	p->REAL = REAL;
	p->IMAG = IMAG;
	p->size = REAL.size();

	return *p;

}



//重载运算符
ostream& operator<<(ostream &os, cMat &cM)		//重载<<
{
	for(int i = 0; i<=cM.rows-1; i++)
		{for(int j = 0; j<=cM.cols-1;j++)
			{
				complex<double> z = cM.at(i,j);
				os << z << " ";
				if((i*cM.cols+j+1)%cM.cols==0){os << "\n";}
			}
		}

	return os;
}

void cMat::operator=(const cMat &cM)
{
	int rows = cM.rows;
	int cols = cM.cols;
	this->rows = rows;
	this->cols = cols;
	this->REAL = cM.REAL;
	this->IMAG = cM.IMAG;
	this->size = (this->REAL).size();

}

cMat cMat::operator+(const cMat &cM)					//重载加法
{
	Mat_<double> REAL = this->REAL+cM.REAL;
	Mat_<double> IMAG = this->IMAG+cM.IMAG;
	cMat temp(REAL,IMAG);
	return temp;
}

cMat cMat::operator-(const cMat &cM)					//重载减法
{
	Mat_<double> REAL = this->REAL-cM.REAL;
	Mat_<double> IMAG = this->IMAG-cM.IMAG;
	cMat temp(REAL,IMAG);
	return temp;
}

cMat cMat::operator*(const cMat &cM)					//重载乘法
{
	//this->cols != cM.rows时，抛出异常。
	Mat_<double> RE;
	Mat_<double> IM;
	RE = (this->REAL)*(cM.REAL)-(this->IMAG)*(cM.IMAG);
	IM = (this->REAL)*(cM.IMAG)+(this->IMAG)*(cM.REAL);
	cMat temp(RE,IM);

	return temp;
}

cMat cMat::operator*(const uchar &a)								//和uchar常数的乘法
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const int &a)								//和int常数的乘法
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const float &a)								//和float常数的乘法
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const double &a)							//和double常数的乘法
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const uchar &a)
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const int &a)
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const float &a)
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const double &a)
{
	Mat_<double> RE;
	Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

//	重载Mat的方法
cMat cMat::clone() const
{
	Mat_<double> RE,IM;
	RE = this->REAL.clone();
	IM = this->IMAG.clone();
	cMat cM(RE,IM);
	return cM;
}

cMat cMat::mul(const cMat& cM)    				    //(r1,i1)*(r2,i2) = (r1*r2-i1*i2,r1*i2+i1*r2)
{
	//前面需要检查AB尺寸是否相等，不相等则抛出异常。
	Mat_<double> RE;
	Mat_<double> IM;
	RE = (this->REAL).mul(cM.REAL)-(this->IMAG).mul(cM.IMAG);
	IM = (this->REAL).mul(cM.IMAG)+(this->IMAG).mul(cM.REAL);
	cMat temp(RE,IM);

	return temp;
}

cMat cMat::mul(const Mat& M)
{
	//前面需要检查AB尺寸是否相等，不相等则抛出异常。
	Mat_<double> RE;
	Mat_<double> IM;
	RE = (this->REAL).mul(M);
	IM = (this->IMAG).mul(M);
	cMat temp(RE,IM);

	return temp;
}

cMat cMat::conj(const cMat& cM)
{
	cMat* p = NULL;
	p = new cMat();
	p->rows = cM.rows;
	p->cols = cM.cols;
	p->REAL = cM.REAL;
	p->IMAG = -cM.IMAG;
	p->size = cM.size;

	return *p;
}

void cMat::reshape(int ro)
{
	//当this->rows*this->cols不能被ro整除时抛出异常。
	Mat_<double> REAL = this->REAL.reshape(0,ro);
	Mat_<double> IMAG = this->IMAG.reshape(0,ro);
	this->cols = (int)((this->rows)*(this->cols)/ro);
	this->rows = ro;

	this->REAL = REAL;
	this->IMAG = IMAG;
	this->size = REAL.size();

}



// 重载cv函数：
cMat imread(const String& filename)
{
	Mat M = cv::imread(filename, COLOR_BGR2GRAY);
	cMat cM = cMat(M);
	return cM;
}

void transpose(cMat& src, cMat& dst)
{
	transpose(src.REAL, dst.REAL);
	transpose(src.IMAG, dst.IMAG);
}

void imshow(const string& str, cMat& cM)
{
	Mat RE;
	cM.REAL.convertTo(RE,CV_8UC1);
	cv::imshow(str, RE);
}

void dft(cMat& src, cMat& dst)
{
	Mat_<float> temp[2];
	Mat f,F;
	temp[0] = src.REAL;
	temp[1] = src.IMAG;
	merge(temp,2,f);
	cv::dft(f,F);
	split(F,temp);
	cMat cM = cMat(temp[0], temp[1]);
	dst = cM.clone();
}

void idft(cMat& src, cMat& dst)
{
	Mat_<float> temp[2];
	Mat f,F;
	temp[0] = src.REAL;
	temp[1] = src.IMAG;
	merge(temp,2,F);
	cv::idft(F,f);
	split(f,temp);
	cMat cM = cMat(temp[0], temp[1]);
	dst = cM.clone();
	dst = dst/(dst.rows*dst.cols);
}

void dftshift(cMat& cM)
{
	int Or,Oc,M,N;
	Mat_<double> A,B,C,D,temp,temp1,temp2;
	M = cM.rows;
	N = cM.cols;
	Or = ceil(M/2.0);
	Oc = ceil(N/2.0);
	A = cM.REAL(Rect(0,0,Oc,Or));
	D = cM.REAL(Rect(Oc,Or,N-Oc,M-Or));
	B = cM.REAL(Rect(Oc,0,N-Oc,Or));
	C = cM.REAL(Rect(0,Or,Oc,M-Or));
	hconcat(D,C,temp1);
	hconcat(B,A,temp2);
	vconcat(temp1,temp2,cM.REAL);


	A = cM.IMAG(Rect(0,0,Oc,Or));
	D = cM.IMAG(Rect(Oc,Or,N-Oc,M-Or));
	B = cM.IMAG(Rect(Oc,0,N-Oc,Or));
	C = cM.IMAG(Rect(0,Or,Oc,M-Or));
	hconcat(D,C,temp1);
	hconcat(B,A,temp2);
	vconcat(temp1,temp2,cM.IMAG);

}

void idftshift(cMat& cM)
{
	int Or,Oc,M,N;
	Mat_<double> A,B,C,D,temp,temp1,temp2;
	M = cM.rows;
	N = cM.cols;
	Or = floor(M/2.0);
	Oc = floor(N/2.0);
	A = cM.REAL(Rect(0,0,Oc,Or));
	D = cM.REAL(Rect(Oc,Or,N-Oc,M-Or));
	B = cM.REAL(Rect(Oc,0,N-Oc,Or));
	C = cM.REAL(Rect(0,Or,Oc,M-Or));
	hconcat(D,C,temp1);
	hconcat(B,A,temp2);
	vconcat(temp1,temp2,cM.REAL);

	A = cM.IMAG(Rect(0,0,Oc,Or));
	D = cM.IMAG(Rect(Oc,Or,N-Oc,M-Or));
	B = cM.IMAG(Rect(Oc,0,N-Oc,Or));
	C = cM.IMAG(Rect(0,Or,Oc,M-Or));
	hconcat(D,C,temp1);
	hconcat(B,A,temp2);
	vconcat(temp1,temp2,cM.IMAG);
}

cMat abs(cMat& cM)
{
	cMat temp = cM.clone();
	temp.REAL = sqrt(temp.REAL.mul(temp.REAL)+temp.IMAG.mul(temp.IMAG));
	temp.IMAG = Mat_<double>::zeros(temp.rows,temp.cols);
	return temp;
}

Mat_<double> cos(Mat& M)
{
	Mat N = M.clone();
	for(int i = 0; i<=M.rows-1; i++)
		{for(int j = 0; j<=M.cols-1; j++)
			{
				double temp = double(M(i,j));
				N(i,j) = cos(temp);
			}
		}
	return N;
}

Mat_<double> sin(Mat& M)
{
	Mat N = M.clone();
	for(int i = 0; i<=M.rows-1; i++)
		{for(int j = 0; j<=M.cols-1; j++)
			{
				double temp = double(M(i,j));
				N(i,j) = sin(temp);
			}
		}
	return N;
}




cMat cos(Mat& M)
{
	cMat cM = cMat::zeros(M.rows, M.cols);
	Mat_<double> re = cos(M);
	return cM;
}

cMat sin(Mat& M)
{
	cMat cM = cMat::zeros(M.rows, M.cols);
	Mat_<double> re = cM.REAL;
	for(int i = 0; i<=M.rows-1; i++)
		{for(int j = 0; j<=M.cols-1; j++)
			{
				double temp = double(M(i,j));
				re(i,j) = sin(temp);
			}
		}
	cM.REAL = re;
	return cM;
}


void randu(cMat& cM, double low, double high)
{
	//当high<=low时抛出异常；
	cv::randu(cM.REAL,low,high);
	cv::randu(cM.IMAG,low,high);
}

void exp(const Mat_<double>& M, cMat& cM)			//返回exp(M)的复数矩阵;
{

}


void exp(const cMat& M, cMat& cM)					//返回exp(M)的复数矩阵;
{
	//M = a+ib; exp(a+ib) = exp(a)*exp(ib)



}

void exp_i2pi(const Mat_<double>& M, cMat& cM)
{
	//exp(i*2*pi*M) = cos(2*pi*M)+1i*sin(2*pi*M)
	for(int i = 0; i<=M.rows-1; i++)
		{for(int j = 0; j<=M.cols-1; j++)
			{
				cM.assign(i,j,cos(2*pi*M(i,j)),sin(2*pi*M(i,j)));
			}}

}

// 自定义的用于科学计算的矩阵函数：
Mat_<double> sqrt(const Mat_<double>& M)
{
	Mat_<double> N = M.clone();
	int num = M.rows*M.cols;
	for(int i = 0;i<=num-1;i++)
	{
		N(i) = sqrt(M(i));
	}
	return N;
}

Mat_<double> stepVector(double start, double interval, double end)
{
	//当end<start时抛出异常。
	int step = floor((end-start)/interval);
	Mat_<double> M = start*Mat_<double>::ones(1,step+1);
	for(int i = 1;i<=step;i++){M(i) = M(i)+i*interval;}
	return M;
}

Mat_<double> stepVector(double start, double interval, int dots)
{
	int step = dots-1;
	Mat_<double> M = start*Mat_<double>::ones(1,dots);
	for(int i = 1; i <= step; i++){M(i) = M(i)+i*interval;}
	return M;
}

Mat_<double> circ(const Mat_<double>& r)
{
	Mat_<double> output;
	output = abs(r) <= 1;
	output = output/255;
	return output;
}

Mat_<double> acos(const Mat_<double>& M)
{
	Mat_<double> N = M.clone();
	int num = M.rows*M.cols;
	for(int i = 0;i<=num-1;i++)
	{
		N(i) = acos(M(i));
	}
	return N;
}

void meshgrid(Mat_<double>& x, Mat_<double>& y,double xstart, double xinterval, double xend, double ystart, double yinterval, double yend)
{
	Mat_<double> tempx,tempy;
	tempx = stepVector(xstart, xinterval, xend);
	tempy = stepVector(ystart, yinterval, yend);
	transpose(tempy,tempy);
	int M = tempy.rows;
	int N = tempx.cols;
	repeat(tempx,M,1,x);
	repeat(tempy,1,N,y);
}

void meshgrid(Mat_<double>& x, Mat_<double>& y, double xstart, double xinterval, int xdots, double ystart, double yinterval, int ydots)
{
	Mat_<double> tempx,tempy;
	tempx = stepVector(xstart, xinterval, xdots);
	tempy = stepVector(ystart, yinterval, ydots);
	transpose(tempy,tempy);
	int M = tempy.rows;
	int N = tempx.cols;
	repeat(tempx,M,1,x);
	repeat(tempy,1,N,y);
}

void replaceInfAndNan(Mat_<double>& M)
{
	int num = M.rows*M.cols;
	for(int i = 0;i<=num-1;i++)
	{
		if(isnan(M(i))||isinf(M(i))){M(i) = 0;}
	}


}


#endif /* SRC_CMAT_H_ */
