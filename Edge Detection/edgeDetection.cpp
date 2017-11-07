#include "opencv2/imgproc/imgproc.hpp"
// #include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray, src_copy;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";

void convert(int i, int j){
  float sum = 0;

  for(int a = i ; a < i+15 ; a++){
    for(int b = j ; b < j+15 ; b++){
      sum += src_gray.at<uchar>(a, b);
    }
  }

  //MEAN
  int mean = sum/225;

  for(int a = i ; a < i+15 ; a++){
    for(int b = j ; b < j+15 ; b++){
      if(src_gray.at<uchar>(a, b) < mean) src_gray.at<uchar>(a, b) = 0;
      else src_gray.at<uchar>(a, b) = 255;
    }
  }
}

void binaryConvert(){
  int a = 0;
  for(int i = 0 ; i < src_gray.rows ; i+=15){
    for(int j = 0 ; j < src_gray.cols ; j+=15){
      convert(i, j);
      a++;
    }
    printf("\n%d", a);
  }

  printf("%d", a);
}

static void CannyThreshold(int, void*){
    int intensity[256], maxVal, minVal, sum;

    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
    imwrite( "canny.jpg", dst );
}

int main( int, char** argv ){
  /// Load an image
  src = imread( argv[1] );
  src_copy = imread( argv[1] , 0);
  if( src.empty() )
    { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  /// convert to binary
  binaryConvert();
  imwrite("binary.jpg", src_copy);
  imshow("Binary Image", src_copy);
  cvMoveWindow("Binary Image", 80, 80);

  /// Create a window
   namedWindow( window_name, WINDOW_AUTOSIZE );
   cvMoveWindow("Edge Map", 500, 50);

  /// Create a Trackbar for user to enter threshold
   createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
   CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}
