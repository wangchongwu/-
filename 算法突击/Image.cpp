#include "Image.h"
#include <math.h>




Image::Image(cv::Mat mat):mat_im(mat)
{
	for (int i = 0; i < 256; i++)
		hist.push_back(0);//初始化直方图

	hasHist = 0;
}


Image::~Image()
{
}

void Image::showInWindow()
{
	if (!mat_im.empty())
	{
		cv::imshow(matPath.c_str(), mat_im);
		cv::waitKey(0);
	}
}

Image Image::imadjust(LimVar input, LimVar output, float gamma)
{
	if(!hasHist)
		getHist();

	int channels = this->mat_im.channels();
	int nRows = mat_im.rows;
	int nCols = mat_im.cols* channels;

	int DNlow =  256*input.low;
	int DNhigh =  256*input.high;

	//gamma校正+灰度压缩
	int highOut = 256 * output.high;
	int lowOut = 256 * output.low;

	for (int row = 0; row < nRows; row++)
	{
		uchar* p = mat_im.ptr<uchar>(row);
		for (int col = 0; col < nCols; ++col)
		{
			if (p[col] < DNlow)
				p[col] = lowOut;
			else if (p[col] > DNhigh)
				p[col] = highOut;
			else
				//p[col] = pow((p[col] - DNlow) / (DNhigh - DNlow) , gamma)* 256*(highOut - lowOut) ;
			{
				p[col] = pow((double)(highOut - lowOut) / (double)(DNhigh - DNlow), gamma)*(p[col] - DNlow) + lowOut;
			}
		}

	}

	return Image(mat_im);


}

LimVar Image::stretchlim(double k1,double k2)
{
	if (!hasHist)
		getHist();
	int channels = this->mat_im.channels();
	int nRows = mat_im.rows;
	int nCols = mat_im.cols* channels;

	int cnt = 0;
	bool flg1 = 0;
	bool flg2 = 0;

	int DNlow = 0;
	int DNhigh = 256;

	for (int i = 0; i < 256; i++)
	{
		cnt += hist[i];
		if ((!flg1) && (cnt > nRows*nCols*(k1)))
		{
			flg1 = 1;
			DNlow = i;
		}
		if ((!flg2) && (cnt > nRows*nCols*(k2)))
		{
			flg2 = 1;
			DNhigh = i;
		}
	}

	return LimVar((double)DNlow/256, (double)DNhigh/256);
}

Image Image::getHistImage()
{
	if (!hasHist)
		getHist();

	int maxVal = 0;
	int minVal = this->mat_im.rows*this->mat_im.cols;
	
	for (int i = 0; i < 255; i++)
	{
		if (hist[i] > maxVal)
			maxVal = hist[i];
		if (hist[i] < minVal)
			minVal = hist[i];
	}

	int histSizer = 255;
	Mat histImg(histSizer + 20, histSizer + 20, CV_8UC3, Scalar(180, 180, 180));

	rectangle(histImg, Rect(Point(10, 10), Point(histSizer + 10, histSizer + 10)), Scalar(50 ,50, 50), -1, 8);

	for (int h = 0; h < histSizer; h++)
	{
		float histVal = hist[h];
		int length = static_cast<int>(histVal*histSizer / maxVal);
		line(histImg, Point(h + 10, histSizer + 10), Point(h + 10, histSizer - length + 10), Scalar(256-h,h, 2*h));
	}

 	//namedWindow("hist", CV_WINDOW_AUTOSIZE);
 	//imshow("hist", histImg);
 	//waitKey(0);
	return Image(histImg);
}

Image Image::equalizeHist()
{
	if (!hasHist)
		getHist();

	int numOfPiexl = mat_im.rows*mat_im.cols;
	int LUT[256];
	LUT[0] = 1.0*hist[0] / numOfPiexl * 255;
	int sum = hist[0];
	for (int i = 1; i <= 255; ++i)
	{
		sum += hist[i];
		LUT[i] = 1.0*sum / numOfPiexl * 255;//累计分布函数（离散形式）
	}

	Mat dstImage = this->mat_im.clone();
	uchar *dataOfSrc = this->mat_im.data;
	uchar *dataOfDst = dstImage.data;
	for (int i = 0; i <= numOfPiexl - 1; ++i)
		dataOfDst[i] = LUT[dataOfSrc[i]];

	return Image(dstImage);




}

Image Image::logTrans()
{
	
}

void Image::getHist()
{
	int channels = this->mat_im.channels();
	int nRows = mat_im.rows;
	int nCols = mat_im.cols* channels;

	if (mat_im.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	
	for (int row = 0; row < nRows; row++)
	{
		uchar* p = mat_im.ptr<uchar>(row);
		for (int col = 0; col < nCols; ++col)
		{
			hist[p[col]]++;
		}
	}
	this->hasHist = 1;
}

