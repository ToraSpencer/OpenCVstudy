#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include "cMat.h"

using namespace std;
using namespace cv;

/* 一维连续傅里叶变换：
 * 			F(u) = $f(t)*exp(-1j*2*pi*t*u)dt;
 * 一维离散傅里叶变换DCT:
 * 			频谱序列序数为j的元素：F(j) = SIGMA(f(i)*exp(-1j*2*pi*i*j/N))， 对f整个序列遍历累加。
 * 			j从0开始。
 * 			f是空域的离散时间信号序列，F是变换到频域的序列，两者长度相同。
 */

/*
N = numel(f);
F = zeros(1,N);
for j = 1:N
    v_complex = 0:1:N-1;
    v_complex = transpose(v_complex);
    v_complex = exp(-1j*2*pi*(j-1)/N.*v_complex);
    F(j) = f*v_complex;
end

a =
   1.0000 + 4.0000i   2.0000 + 5.0000i   3.0000 + 6.0000i
fft(a) =
   6.0000 +15.0000i  -2.3660 - 0.6340i  -0.6340 - 2.3660i
*/


//DCT的底层实现：
cMat DFT(cMat f)		//f要求为cMat行向量。
{
	int N;
	cMat F,temp1,temp2,temp3;
	std::complex<double> c,d;
	double* pre = nullptr;
	double* pim = nullptr;

	N = f.rows*f.cols;
	F = f.clone();
	temp1 = cMat(1,N);
	temp2 = cMat(N,1);
	for(int k = 0; k<= N-1;k++)
	{
		temp1 = cv::stepVector(0,1,N-1);
		temp2 = transpose(temp1);
		c = std::complex<double>(0,-2*pi/double(N));
		temp2 = temp2*c;
		cv::exp(temp2,temp3);
		temp3 = f*temp3;
		d = cv::complex(temp3);
		pre = F.ptrReal(k);
		pim = F.ptrImag(k);
		*pre = d.real();
		*pim = d.imag();
	}
	return F;
}

void test0()
{
	cMat a = cMat::eye(3,3);
	double* pre = a.ptrReal(0,1);
	double* pim = a.ptrImag(0,1);
	cout << "a = \n" << a << endl;
	*pre = 33;
	*pim = 44;
	cout << "a = \n" << a << endl;
	*pre = 0;
	*pim = 0;
	a.IMAG = Mat_<double>::zeros(3,3);
	cout << "a = \n" << a << endl;
	std::complex<double> c(1,2);
	cMat temp;
	temp = a*c;
	cout << "temp = \n" << temp << endl;
	temp = c*a;
	cout << "temp = \n" << temp << endl;

	a = cMat(1,3);
	cMat b = cMat(3,1);
	cout << "a = \n" << a << endl;
	cv::randu(a,0,1);
	cout << "a = \n" << a << endl;
	a = cv::conj(a);
	cout << "a = \n" << a << endl;
	b = transpose(a);
	temp = a*b;
	cout << "temp = \n" << temp << endl;
	temp = b*a;
	cout << "temp = \n" << temp << endl;

}

void test1()
{
	cMat f,F;
	double a[] = {1,2,3};
	double b[] = {4,5,6};

	Mat_<double> RE(1,3,a);
	Mat_<double> IM(1,3,b);
	f = cMat(RE,IM);
	cout << "f = \n"<< f << endl;

	cv::dft(f,F);
	cout << "F  = \n" << F << endl;

	F = DFT(f);
	cout << "F  = \n" << F << endl;


}

void test2()
{
	int N;
		cMat f, F,temp1,temp2,temp3;
		std::complex<double> c,d;
		//double* pre = nullptr;
		//double* pim = nullptr;


		double a[3] = {1,2,3};
		double b[3] = {4,5,6};
		Mat_<double> re = Mat_<double>(1,3,a);
		Mat_<double> im = Mat_<double>(1,3,b);
		f = cMat(re,im);

		N = f.rows*f.cols;
		F = f.clone();
		temp1 = cMat(1,N);
		temp2 = cMat(N,1);

		temp1 = cv::stepVector(1,1,N);
		temp2 = transpose(temp1);
		cout << "N = " << N << endl;
		cout << "temp1 = \n" << temp1 << endl;
		cout << "temp2 = \n" << temp2 << endl;

		c = std::complex<double>(0,-2*pi/double(N));
		cout << "c = " << c << endl;

		int k = 0;

		temp2 = temp2*c;
		cv::exp(temp2,temp3);
		cout << temp3 << endl;
		cout << f << endl;
		//temp3 = f*temp3;
		//d = cv::complex(temp3);
		//pre = F.ptrReal(k);
		//pim = F.ptrImag(k);
		//*pre = d.real();
		//*pim = d.imag();

		//cout << "F = \n" << F << endl;
}


void test3()
{
	Mat_<double> m,m1,m2;

	m = Mat_<double>::zeros(3,4);
	m1 = m.clone();
	m2 = m.clone();
	cout << "m = \n" << m << endl;
	cout << "m1 = \n" << m1 << endl;
	cout << "m2 = \n" << m2 << endl;
	cout << endl;

	cv::randu(m,0,2);
	cout << "m = \n" << m << endl;
	cout << endl;

	cv::max(m,1);
	cout << "m = \n" << m << endl;
	cout << endl;

	//cv::randu(m1,0,2);
	//cv::randu(m2,0,2);
	cout << "m1 = \n" << m1 << endl;
	cout << "m2 = \n" << m2 << endl;

	Mat_<double> temp = max(m1,m2);
	cout << "temp = \n" << temp << endl;
	cout << endl;




}


int main()
{
	test1();
	//test2();
	//test3();







	return 0;
}
