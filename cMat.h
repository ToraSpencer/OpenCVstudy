// 最后更新于2019.6.10下午
/* to be done：
		norm():求行向量的L2范数。
		重载*运算符，定义数值变量*复数矩阵，使用偏特化限定函数模板中的类型变量T为数值变量。

   问题：
   	   	已经开辟内存空间的矩阵引用，能否用来接收函数返回的矩阵？
*/

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
#include <stdexcept>

#define pi 3.14159
#define eps 1e-6										//判断浮点数是否等于0的极小量。

#ifndef SRC_CMAT_H_
#define SRC_CMAT_H_


namespace cv
{
//复数矩阵类
class cMat
{public:
	int rows;
	int cols;
	cv::Mat_<double> REAL;
	cv::Mat_<double> IMAG;
	cv::Size_<double> size;

	// cMat类内：构造函数、析构函数。
	cMat();
	cMat(int ro,int co);
	cMat(cv::Mat_<double> RE, cv::Mat_<double> IM);			//输入实部和虚部矩阵构造复数矩阵。
	cMat(int ro,int co,double real,double imag);			//生成元素全为(real,imag)的复数矩阵。
	cMat(int ro,int co,double a[], double b[]);				//输入两个一维数组，指定尺寸，构造复数矩阵。
	cMat(const cv::Mat& M);									//输入普通矩阵，构造复数矩阵，虚部为0。
	cMat(const cMat& cM);									//拷贝构造函数。
	~cMat();

	// cMat类内：get/set方法，访问/修改矩阵元素的方法。
	std::complex<double> at(int ro,int co)	const;
	double* ptrReal(int ro, int co);
	double* ptrImag(int ro, int co);
	double* ptrReal(int a);
	double* ptrImag(int a);
	void assign(int ro,int co,std::complex<double> z);			//元素赋值函数
	void assign(int ro,int co,double real,double imag);

	// cMat类内：生成特殊复数矩阵的方法。
	cMat static zeros(int ro, int co);
	cMat static ones(int ro, int co);
	cMat static eye(int ro, int co);
	cMat static is(int ro, int co);

	// cMat类内：重载运算符。
	friend std::ostream& operator<<(std::ostream &os, cMat &cM);		//重载运算符<<使其可以输出复数矩阵。
	void operator=(const cMat& cM);								//重载赋值运算符。
	cMat operator+(const cMat& cM);								//重载加法
	cMat operator-(const cMat& cM);								//重载减法
	template<typename T>
	cMat operator*(const T& num);
	cMat operator*(const cv::Mat_<double>& M);
	template<typename T>
	cMat operator*(const std::complex<T>& c);
	cMat operator*(const cMat& cM);
	template<typename T>
	cMat operator/(const T& num);

	// cMat类内：重载Mat的成员方法。
	cMat clone() const;
	cMat mul(const cMat& cM);								// 矩阵按元素相乘。
	cMat mul(const cv::Mat& M);								// 和普通Mat按元素相乘
	void reshape(int ro);									// 矩阵整形。
	void release();
	void create(int ro, int co);


protected:

};

// 重载、自定义矩阵函数
cMat imread(const std::string& filename);				//限定读取图片转为灰度数据。
void imshow(const std::string&, cMat&);
cMat transpose(cMat);
void dft(cMat&,cMat&);
void idft(cMat&,cMat&);
void dftshift(cMat&);									//零频移到中心：交换矩阵的一三象限、二四象限。
void idftshift(cMat&);
cMat abs(cMat&);
void randu(cMat& cM, double low, double high);			//返回随机矩阵。
void exp(const cv::Mat_<double>& M, cMat& cM);			//返回exp(M)的复数矩阵;
void exp(const cMat& cM1, cMat& cM2);					//返回exp(M)的复数矩阵;
cMat exp(const cMat& cM);
void exp_i2pi(const cv::Mat_<double>& M, cMat& cM);		//返回exp(1j*2*pi*M)的复数矩阵;
std::complex<double> complex(const cMat&);
cMat conj(const cMat& cM);
cMat dot(const cMat&, const cMat&);
cMat dot(const cMat&, const cv::Mat_<double>&);
cMat dot(const cv::Mat_<double>&, const cMat&);


// 重载、自定义Mat_<double> → Mat_<double>的函数
cv::Mat_<double> transpose(cv::Mat_<double>);
cv::Mat_<double> cos(cv::Mat_<double>&);
cv::Mat_<double> sin(cv::Mat_<double>&);
cv::Mat_<double> sqrt(const cv::Mat_<double>&);
cv::Mat_<double> exp(const cv::Mat_<double>&);
cv::Mat_<double> stepVector(double start, double interval, double end);	//用于创建元素间隔相等的行向量。
cv::Mat_<double> linspace(double start, double end, int dots);		//用于创建元素间隔相等的行向量。
cv::Mat_<double> circ(const cv::Mat_<double>& r);
cv::Mat_<double> acos(const cv::Mat_<double>&);
void meshgrid(cv::Mat_<double>&,cv::Mat_<double>&,double,double,double,double,double,double);
void linspacegrid(cv::Mat_<double>&,cv::Mat_<double>&,double,double,int,double,double,int);
void replaceInfAndNan(cv::Mat_<double>&);
cv::Mat_<double> dot(const cv::Mat_<double>&, const cv::Mat_<double>&);
void max(cv::Mat_<double>& M, int num);
void max(cv::Mat_<double>& M, double num);
cv::Mat_<double> max(cv::Mat_<double>& M1, cv::Mat_<double>& M2);
void min(cv::Mat_<double>& M, int num);
void min(cv::Mat_<double>& M, double num);
template <typename T>
cv::Mat_<double> max(const cv::Mat_<double>& src, int flag, const T &num);		// 取src每行/列最大值，生成列/行向量，不过如果最大值比不过num的话，取num
template <typename T>
cv::Mat_<double> min(const cv::Mat_<double>& src, int flag, const T &num);		// 取src每行/列最小值，生成列/行向量，不过如果最小值比不过num的话，取num
double norm2(const cv::Mat_<double>& src);											// 求src的L2范数。
double normInf(const cv::Mat_<double>& src);									// 求src的最大绝对行之和。


// Mat_<double> → Mat_<double>的重载运算符；
template<typename T>
cMat operator*(const cv::Mat_<double>& M, const std::complex<T>& c);
template<typename T>
cMat operator*(const std::complex<T>& c, const cv::Mat_<double>& M);

// 类外的关于cMat的重载运算符











// 实现部分：

// cMat类内：构造函数和析构函数
cMat::cMat()
{
	this->rows = 0;
	this->cols = 0;
	this->REAL = cv::Mat_<double>();
	this->IMAG = cv::Mat_<double>();
	this->size = (this->REAL).size();
}

cMat::cMat(int ro,int co)
{
	this->rows = ro;
	this->cols = co;
	this->REAL = cv::Mat_<double>(ro,co);
	this->IMAG = cv::Mat_<double>(ro,co);
	this->size = (this->REAL).size();
}

cMat::cMat(cv::Mat_<double> RE, cv::Mat_<double> IM)
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
	cv::Mat_<double> O = cv::Mat_<double>::ones(ro,co);
	this->REAL = real*O;
	this->IMAG = imag*O;
	this->size = (this->REAL).size();
}

cMat::cMat(int ro,int co,double a[], double b[])
{
	this->rows = ro;
	this->cols = co;
	cv::Mat_<double> REAL = cv::Mat_<double>(ro,co,a);
	cv::Mat_<double> IMAG = cv::Mat_<double>(ro,co,b);
	this->REAL = REAL;
	this->IMAG = IMAG;
	this->size = (this->REAL).size();
}

cMat::cMat(const cv::Mat& M)
{
	cv::Mat MM;
	M.convertTo(MM,CV_64FC1);
	this->rows = MM.rows;
	this->cols = MM.cols;
	this->REAL = MM;
	this->IMAG = cv::Mat_<double>::zeros(MM.size());
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


// cMat类内：get/set方法，和访问/修改矩阵元素的方法。
std::complex<double> cMat::at(int ro,int co)	const
{
	double real = this->REAL(ro,co);
	double imag = this->IMAG(ro,co);
	std::complex<double> z(real,imag);

	return z;
}

double* cMat::ptrReal(int ro, int co)
{
	double* p = this->REAL.ptr<double>(ro,co);
	return p;
}

double* cMat::ptrImag(int ro, int co)
{
	double* p = this->IMAG.ptr<double>(ro,co);
	return p;
}

double* cMat::ptrReal(int a)
{
	double* p = this->REAL.ptr<double>(a);
	return p;
}

double* cMat::ptrImag(int a)
{
	double* p = this->IMAG.ptr<double>(a);
	return p;
}

void cMat::assign(int ro,int co, std::complex<double> z)
{
	this->REAL(ro,co) = z.real();
	this->IMAG(ro,co) = z.imag();
}

void cMat::assign(int ro,int co,double real,double imag)
{
	this->REAL(ro,co) = real;
	this->IMAG(ro,co) = imag;
}

// cMat类内：生成特殊复数矩阵的方法。
cMat cMat::zeros(int ro, int co)
{
	cMat* p = NULL;
	p = new cMat();
	cv::Mat_<double> REAL = cv::Mat_<double>::zeros(ro,co);
	cv::Mat_<double> IMAG = cv::Mat_<double>::zeros(ro,co);
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
	cv::Mat_<double> REAL = cv::Mat_<double>::ones(ro,co);
	cv::Mat_<double> IMAG = cv::Mat_<double>::ones(ro,co);
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
	cv::Mat_<double> REAL = cv::Mat_<double>::eye(ro,co);
	cv::Mat_<double> IMAG = cv::Mat_<double>::eye(ro,co);
	p->rows = ro;
	p->cols = co;
	p->REAL = REAL;
	p->IMAG = IMAG;
	p->size = REAL.size();

	return *p;
}

cMat cMat::is(int ro, int co)
{
	cMat* p = nullptr;
	p = new cMat();
	cv::Mat_<double> REAL = cv::Mat_<double>::zeros(ro,co);
	cv::Mat_<double> IMAG = cv::Mat_<double>::ones(ro,co);
	p->rows = ro;
	p->cols = co;
	p->REAL = REAL;
	p->IMAG = IMAG;
	p->size = REAL.size();

	return *p;
}

// cMat类内：重载运算符
std::ostream& operator<<(std::ostream &os, cMat &cM)		//重载<<
{
	for(int i = 0; i<=cM.rows-1; i++)
		{for(int j = 0; j<=cM.cols-1;j++)
			{
			std::complex<double> z = cM.at(i,j);
				os << z << " ";
				if((i*cM.cols+j+1)%cM.cols==0){os << "\n";}
			}
		}

	return os;
}

void cMat::operator=(const cMat &cM)
{
	this->release();
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
	cv::Mat_<double> REAL = this->REAL+cM.REAL;
	cv::Mat_<double> IMAG = this->IMAG+cM.IMAG;
	cMat temp(REAL,IMAG);
	return temp;
}

cMat cMat::operator-(const cMat &cM)					//重载减法
{
	cv::Mat_<double> REAL = this->REAL-cM.REAL;
	cv::Mat_<double> IMAG = this->IMAG-cM.IMAG;
	cMat temp(REAL,IMAG);
	return temp;
}

cMat cMat::operator*(const cMat &cM)					//重载乘法
{
	//this->cols != cM.rows时，抛出异常。
	cMat temp;
	if((this->cols)!=cM.rows)
	{
		throw std::invalid_argument("left matrix's cols must equal to the right matrix's rows.");
	}
	else
	{
		cv::Mat_<double> RE,IM;
		RE = (this->REAL)*(cM.REAL)-(this->IMAG)*(cM.IMAG);
		IM = (this->REAL)*(cM.IMAG)+(this->IMAG)*(cM.REAL);
		temp = cMat(RE,IM);
	}
	return temp;
}

cMat cMat::operator*(const cv::Mat_<double>& M)			//和实矩阵的乘法
{
	cMat temp;
	cv::Mat_<double> re,im;
	re = this->REAL*M;
	im = this->IMAG*M;
	temp = cMat(re,im);
	return temp;
}

template<typename T>
cMat cMat::operator*(const T& num)						//和实数的乘法
{
	cMat temp;
	Mat_<double> re,im;
	re = this->REAL/num;
	im = this->IMAG/num;
	temp = cMat(re,im);
	return temp;
}

template<typename T>
cMat cMat::operator*(const std::complex<T>& c)			//和复数的乘法
{
	T a,b;
	cv::Mat_<double> re,im;
	cMat temp;
	a = c.real();
	b = c.imag();
	re = this->REAL*a-this->IMAG*b;
	im = this->REAL*b+this->IMAG*a;
	temp = cMat(re,im);
	return temp;
}

template<typename T>
cMat cMat::operator/(const T& num)						//和实数的除法
{
	//当除数为0时，抛出异常
	cMat temp;
	Mat_<double> re,im;

	if(num<eps && num>-eps)
	{
		throw std::invalid_argument("The divisor cannot be zero.");
	}
	else
	{
		re = this->REAL/num;
		im = this->IMAG/num;
		temp = cMat(re,im);
	}

	return temp;
}


// cMat类内：重载Mat的成员方法。
cMat cMat::clone() const
{
	cv::Mat_<double> RE,IM;
	RE = this->REAL.clone();
	IM = this->IMAG.clone();
	cMat cM(RE,IM);
	return cM;
}

cMat cMat::mul(const cMat& cM)    				    //(r1,i1)*(r2,i2) = (r1*r2-i1*i2,r1*i2+i1*r2)
{
	cv::Mat_<double> RE,IM;
	cMat temp;
	if(this->rows!=cM.rows||this->cols!=cM.cols)
	{
		throw std::invalid_argument("Two Matrices arguments should have the same size.");
	}
	else
	{
		RE = (this->REAL).mul(cM.REAL)-(this->IMAG).mul(cM.IMAG);
		IM = (this->REAL).mul(cM.IMAG)+(this->IMAG).mul(cM.REAL);
		temp = cMat(RE,IM);
	}
	return temp;
}

cMat cMat::mul(const cv::Mat& M)
{
	cv::Mat_<double> RE,IM;
	cMat temp;
	if(this->rows!=M.rows||this->cols!=M.cols)
	{
		throw std::invalid_argument("Two Matrices arguments should have the same size.");
	}
	else
	{
		RE = (this->REAL).mul(M);
		IM = (this->IMAG).mul(M);
		temp = cMat(RE,IM);
	}
	return temp;
}

cMat conj(const cMat& cM)
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
	cv::Mat_<double> REAL = this->REAL.reshape(0,ro);
	cv::Mat_<double> IMAG = this->IMAG.reshape(0,ro);
	this->cols = (int)((this->rows)*(this->cols)/ro);
	this->rows = ro;

	this->REAL = REAL;
	this->IMAG = IMAG;
	this->size = REAL.size();

}

void cMat::release()
{
	this->REAL.release();
	this->IMAG.release();
	this->rows = REAL.rows;
	this->cols = REAL.cols;
	this->size = REAL.size();
}

void cMat::create(int ro, int co)
{
	this->REAL.create(ro,co);
	this->IMAG.create(ro,co);
	this->rows = REAL.rows;
	this->cols = REAL.cols;
	this->size = REAL.size();

}

// 重载、自定义和cMat有关的函数：
cMat imread(const std::string& filename)
{
	cv::Mat M = cv::imread(filename, COLOR_BGR2GRAY);
	cMat cM = cMat(M);
	return cM;
}

cMat transpose(cMat M)
{
	cMat temp;
	int rows,cols;
	cv::Mat_<double> re,im,ree,imm;
	rows = M.rows;
	cols = M.cols;
	re = M.REAL;
	im = M.IMAG;
	ree = Mat_<double>(cols,rows);
	imm = Mat_<double>(cols,rows);
	cv::transpose(re,ree);
	cv::transpose(im,imm);
	temp = cMat(ree,imm);
	return temp;
}

void imshow(const std::string& str, cMat& cM)
{
	cv::Mat RE;
	cM.REAL.convertTo(RE,CV_8UC1);
	cv::imshow(str, RE);
}

void dft(cMat& src, cMat& dst)
{
	cv::Mat_<float> temp[2];
	cv::Mat f,F;
	temp[0] = src.REAL;
	temp[1] = src.IMAG;
	cv::merge(temp,2,f);
	cv::dft(f,F);
	cv::split(F,temp);
	cMat cM = cMat(temp[0], temp[1]);
	dst = cM.clone();
}

void idft(cMat& src, cMat& dst)
{
	cv::Mat_<float> temp[2];
	cv::Mat f,F;
	temp[0] = src.REAL;
	temp[1] = src.IMAG;
	cv::merge(temp,2,F);
	cv::idft(F,f);
	cv::split(f,temp);
	cMat cM = cMat(temp[0], temp[1]);
	dst = cM.clone();
	dst = dst/(dst.rows*dst.cols);
}

void dftshift(cMat& cM)
{
	int Or,Oc,M,N;
	cv::Mat_<double> A,B,C,D,temp,temp1,temp2;
	M = cM.rows;
	N = cM.cols;
	Or = ceil(M/2.0);
	Oc = ceil(N/2.0);
	A = cM.REAL(cv::Rect(0,0,Oc,Or));
	D = cM.REAL(cv::Rect(Oc,Or,N-Oc,M-Or));
	B = cM.REAL(cv::Rect(Oc,0,N-Oc,Or));
	C = cM.REAL(cv::Rect(0,Or,Oc,M-Or));
	cv::hconcat(D,C,temp1);
	cv::hconcat(B,A,temp2);
	cv::vconcat(temp1,temp2,cM.REAL);


	A = cM.IMAG(cv::Rect(0,0,Oc,Or));
	D = cM.IMAG(cv::Rect(Oc,Or,N-Oc,M-Or));
	B = cM.IMAG(cv::Rect(Oc,0,N-Oc,Or));
	C = cM.IMAG(cv::Rect(0,Or,Oc,M-Or));
	cv::hconcat(D,C,temp1);
	cv::hconcat(B,A,temp2);
	cv::vconcat(temp1,temp2,cM.IMAG);

}

void idftshift(cMat& cM)
{
	int Or,Oc,M,N;
	cv::Mat_<double> A,B,C,D,temp,temp1,temp2;
	M = cM.rows;
	N = cM.cols;
	Or = floor(M/2.0);
	Oc = floor(N/2.0);
	A = cM.REAL(cv::Rect(0,0,Oc,Or));
	D = cM.REAL(cv::Rect(Oc,Or,N-Oc,M-Or));
	B = cM.REAL(cv::Rect(Oc,0,N-Oc,Or));
	C = cM.REAL(cv::Rect(0,Or,Oc,M-Or));
	cv::hconcat(D,C,temp1);
	cv::hconcat(B,A,temp2);
	cv::vconcat(temp1,temp2,cM.REAL);

	A = cM.IMAG(cv::Rect(0,0,Oc,Or));
	D = cM.IMAG(cv::Rect(Oc,Or,N-Oc,M-Or));
	B = cM.IMAG(cv::Rect(Oc,0,N-Oc,Or));
	C = cM.IMAG(cv::Rect(0,Or,Oc,M-Or));
	cv::hconcat(D,C,temp1);
	cv::hconcat(B,A,temp2);
	cv::vconcat(temp1,temp2,cM.IMAG);
}

cMat abs(cMat& cM)
{
	cMat temp = cM.clone();
	temp.REAL = cv::sqrt(temp.REAL.mul(temp.REAL)+temp.IMAG.mul(temp.IMAG));
	temp.IMAG = cv::Mat_<double>::zeros(temp.rows,temp.cols);
	return temp;
}

void randu(cMat& cM, double low, double high)
{
	//当high<=low时抛出异常；
	cv::randu(cM.REAL,low,high);
	cv::randu(cM.IMAG,low,high);
}

void exp(const cv::Mat_<double>& M, cMat& cM)			//返回exp(M)的复数矩阵;
{
	cM = cMat::zeros(M.rows,M.cols);
	cv::exp(M, cM.REAL);
}

void exp(const cMat& cM1, cMat& cM2)					//返回exp(M)的复数矩阵;
{
	//M = a+ib; exp(a+ib) = exp(a).*exp(ib) = exp(a).*(cos(b)+i*sin(b))
	Mat_<double> a, b, re, im;
	cMat temp;

	a = cM1.REAL;
	b = cM1.IMAG;

	a = cv::exp(a);
	re = cv::cos(b);
	im = cv::sin(b);
	cM2 = cMat(re,im);
	cM2 = cv::dot(a,cM2);
}

cMat exp(const cMat& cM)
{
	Mat_<double> a, b, re, im;
	cMat temp;

	a = cM.REAL;
	b = cM.IMAG;

	a = cv::exp(a);
	re = cv::cos(b);
	im = cv::sin(b);
	temp = cMat(re,im);
	temp = cv::dot(a,temp);

	return temp;
}

void exp_i2pi(const cv::Mat_<double>& M, cMat& cM)
{
	//exp(i*2*pi*M) = cos(2*pi*M)+1i*sin(2*pi*M)
	cv::Mat_<double> a,b;
	a = M.clone();
	b = M.clone();
	a = 2*pi*a;
	b = 2*pi*b;
	a = cv::cos(a);
	b = cv::sin(b);
	cM = cMat(a,b);
}

std::complex<double> complex(const cMat& cM)			//将1×1的复数矩阵转换为double复数类型。
{
	if(cM.rows==1 && cM.cols==1)
	{
		std::complex<double> c = cM.at(0,0);
		return c;
	}
	else{throw std::invalid_argument("the matrix's size is not 1×1.");}
}

cMat dot(const cMat& cM1, const cMat& cM2)
{
	cMat temp;
	cv::Mat_<double> re,im;
	if(cM1.rows!=cM2.rows||cM1.cols!=cM2.cols)
	{
		throw std::invalid_argument("Two Matrices arguments should have the same size.");
	}
	else
	{
		re = cM1.REAL.mul(cM2.REAL)-cM1.IMAG.mul(cM2.IMAG);
		im = cM1.REAL.mul(cM1.IMAG)+cM1.IMAG.mul(cM2.REAL);
		temp = cMat(re,im);
	}
	return temp;
}

cMat dot(const cMat& cM, const cv::Mat_<double>& M)
{
	cMat temp;
	cv::Mat_<double> re,im;
	if(cM.rows!=M.rows||cM.cols!=M.cols)
	{
		throw std::invalid_argument("Two Matrices arguments should have the same size.");
	}
	else
	{
		re = cM.REAL.mul(M);
		im = cM.IMAG.mul(M);
		temp = cMat(re,im);
	}
	return temp;
}

cMat dot(const cv::Mat_<double>& M, const cMat& cM)
{
	cMat temp;
	cv::Mat_<double> re,im;
	if(cM.rows!=M.rows||cM.cols!=M.cols)
	{
		throw std::invalid_argument("Two Matrices arguments should have the same size.");
	}
	else
	{
		re = M.mul(cM.REAL);
		im = M.mul(cM.IMAG);
		temp = cMat(re,im);
	}
	return temp;
}


// 重载、自定义Mat_<double> → Mat_<double>的函数
cv::Mat_<double> transpose(cv::Mat_<double> M)
{
	int rows,cols;
	Mat_<double> temp;

	rows = M.rows;
	cols = M.cols;
	temp = Mat_<double>(cols,rows);
	transpose(M,temp);
	return temp;
}

cv::Mat_<double> cos(cv::Mat_<double>& M)
{
	cv::Mat_<double> N = M.clone();
	for(int i = 0; i<=M.rows-1; i++)
		{for(int j = 0; j<=M.cols-1; j++)
			{
				double temp = M(i,j);
				N(i,j) = std::cos(temp);
			}
		}
	return N;
}

cv::Mat_<double> sin(cv::Mat_<double>& M)
{
	cv::Mat_<double> N = M.clone();
	for(int i = 0; i<=M.rows-1; i++)
		{for(int j = 0; j<=M.cols-1; j++)
			{
				double temp = M(i,j);
				N(i,j) = std::sin(temp);
			}
		}
	return N;
}

cv::Mat_<double> sqrt(const cv::Mat_<double>& M)
{
	cv::Mat_<double> N = M.clone();
	int num = M.rows*M.cols;
	for(int i = 0;i<=num-1;i++)
	{
		N(i) = cv::sqrt(M(i));
	}
	return N;
}

cv::Mat_<double> exp(const cv::Mat_<double>&M)
{
	cv::Mat_<double> temp1,temp2;
	temp1 = M.clone();
	cv::exp(temp1,temp2);
	return temp2;
}

cv::Mat_<double> stepVector(double start, double interval, double end)
{
	//当end<start时抛出异常。
	int step = floor((end-start)/interval);
	cv::Mat_<double> M = start*cv::Mat_<double>::ones(1,step+1);
	for(int i = 1;i<=step;i++){M(i) = M(i)+i*interval;}
	return M;
}

cv::Mat_<double> linspace(double start, double end, int dots)
{
	int step = dots-1;
	double interval = (end-start)/double(step);
	cv::Mat_<double> M = start*cv::Mat_<double>::ones(1,dots);
	for(int i = 1; i <= step; i++){M(i) = M(i)+i*interval;}
	return M;
}

cv::Mat_<double> circ(const cv::Mat_<double>& r)
{
	cv::Mat_<double> output;
	output = cv::abs(r) <= 1;
	output = output/255;
	return output;
}

cv::Mat_<double> acos(const cv::Mat_<double>& M)
{
	cv::Mat_<double> N = M.clone();
	int num = M.rows*M.cols;
	for(int i = 0;i<=num-1;i++)
	{
		N(i) = std::acos(N(i));
	}
	return N;
}

void meshgrid(cv::Mat_<double>& x, cv::Mat_<double>& y,double xstart, double xinterval, double xend, double ystart, double yinterval, double yend)
{
	cv::Mat_<double> tempx,tempy;
	tempx = stepVector(xstart, xinterval, xend);
	tempy = stepVector(ystart, yinterval, yend);
	cv::transpose(tempy,tempy);
	int M = tempy.rows;
	int N = tempx.cols;
	cv::repeat(tempx,M,1,x);
	cv::repeat(tempy,1,N,y);
}

void linspacegrid(cv::Mat_<double>&x, cv::Mat_<double>&y, double xstart, double xend, int xdots, double ystart, double yend, int ydots)
{
	cv::Mat_<double> tempx,tempy;
	tempx = linspace(xstart, xend, xdots);
	tempy = linspace(ystart, yend, ydots);
	cv::transpose(tempy,tempy);
	int M = tempy.rows;
	int N = tempx.cols;
	cv::repeat(tempx,M,1,x);
	cv::repeat(tempy,1,N,y);
}

void replaceInfAndNan(cv::Mat_<double>& M)
{
	int num = M.rows*M.cols;
	for(int i = 0;i<=num-1;i++)
	{
		if(std::isnan(M(i))||std::isinf(M(i))){M(i) = 0;}
	}


}

cv::Mat_<double> dot(const cv::Mat_<double>& M1, const cv::Mat_<double>& M2)
{
	cv::Mat_<double> temp;
	temp = M1.mul(M2);
	return temp;
}

void max(cv::Mat_<double>& M, int num)
{
	//以后可以考虑用偏特化限定类型参数，然后用函数模板编写此函数：
	double* p = nullptr;

	double num2 = double(num);

	for(int m = 0; m<=M.rows-1; m++)
	{
		for(int n = 0; n<=M.cols-1; n++)
		{
			p = M.ptr<double>(m,n);
			if(*p<num2){*p = num2;}
		}
	}

}

void max(cv::Mat_<double>& M, double num)
{
	//以后可以考虑用偏特化限定类型参数，然后用函数模板编写此函数：
	double* p = nullptr;

	for(int m = 0; m<=M.rows-1; m++)
	{
		for(int n = 0; n<=M.cols-1; n++)
		{
			p = M.ptr<double>(m,n);
			if(*p<num){*p = num;}
		}
	}
}

cv::Mat_<double> max(cv::Mat_<double>& M1, cv::Mat_<double>& M2)
{
	cv::Mat_<double> temp;
	double* p = nullptr;
	double* q = nullptr;
	double* r = nullptr;

	temp = Mat_<double>::zeros(M1.rows, M1.cols);
	//当M1M2尺寸不相同时抛出异常：
	if(M1.rows!=M2.rows||M1.cols!=M2.cols)
	{
		throw std::invalid_argument("Two matrices inputed should have the same size.");
	}
	else
	{
		for(int m = 0; m<=M1.rows-1; m++)
		{
			for(int n = 0; n<=M1.cols-1; n++)
			{
				p = M1.ptr<double>(m,n);
				q = M2.ptr<double>(m,n);;
				r = temp.ptr<double>(m,n);

				(*p > *q)? (*r = *p): (*r = *q);
			}
		}
	}

	return temp;
}

void min(cv::Mat_<double>& M, int num)
{
	//以后可以考虑用偏特化限定类型参数，然后用函数模板编写此函数：
	double* p = nullptr;

	double num2 = double(num);

	for(int m = 0; m<=M.rows-1; m++)
	{
		for(int n = 0; n<=M.cols-1; n++)
		{
			p = M.ptr<double>(m,n);
			if(*p>num2){*p = num2;}
		}
	}

}

void min(cv::Mat_<double>& M, double num)
{
	//以后可以考虑用偏特化限定类型参数，然后用函数模板编写此函数：
	double* p = nullptr;

	for(int m = 0; m<=M.rows-1; m++)
	{
		for(int n = 0; n<=M.cols-1; n++)
		{
			p = M.ptr<double>(m,n);
			if(*p>num){*p = num;}
		}
	}
}

cv::Mat_<double> min(cv::Mat_<double>& M1, cv::Mat_<double>& M2)
{
	cv::Mat_<double> temp;
	double* p = nullptr;
	double* q = nullptr;
	double* r = nullptr;

	temp = Mat_<double>::zeros(M1.rows, M1.cols);
	//当M1M2尺寸不相同时抛出异常：
	if(M1.rows!=M2.rows||M1.cols!=M2.cols)
	{
		throw std::invalid_argument("Two matrices inputed should have the same size.");
	}
	else
	{
		for(int m = 0; m<=M1.rows-1; m++)
		{
			for(int n = 0; n<=M1.cols-1; n++)
			{
				p = M1.ptr<double>(m,n);
				q = M2.ptr<double>(m,n);;
				r = temp.ptr<double>(m,n);

				(*p < *q)? (*r = *p): (*r = *q);
			}
		}
	}

	return temp;
}

template <typename T>
cv::Mat_<double> max(const cv::Mat_<double>& src, int flag, const T &num) 		// 取src每行/列最大值，生成列/行向量，不过如果最大值比不过num的话，取num
{
	// flag为0时返回行向量，为1时返回列向量。
	// 输入矩阵为空时抛出异常；
	if(!src.data)
	{
		throw std::invalid_argument("the input matrix is empty.");
	}

	// 输入矩阵必须为单通道二维矩阵，否则抛出异常。
	if(src.dims>2 && src.channels()>1)
	{
		throw std::invalid_argument("Input matrix must be two dimensional and has only one channel.");
	}

	cv::Mat temp;
	cv::reduce(src, temp, flag, CV_REDUCE_MAX);

	// 将生成的向量中的元素逐个和num比较。
	double* p;
	p = temp.ptr<double>(0,0);
	for(int count = 1; count <= temp.rows*temp.cols; count++, p++)
	{
		if(*p<num)
		{
			*p = num;
		}
	}


	return temp;
}

template <typename T>
cv::Mat_<double> min(const cv::Mat_<double>& src, int flag, const T &num)
{
	// 输入矩阵为空时抛出异常；
	if(!src.data)
	{
		throw std::invalid_argument("the input matrix is empty.");
	}

	// 输入矩阵必须为单通道二维矩阵，否则抛出异常。
	if(src.dims>2 && src.channels()>1)
	{
		throw std::invalid_argument("Input matrix must be two dimensional and has only one channel.");
	}

	cv::Mat temp;
	cv::reduce(src, temp, flag, CV_REDUCE_MIN);

	// 将生成的向量中的元素逐个和num比较。
	double* p;
	p = temp.ptr<double>(0,0);
	for(int count = 1; count <= temp.rows*temp.cols; count++, p++)
	{
		if(*p>num)
		{
			*p = num;
		}
	}


	return temp;

}

double norm2(const cv::Mat_<double>& src)											// 求src的L2范数。
{
	// 输入矩阵为空时抛出异常；
	if(!src.data)
	{
		throw std::invalid_argument("the input matrix is empty.");
		return -1;
	}

	const double* p = src.ptr<double>(0,0);
	double temp = 0;
	for(int count = 1; count<= src.rows*src.cols; count++, p++)
	{
		temp = temp + (*p)*(*p);
	}

	temp = std::sqrt(temp);
	return temp;
}

double normInf(const cv::Mat_<double>& src)									// 求src的最大绝对行之和。
{
	cv::Mat_<double> dst1, dst2;
	double minVal, maxVal;

	dst1 = cv::abs(src);

	cv::reduce(dst1, dst2,0,CV_REDUCE_SUM);
	cv::minMaxIdx(dst2, &minVal, &maxVal);

	return maxVal;
}

// Mat_<double> → Mat_<double>的重载运算符；
template<typename T>
cMat operator*(const cv::Mat_<double>& M, const std::complex<T>& c)
{
	cMat temp;
	T a,b;
	Mat_<double> RE,IM;
	a = c.real();
	b = c.imag();
	RE = a*M-b*M;
	IM = b*M+a*M;
	temp = cMat(RE,IM);

	return temp;
}

template<typename T>
cMat operator*(const std::complex<T>& c, const cv::Mat_<double>& M)
{
	cMat temp;
	T a,b;
	Mat_<double> RE,IM;
	a = c.real();
	b = c.imag();
	RE = a*M-b*M;
	IM = b*M+a*M;
	temp = cMat(RE,IM);

	return temp;
}


// 类外的关于cMat的重载运算符


}



#endif /* SRC_CMAT_H_ */
