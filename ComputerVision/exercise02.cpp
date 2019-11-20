#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
	CvCapture* capture = cvCaptureFromCAM(0);
	Mat frame, gray;
	double weight[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}
	frame = cvQueryFrame(capture);
	cvColor(frame, gray, CV_BGR2GRAY);
	Mat gray2 = Mat::zeros(gray.size(), CV_8UC1);

	while(capture)
	{
		frame = cvQueryFrame(capture);
		cvColor(frame, gray, CV_BGR2GRAY);

		for(int j=1; j<gray.row-1; j++)
			for(int i=1; i<gray.cols-1; i++)
			{
				int temp = 0; double sum = 0;//
				for(int k1=-1; k1<=1; k1++)//
					for(int k2=-1; k2<=1; k2++)//
					{
						temp += weight[k1+1][k2+1] * gray.at<unsigned char>(j+k1, i+k2);//컨볼루션 연산(convolution) 
						sum += weight[k1+1][k2+1];//
					}//
					gray2.at<unsigned char>(j, i) = temp/sum;//
			}

			imshow("Color", frame);
			imshow("Gray", gray);
			imshow("Gray2", gray2);

			if(cvWaitKey(33) == 27)
				break;
	}

	waitKey(0);
	cvReleaseCapture(&capture);
	cvDestroyWindow("Color");
	return 0;
}