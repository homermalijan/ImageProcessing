#include "opencv2/opencv.hpp"
#include <stdio.h>
using namespace cv;

int main( int, char**) {
	//store video (set of images) in a variable
	VideoCapture cap("fg.mp4");
	VideoCapture cap2("bg.mp4");
	namedWindow("output2", 1);

	//loop until the video ends
	for (;;) {
		Mat frame, frame2;
		cap >> frame;
		cap2 >> frame2;

		//loop every pixel of the original video
		for(int i = 0 ; i < frame.rows ; i++){
			for(int j = 0 ; j < frame.cols ; j++){
				//if part of the original video is not a background (foreground == people moving; not green)
				if(!((frame.at<Vec3b>(i,j)[1] == 255) && (frame.at<Vec3b>(i,j)[2] < 30) && (frame.at<Vec3b>(i,j)[0] < 30))){
					//attach it to the background video
					frame2.at<Vec3b>(i,j)[0] = frame.at<Vec3b>(i,j)[0];
					frame2.at<Vec3b>(i,j)[1] = frame.at<Vec3b>(i,j)[1];
					frame2.at<Vec3b>(i,j)[2] = frame.at<Vec3b>(i,j)[2];
				}
			}
		}

		//show output
		imshow("output2", frame2);
		if(waitKey(30) >= 0) break;
	}

	return 0;
}//close main
