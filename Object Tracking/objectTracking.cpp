#include "opencv2/opencv.hpp"
#include <stdio.h>
using namespace cv;

int main( int, char**) {
	//store video (set of images) in a variable
	VideoCapture cap("balls.mp4");
	Mat outputFrame;
	namedWindow("video", 1);
	cap >> outputFrame;
	cvtColor(outputFrame, outputFrame, CV_BGR2GRAY);

	//fill outputFrame with black
	for(int i = 0 ; i < outputFrame.rows ; i++){
		for(int j = 0 ; j < outputFrame.cols ; j++){
			outputFrame.at<uchar>(i,j) = 0;
		}
	}

	//loop until the video ends
	for (;;) {
		Mat frame, frame2;
		cap >> frame;

		cvtColor(frame, frame, CV_BGR2GRAY);

		//remove the other ball
		for(int i = 0 ; i < frame.rows ; i++){
			for(int j = 0 ; j < frame.cols ; j++){
				if(frame.at<uchar>(i,j) > 120) frame.at<uchar>(i,j) = 255;
			}
		}

		//append the position of the remaining ball to the outputFrame
		for(int i = 0 ; i < frame.rows ; i++){
			for(int j = 0 ; j < frame.cols ; j++){
				if(frame.at<uchar>(i,j) != 255) outputFrame.at<uchar>(i,j) = 255;
			}
		}

		//show output
		imshow("video", frame);
		imshow("output", outputFrame);
		imwrite("output.jpg", outputFrame);
		if(waitKey(30) >= 0) break;
	}


	return 0;
}//close main
