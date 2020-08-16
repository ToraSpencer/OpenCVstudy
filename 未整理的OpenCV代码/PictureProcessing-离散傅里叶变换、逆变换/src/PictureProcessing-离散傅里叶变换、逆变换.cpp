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
		cv::transpose(temp1,temp2);
		c = std::complex<double>(0,-2*pi/double(N));
		temp2 = temp2*c;
		cv::exp(temp2,temp2);
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
	cv::transpose(a,b);
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


int main()
{
	double a[3] = {1,2,3};
	double b[3] = {4,5,6};
	Mat_<double> re = Mat_<double>(1,3,a);
	Mat_<double> im = Mat_<double>(1,3,b);
	cMat f = cMat(re,im);

	int N = f.rows*f.cols;
	cMat F = f.clone();
	cMat temp1 = cMat(1,N);
	cMat temp2 = cMat(N,1);

	temp1 = cv::stepVector(0,1,N-1);
	cv::transpose(temp1,temp2);
	cout << N << endl;
	cout << temp1 << endl;
	cout << temp2 << endl;



	return 0;
}
