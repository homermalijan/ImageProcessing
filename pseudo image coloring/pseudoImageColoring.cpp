#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

//Global variables
Mat src, src_gray, base;

int evaluateRed(int i, int j){
  if(src_gray.at<uchar>(i,j) > 250) src_gray.at<uchar>(i,j) = 250;
  return base.at<Vec3b>(src_gray.at<uchar>(i,j)*2,1)[2];
  //return 0;
}

int evaluateGreen(int i, int j){
  if(src_gray.at<uchar>(i,j) > 250) src_gray.at<uchar>(i,j) = 250;
  return base.at<Vec3b>(src_gray.at<uchar>(i,j)*2,1)[1];
  //return 0;
}

int evaluateBlue(int i, int j){
  if(src_gray.at<uchar>(i,j) > 250) src_gray.at<uchar>(i,j) = 250;
  return base.at<Vec3b>(src_gray.at<uchar>(i,j)*2,1)[0];
  //return 0;
}

int main( int, char** argv ){
  /// Load an image
  src = imread(argv[1], 1);
  src_gray = imread(argv[1], 0);
  imshow("show",src);
  imwrite("map.jpg", src);
  imwrite("map.jpg", src_gray);

  base = imread("colors.jpg", 1);

  printf("%d %d", base.rows, base.cols);

  for(int i = 0 ; i < src_gray.rows ; i++){
    for(int j = 0 ; j < src_gray.cols ; j++){
      if(src_gray.at<uchar>(i,j)>=190){
        src.at<Vec3b>(i,j)[2] = evaluateRed(i,j);
        src.at<Vec3b>(i,j)[1] = evaluateGreen(i,j);
        src.at<Vec3b>(i,j)[0] = evaluateBlue(i,j);
      }
    }
  }

  imwrite("output.jpg", src);
  imshow("output.jpg", src);
  waitKey(0);
}
