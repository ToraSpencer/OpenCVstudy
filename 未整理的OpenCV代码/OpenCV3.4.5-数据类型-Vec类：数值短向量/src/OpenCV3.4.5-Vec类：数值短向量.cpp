#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

//Vec<_Tp,cn>类模板继承自Mat<_Tp,cn,1>类模板，表示元素数量为cn的列向量。
//Vec3b == Vec<uchar,3>
//Vec3f == Vec<float,3>
//Vec3d == Vec<double,3>
//RGB图像提取出的3通道Mat矩阵的元素数据类型就是Vec3x

//test1：Vec类的构造函数：
void test1()
{
	cout << "test1：Vec类的构造函数：" << endl << endl;

	cout << "格式：Vec<type,通道数>" << endl;

	Vec<int,1> v11(1);
	cout << "Vec<int,1> v11(1) = " << v11 << endl;

	Vec<float,2> v12(5,6);
	cout << "Vec<float,2> v12(5,6) = " << v12 << endl;

	Vec3d v13(1,2,3);
	cout << "Vec3d v13(1,2,3) = " << v13 << endl;

	cout << endl;
}

//test2:Vec类的成员数据：
void test2()
{
	cout << "test2:Vec类的成员数据：" << endl << endl;

	Vec<int,1> v21(1);
	Vec3d v22(1,2,3);

	cout << "v21.channels = " << v21.channels << endl;
	cout << "v22.channels = " << v22.channels << endl;
	cout << endl;

	cout << "v22.cols = " << v22.cols << endl;
	cout << "v22.rows = " << v22.rows << endl;
	cout << endl;




	cout << endl;
}


int main(int argc, char** argv)
{
	test1();
	test2();

    return 0;
}
