#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
	CvCapture* capture = cvCaptureFromCAM(0);
  //  Mat img = imread("C:/Users/Public/Pictures/Sample Pictures/1.jpg");//컬러이미지를 넣음
	Mat frame;
	Mat gray, dst_norm, dst_norm_scaled;
	frame = cvQueryFrame(capture);
	cvtColor(frame, gray, CV_BGR2GRAY); 
	Mat dst = Mat::zeros(gray.size(), CV_32FC1);
	int thresh = 100;
	while(capture)
	{
		frame = cvQueryFrame(capture);
		cvtColor(frame, gray, CV_BGR2GRAY);
		Canny(gray, gray, 50, 300, 3);
		imshow("Color", frame);
		imshow("Gray", gray);
		if(cvWaitKey(33) == 27)
			break;
	}
	waitKey(0);
	cvReleaseCapture(&capture);
	cvDestroyWindow("Test");
	return 0;
}