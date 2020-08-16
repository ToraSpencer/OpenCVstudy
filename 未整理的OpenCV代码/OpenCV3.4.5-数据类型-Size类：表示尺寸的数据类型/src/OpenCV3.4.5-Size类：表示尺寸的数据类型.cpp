#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

/*
Size类的源代码在opencv2/core/core.hpp中

名字定义：
	Size_<int> = Size2i = Size
	Size_<int64> = Size2l
	Size_<float> = Size2f
	Size_<double> = Size2d

成员数据：
	_Tp height
	_Tp width

构造方法：
	Size_ ()
	Size_ (_Tp _width, _Tp _height)
	Size_ (const Size_ &sz)
	Size_ (const Point_< _Tp > &pt)
 */


//test1():Size类的构造方法
void test1()
{
	cout << "test1：Size类的构造方法：" << endl;
	Size sz = Size(3,4);
	cout << "sz = " << sz << endl;
	cout << endl;



	cout << endl << endl;
}

//利用Size对象规定的尺寸来构造矩阵。
void test2()
{
	cout << "test2：利用Size对象规定的尺寸来构造矩阵：" << endl;
	Size sz = Size(5,6);
	Mat M = Mat(sz,CV_8UC1);
	cout << "M = \n" << format(M,Formatter::FMT_MATLAB) << endl << endl;

	cout << endl << endl;

}

//test3():Size类的成员方法
void test3()
{}

//test4():Size类的重载运算符
void test4()
{
	cout << "test4():Size类的重载运算符" << endl << endl;

	cout << "重载赋值运算符=" << endl;
	Size_<double> size41;
    cout << "size41 = " << size41 << endl;
    Size_<double> size42(3,2);
    cout << "size42 = " << size42 << endl;
    size41 = size42;
    cout << "size41 = size42; size41 = " << size41 << endl;


}


int main(int argc, char** argv)
{
	//test1();
	//test2();
	//test3();
	test4();

    return 0;
}
