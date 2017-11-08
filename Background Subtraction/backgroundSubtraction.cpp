#include "opencv2/opencv.hpp"
#include <stdio.h>
using namespace cv;

int main( int, char**) {
Mat frame1, frame2, original;
	//store video (set of images) in a variable
	VideoCapture cap("vid.avi");
	cap >> frame1;
	cvtColor( frame1, frame1, CV_BGR2GRAY );
	imwrite("1.jpg", frame1);

	//loop until the video ends
	for (;;) {
		cap >> frame2;
		Mat tempFrame;
		imshow("original", frame2);
		cvtColor(frame2, frame2, CV_BGR2GRAY );

		tempFrame = frame2;
		imwrite("2.jpg", frame2);
		tempFrame = abs(frame1 - frame2);
		
		//loop every pixel of the original video
		for(int i = 0 ; i < frame1.rows ; i++){
			for(int j = 0 ; j < frame1.cols ; j++){
				if(abs(frame1.at<uchar>(i,j) - frame2.at<uchar>(i,j)) > 50)
					tempFrame.at<uchar>(i,j) = 0;
				else
					tempFrame.at<uchar>(i,j) = 255;
			}
		}

		imwrite("3.jpg", tempFrame);
		//show output
		imshow("output", tempFrame);

		frame1 = frame2;
		if(waitKey(30) >= 0) break;
	}
	return 0;
}//close main