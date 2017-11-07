#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main ( int argc, char** argv ){
  Mat filtered; //temporary varaible for newly computed values
  Mat src = imread( argv[1], 0);  //grayscale

  //check if src image is properly loaded
  if( !src.data ) return -1;

  imshow("Original", src);
  imwrite("original.jpg", src);
  cvMoveWindow("Original", 100, 300);

  int meanFilter1[3][3], meanFilter2[3][3] = 	   {{1,2,1},
                          												{2,4,2},
                          												{1,2,1}},
              						spatialFilter1[3][3] =  {{0,1,0},
                          												{1,-4,1},
                          												{0,1,0}},
              						spatialFilter2[3][3] = {{0,-1,0},
                          												{-1,5,-1},
                          												{0,-1,0}};
  //initialize meanFilter1 into 3x3 matrix of 1s
  for(int i = 0 ; i < 3 ; i++){
    for(int j = 0 ; j < 3 ; j++){
      meanFilter1[i][j] = 1;
    }
  }

//======================================================================================================//
//========================================MEAN FILTER 1=================================================//
//======================================================================================================//

  src = imread( argv[1], 0);  //grayscale
  filtered = imread( argv[1], 0);

  for(int i = 1 ; i < src.rows-1 ; i++){    //traverses the rows of the image source
    for(int j = 1 ; j < src.cols-1 ; j++){  //traverses the cols of the image source
      int temp = 0, sum = 0;

      for(int a = -1 ; a < 2 ; a++){         //traverses the rows of the kernel
        for (int b =  -1 ; b < 2 ; b++){      //traverses the cols of the kernel
          sum += meanFilter1[a + 1][b + 1];         //computes the sum of the values of the kernel
          temp = temp + (meanFilter1[a + 1][b + 1] * src.at<uchar>(i + a, j + b)); //multiplies the corresponding value of the kernel to the current matrix
        }
      }

      filtered.at<uchar>(i,j) = abs(temp/sum); //computes the new value of the target pixel
    }//close for
  }//close for

  //display and save image
  imshow("Mean Filter 1", filtered);
  imwrite("meanFilter1.jpg", filtered);
  cvMoveWindow("Mean Filter 1", 500, 100);

//======================================================================================================//
//========================================MEAN FILTER 1=================================================//
//======================================================================================================//

  src = imread( argv[1], 0);  //grayscale
  filtered = imread( argv[1], 0);

  for(int i = 1 ; i < src.rows-1 ; i++){    //traverses the rows of the image source
    for(int j = 1 ; j < src.cols-1 ; j++){  //traverses the cols of the image source
      int temp = 0, sum = 0;

      for(int a = -1 ; a < 2 ; a++){         //traverses the rows of the kernel
        for (int b =  -1 ; b < 2 ; b++){      //traverses the cols of the kernel
          sum += meanFilter2[a + 1][b + 1];         //computes the sum of the values of the kernel
          temp = temp + (meanFilter2[a + 1][b + 1] * src.at<uchar>(i + a,j + b)); //multiplies the corresponding value of the kernel to the current matrix
        }
      }

      filtered.at<uchar>(i,j) = abs(temp/sum); //computes the new value of the target pixel
    }//close for
  }//close for

  //display and save image
  imshow("Mean Filter 2", filtered);
  imwrite("meanFilter2.jpg", filtered);
  cvMoveWindow("Mean Filter 2", 900, 90);

//======================================================================================================//
//=======================================SPATIAL FILTER 1===============================================//
//======================================================================================================//

  src = imread( argv[1], 0);  //grayscale
  filtered = imread( argv[1], 0);

  for(int i = 1 ; i < src.rows-1 ; i++){    //traverses the rows of the image source
    for(int j = 1 ; j < src.cols-1 ; j++){  //traverses the cols of the image source
      int temp = 0;

      for(int a = -1 ; a < 2 ; a++){         //traverses the rows of the kernel
        for (int b =  -1 ; b < 2 ; b++){      //traverses the cols of the kernel
          temp = temp + (spatialFilter1[a + 1][b + 1] * src.at<uchar>(i + a, j + b)); //multiplies the corresponding value of the kernel to the current matrix
        }
      }

      //if (abs(temp) > 255) temp = 255;
      filtered.at<uchar>(i,j) = abs(temp); //computes the new value of the target pixel

    }//close for
  }//close for

  //display and save image
  imshow("Spatial Filter 1", filtered);
  imwrite("spatialfilter1.jpg", filtered);
  cvMoveWindow("Spatial Filter 1", 500, 400);

//======================================================================================================//
//=======================================SPATIAL FILTER 2===============================================//
//======================================================================================================//

  src = imread( argv[1], 0);  //grayscale
  filtered = imread( argv[1], 0);

  for(int i = 1 ; i < src.rows-1 ; i++){    //traverses the rows of the image source
    for(int j = 1 ; j < src.cols-1 ; j++){  //traverses the cols of the image source
      int temp = 0;

      for(int a = -1 ; a < 2 ; a++){         //traverses the rows of the kernel
        for (int b =  -1 ; b < 2 ; b++){      //traverses the cols of the kernel
          temp = temp + (spatialFilter2[a + 1][b + 1] * src.at<uchar>(i + a, j + b)); //multiplies the corresponding value of the kernel to the current matrix
        }
      }

      //if (abs(temp) > 255) temp = 255;
      filtered.at<uchar>(i,j) = abs(temp); //computes the new value of the target pixel
    }//close for
  }//close for

  //display and save image
  imshow("Spatial Filter 2", filtered);
  imwrite("spatialFilter2.jpg", filtered);
  cvMoveWindow("Spatial Filter 2", 900, 400);

  waitKey(0);
	return 0;
}//end
