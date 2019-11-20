#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main()
{
	CvCapture* capture = cvCaptureFromCAM(0); //영상파일이 아니라 캠코더? 로 찍히는것
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
		cornerHarris( gray, dst, 2, 3, 0.03, BORDER_DEFAULT); //3바이3 공간에서 2는 블럭사이즈 0.03은..?
	//해리스코너에 대한 값이 dst에 들어가있음 

		normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );// 값이 작아서 노멀라이즈 해줌 

	  /// Drawing a circle around corners
	  for( int j = 0; j < dst_norm.rows ; j++ )//dst_norm의 모든 행과 열에 대해서
		 { for( int i = 0; i < dst_norm.cols; i++ )
			  {
				if( (int) dst_norm.at<float>(j,i) > thresh )
				  {
				   circle(frame, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
				  }
			  }
		 }
		imshow("Color", frame);
		if(cvWaitKey(33) == 27)
			break;
	}//while 끝

	waitKey(0);
	cvReleaseCapture(&capture);
	cvDestroyWindow("Test");
	return 0;
}