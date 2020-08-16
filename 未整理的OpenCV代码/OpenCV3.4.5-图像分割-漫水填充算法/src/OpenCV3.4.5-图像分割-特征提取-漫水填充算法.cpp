#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void test1()
{
	Mat src,dst;
	Rect r;

	src = imread("/Users/wuhan/Downloads/buliding.jpg");
	if(!src.data)
	{
		printf("the image input is empty!");
		return ;
	}

	dst = src.clone();

	// 执行漫水填充染色；
	floodFill(dst,
			Point(50,300),				// 种子坐标
			Scalar(0,0,255), 		// 要染的颜色
			&r, 						//
			Scalar(20,20,20), 			// 负差最大值。
			Scalar(20,20,20));			// 正差最大值

	imshow("original image", src);
	imshow("operated image", dst);

	waitKey(0);
}


int main()
{
	test1();

	return 0;
}
