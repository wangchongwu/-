#include "image.h"
#include <fstream>
using namespace std;
int main()
{
	ifstream fid("C:\\Users\\wcw\\Desktop\\PCO-20170228_205534277.dat", ios::binary);

	fid.seekg(200, ios::beg);
	char* data = new char[1024 * 1028 * 2];
	//	fid.seekg(200);
	fid.read(data, 1024 * 1028 * 2);

	cv::Mat matIm(1024, 1028, CV_16UC1, data, 0);

	//cout << matIm.at<ushort>(0, 1);
	//imshow("", matIm);
	//cv::waitKey(0);

	cv::Mat im;
	matIm.convertTo(im, CV_8UC1);

	Image img(im);
	//im.showInWindow();

	//LimVar input = img.stretchlim(0.02, 0.98);
	//Image im2 = img.imadjust(input, LimVar(0, 0.8), 1.5);
	//imshow("", im2.mat_im);
	//cv::waitKey();

	imshow("原直方图",img.getHistImage().mat_im);
	cv::waitKey();
	imshow("均衡化", img.equalizeHist().mat_im);
	cv::waitKey();
	imshow("直方图均衡化后直方图", img.equalizeHist().getHistImage().mat_im);
	cv::waitKey();
}