//最后更新于2019.4.17晚上
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
#include <stdexcept>

#define pi 3.14159

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
	cv::Size size;

	//构造函数、析构函数。
	cMat();
	cMat(int ro,int co);
	cMat(cv::Mat_<double> RE, cv::Mat_<double> IM);					//输入实部和虚部矩阵构造复数矩阵。
	cMat(int ro,int co,double real,double imag);			//生成元素全为(real,imag)的复数矩阵。
	cMat(int ro, int co, double* pa, double* pb);			//输入二维数组的指针构造复数矩阵。
	cMat(const cv::Mat& M);										//输入普通矩阵，构造复数矩阵，虚部为0。
	cMat(const cMat& cM);									//拷贝构造函数。
	~cMat();

	//get/set方法，访问/修改矩阵元素的方法。
	std::complex<double> at(int ro,int co)	const;
	double* ptrReal(int ro, int co);
	double* ptrImag(int ro, int co);
	double* ptrReal(int a);
	double* ptrImag(int a);
	void assign(int ro,int co,std::complex<double> z);			//元素赋值函数
	void assign(int ro,int co,double real,double imag);

	//生成特殊复数矩阵的方法。
	cMat static zeros(int ro, int co);
	cMat static ones(int ro, int co);
	cMat static eye(int ro, int co);
	cMat static is(int ro, int co);

	//重载运算符。
	friend std::ostream& operator<<(std::ostream &os, cMat &cM);		//重载运算符<<使其可以输出复数矩阵。
	void operator=(const cMat &cM);								//重载赋值运算符。
	cMat operator+(const cMat &cM);								//重载加法
	cMat operator-(const cMat &cM);								//重载减法
	cMat operator*(const cMat &cM);								//重载乘法
	cMat operator*(const uchar &a);								//和uchar常数的乘法
	cMat operator*(const int &a);								//和int常数的乘法
	cMat operator*(const float &a);								//和float常数的乘法
	cMat operator*(const double &a);							//和double常数的乘法
	cMat operator*(const std::complex<double> &c);
	cMat operator/(const uchar &a);
	cMat operator/(const int &a);
	cMat operator/(const float &a);
	cMat operator/(const double &a);

	//重载Mat的方法。
	cMat clone() const;
	cMat mul(const cMat& cM);								//矩阵按元素相乘。
	cMat mul(const cv::Mat& M);								//和普通Mat按元素相乘
	void reshape(int ro);									//矩阵整形。

protected:



};

// 重载cv函数：
cMat imread(const std::string& filename);				//限定读取图片转为灰度数据。
void imshow(const std::string&, cMat&);
void transpose(cMat&, cMat&);
void dft(cMat&,cMat&);
void idft(cMat&,cMat&);
void dftshift(cMat&);								//零频移到中心：交换矩阵的一三象限、二四象限。
void idftshift(cMat&);
cMat abs(cMat&);
void randu(cMat& cM, double low, double high);			//返回随机矩阵。
void exp(const cv::Mat_<double>& M, cMat& cM);			//返回exp(M)的复数矩阵;
void exp(const cMat& M, cMat& cM);					//返回exp(M)的复数矩阵;
void exp_i2pi(const cv::Mat_<double>& M, cMat& cM);		//返回exp(1j*2*pi*M)的复数矩阵;
std::complex<double> complex(const cMat&);
cMat conj(const cMat& cM);

// 自定义的作用于Mat_<double>或返回Mat_<double>的函数
cv::Mat_<double> cos(cv::Mat_<double>&);
cv::Mat_<double> sin(cv::Mat_<double>&);
cv::Mat_<double> sqrt(const cv::Mat_<double>&);
cv::Mat_<double> stepVector(double start, double interval, double end);	//用于创建元素间隔相等的行向量。
cv::Mat_<double> linspace(double start, double end, int dots);		//用于创建元素间隔相等的行向量。
cv::Mat_<double> circ(const cv::Mat_<double>& r);
cv::Mat_<double> acos(const cv::Mat_<double>&);
void meshgrid(cv::Mat_<double>&,cv::Mat_<double>&,double,double,double,double,double,double);
void meshgrid(cv::Mat_<double>&,cv::Mat_<double>&,double,double,int,double,double,int);
void replaceInfAndNan(cv::Mat_<double>&);

// 类外的重载运算符
template <typename T>
cMat operator *(std::complex<T> c, cMat M);




//实现部分：

//构造函数和析构函数
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

cMat::cMat(int ro, int co, double* pa, double* pb)
{
	this->rows = ro;
	this->cols = co;
	cv::Mat_<double> REAL = cv::Mat_<double>::zeros(ro,co);
	cv::Mat_<double> IMAG = cv::Mat_<double>::zeros(ro,co);
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


//get/set方法，和访问/修改矩阵元素的方法。
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



//生成特殊复数矩阵的方法。
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

//重载运算符
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
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = (this->REAL)*(cM.REAL)-(this->IMAG)*(cM.IMAG);
	IM = (this->REAL)*(cM.IMAG)+(this->IMAG)*(cM.REAL);
	cMat temp(RE,IM);

	return temp;
}

cMat cMat::operator*(const uchar &a)								//和uchar常数的乘法
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const int &a)								//和int常数的乘法
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const float &a)								//和float常数的乘法
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const double &a)							//和double常数的乘法
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL*double(a);
	IM = this->IMAG*double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator*(const std::complex<double> &c)
{// (a+ib)*(m*in) = am-bn+i(bm+an)
	cv::Mat_<double> RE,IM;
	double a,b;
	a = c.real();
	b = c.imag();
	RE = (this->REAL)*a-(this->IMAG)*b;
	IM = (this->REAL)*b+(this->IMAG)*a;
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const uchar &a)
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const int &a)
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const float &a)
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

cMat cMat::operator/(const double &a)
{
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = this->REAL/double(a);
	IM = this->IMAG/double(a);
	cMat temp(RE,IM);
	return temp;
}

//	重载Mat的方法
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
	//前面需要检查AB尺寸是否相等，不相等则抛出异常。
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = (this->REAL).mul(cM.REAL)-(this->IMAG).mul(cM.IMAG);
	IM = (this->REAL).mul(cM.IMAG)+(this->IMAG).mul(cM.REAL);
	cMat temp(RE,IM);

	return temp;
}

cMat cMat::mul(const cv::Mat& M)
{
	//前面需要检查AB尺寸是否相等，不相等则抛出异常。
	cv::Mat_<double> RE;
	cv::Mat_<double> IM;
	RE = (this->REAL).mul(M);
	IM = (this->IMAG).mul(M);
	cMat temp(RE,IM);

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



// 重载cv函数：
cMat imread(const std::string& filename)
{
	cv::Mat M = cv::imread(filename, COLOR_BGR2GRAY);
	cMat cM = cMat(M);
	return cM;
}

void transpose(cMat& src, cMat& dst)
{
	cv::transpose(src.REAL, dst.REAL);
	cv::transpose(src.IMAG, dst.IMAG);
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

void exp(const cMat& M, cMat& cM)					//返回exp(M)的复数矩阵;
{
	//M = a+ib; exp(a+ib) = exp(a)*exp(ib)

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

std::complex<double> complex(const cMat& cM)
{
	if(cM.rows==1 && cM.cols==1)
	{
		std::complex<double> c = cM.at(0,0);
		return c;
	}
	else{throw std::invalid_argument("the matrix's size is not 1×1.");}
}



// 自定义的用于科学计算的矩阵函数：
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

cv::Mat_<double> stepVector(double start, double interval, double end)
{
	//当end<start时抛出异常。
	int step = floor((end-start)/interval);
	cv::Mat_<double> M = start*cv::Mat_<double>::ones(1,step+1);
	for(int i = 1;i<=step;i++){M(i) = M(i)+i*interval;}
	return M;
}

cv::Mat_<double> stepVector(double start, double interval, int dots)
{
	int step = dots-1;
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

void meshgrid(cv::Mat_<double>& x, cv::Mat_<double>& y, double xstart, double xinterval, int xdots, double ystart, double yinterval, int ydots)
{
	cv::Mat_<double> tempx,tempy;
	tempx = stepVector(xstart, xinterval, xdots);
	tempy = stepVector(ystart, yinterval, ydots);
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


// 类外的运算符重载
template <typename T>
cMat operator *(std::complex<T> c, cMat M)
{
	T a,b;
	a = c.real();
	b = c.imag();
	Mat_<double> RE,IM;
	cMat temp;
	RE = a*M.REAL-b*M.IMAG;
	IM = b*M.REAL+a*M.IMAG;
	temp = cMat(RE,IM);
	return temp;
}

}



#endif /* SRC_CMAT_H_ */
