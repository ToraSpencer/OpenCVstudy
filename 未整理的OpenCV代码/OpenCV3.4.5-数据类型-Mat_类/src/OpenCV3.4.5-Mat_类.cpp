#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
using namespace cv;

//test1():Mat_类相比于Mat类新增的方法：
void test1()
{
	cout << "Mat_类新增的方法：" << endl << endl;

	//直接输入元素初始化：
	cout << "小矩阵用(Mat_<type>(rows,cols) << ...)直接罗列元素初始化：" << endl;
	Mat_<double> M11 = (Mat_<double>(3,3) << 1,2,3,4,5,6,7,8,9);
	Mat_<Vec3d> M21 = (Mat_<Vec3d>(2,2) << Vec3d(1,2,3),Vec3d(4,5,6),Vec3d(0,-1,2),Vec3d(9,2,3));
	cout << "M1 = \n" << M11 << endl;
	cout << "Mat_<Vec3d> M21 = \n" << M21 << endl;
	cout << endl;

	//直接用括号来索引矩阵元素。
	cout << "直接用单数索引、位置索引来访问、修改Mat_矩阵的元素：" << endl;
	cout << "注意单数索引从(0)开始，位置索引从(0,0)开始" << endl;
	M11(7) = 88;
	M11(2,2) = 99;
	cout << "M11(7) = 88; M11(2,2) = 99; M1 = \n" << M11 << endl;
	cout << endl;



	cout << endl;
}

//test2():Mat_类和Mat类的相互转化：
void test2()
{
	cout << "test2():Mat_类和Mat类的相互转化：" << endl << endl;

	Mat M21 = Mat::ones(2,3,CV_32FC2);
	Mat_<Vec2f> M22 = (Mat_<Vec2f>)M21;
	cout << "M22(1,2) = " << M22(1,2) << endl;


	cout << endl;
}

//test3():Mat_类的构造函数：
void test3()
{
	cout << "test3():Mat_类的构造函数：" << endl << endl;

	//多通道的Mat_类对象构造函数：
	cout << "多通道的Mat_类对象构造函数：" << endl;
	Mat_<Vec4d> M31(2,3,Scalar(1,2,3,4));
	cout << "Mat_<Vec4d> M31(2,3,Scalar(1,2,3,4)) = \n" << M31 << endl;

}

//test4():作用于Mat_对象的cv函数
void test4()
{
	cout << "test4():作用于Mat_对象的cv函数" << endl << endl;

	Mat_<double> M41 = Mat_<double>::ones(3,4);
	randu(M41,0,1);
	cout << "M41 = \n" << M41 << endl;
	cout << endl;



}

//test5():返回Mat_对象的方法。
void test5()
{
	cout << "test5():返回Mat_对象的方法。" << endl << endl;

	//Mat_<_Tp> Mat_<_Tp>::zeros(int rows, int cols)
	cout << "Mat_类重写了Mat类的zeros(),ones(),eye()方法，不需要指定矩阵的type：" << endl;
	Mat_<double> M2 = Mat_<double>::ones(5,5);
	cout << "M2 = \n" << M2 << endl;
	cout << endl;

}

int main(int argc, char** argv)
{
	test1();
	//test2();
	//test3();
	//test4();
	//test5();


    return 0;
}
