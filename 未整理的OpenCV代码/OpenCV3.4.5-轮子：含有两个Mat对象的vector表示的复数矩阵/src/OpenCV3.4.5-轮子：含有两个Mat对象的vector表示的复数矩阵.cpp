#include "cMat.h"
using namespace std;
using namespace cv;

//test1():
void test1()
{
	Mat_<double> I = Mat_<double>::ones(3,3);
	cout << "I = \n" << I << endl;
	Mat_<double> a = 2*pi*I;
	cout << "a = \n" << a << endl;
	Mat_<double> ac = cv::cos(a);
	cout << "cv::cos(a) = \n" << ac << endl;
	Mat_<double> as = cv::sin(a);
	cout << "cv::sin(a) = \n" << as << endl;
	cout << endl;

	cMat b;
	cv::exp(I,b);
	cout << "b = \n" << b << endl;
	cout << endl;

	cMat c;
	cv::exp_i2pi(I,c);
	cout << "c = \n" << c << endl;
}

//test2():
void test2()
{


}

int main()
{
	//test1();
	test2();



	return 0;
}
