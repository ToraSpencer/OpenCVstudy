#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	//Mat imread(const string& filename, int flags = 1)
	cout << "imread(图片文件, int flags = IMREAD_COLOR)：一个flags整数值对应着ImreadModes中的枚举常量，以此决定以不同的模式来提取图片文件的数据保存到Mat对象中。" << endl;
	cout << "flags是一个枚举类型，默认取IMREAD_COLOR枚举常量，其值为1，即将图像数据保存为三通道RBG矩阵。" << endl;
	Mat lena = imread("lena.jpg");
	imwrite("/Users/wuhan/Downloads/lena_imwrited.jpg",lena);
	imshow("lena",lena);
	waitKey(0);								 							//延迟x毫秒后关闭窗口，如果x==0则一直不关闭，直到按下任意键。

	cout << "lena.depth() = " << lena.depth() << endl;
	cout << "lena.depth() = 0，表示用默认的IMREAD_COLOR模式保存的图像矩阵一个通道中的数据元素类型为8U，即unchar。" << endl;
	cout << "lena.type() = " << lena.type() << endl;
	cout << "lena.type() = 16 = (3-1)*8+0，表示矩阵类型为CV_8UC3,标准的三通道RGB图像矩阵。" << endl;

    cout << "flag取0表示取ImreadModes中的枚举常量IMREAD_GRAYSCALE，图像数据保存到单通道矩阵中，即保存为灰度图矩阵。" << endl;
	Mat lena_blue = imread("lena.jpg",0);
	imshow("lena blue",lena_blue);
	waitKey(0);

    return 0;
}
