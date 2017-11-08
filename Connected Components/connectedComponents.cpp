#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

//Global variables
Mat src, binaryMat, temp, cnt;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
int **equivalence;
int rowCount, colCount;

int getLast(int index){
  for(int i = 0 ; i < colCount ; i++){
    if(equivalence[index][i] == 0) return i;
  }
  return 0;

}

void printEquivalence(){
  for(int i = 0 ; i < rowCount ; i++){
    if(equivalence[i][0] == 0 ) continue;
    for(int j = 0; j < colCount ; j++){
      if(equivalence[i][j] == 0) break;
      printf("%d ", equivalence[i][j]);
    }
    printf("\n");
  }
}

int getMin(int index){
  int temp = equivalence[index][0];
  for(int i = 1 ; i < colCount ; i++){
    if(equivalence[index][i] == 0) break;
    if(temp > equivalence[index][i]) temp = equivalence[index ][i];
  }
  return temp;
}


void binarize(){
  for(int i = 0 ; i < rowCount ; i++){
    for(int j = 0 ; j < colCount ; j++){
      if(binaryMat.at<uchar>(i, j) != 255) binaryMat.at<uchar>(i, j) = 0;
    }
  }
}

int main( int, char** argv ){
  /// Load an image
  src = imread(argv[1], 0);
  if( src.empty()) return -1;

  blur(src, src, Size(7,7));

  Mat binaryMat(src.size(), src.type());
  threshold(src, binaryMat, 252, 255, THRESH_BINARY);
  binarize();
  imshow("binarized.jpg", binaryMat);
  imwrite("binarized.jpg", binaryMat);

  rowCount = binaryMat.rows;
  colCount = binaryMat.cols;
  int component[(int)binaryMat.rows][(int)binaryMat.cols], counter = 1;

  equivalence = (int**)malloc(rowCount*sizeof(int*));
  for(int i = 0 ; i < colCount ; i++){
    equivalence[i] = (int*)malloc(colCount*sizeof(int));
  }

  for(int i = 0 ; i < rowCount ; i++){
      for(int j = 0 ; j < colCount ; j++){
        equivalence[i][j] = 0;
      }
  }

  for(int i = 0; i < binaryMat.rows ; i++){
    for(int j = 0; j < binaryMat.cols ; j++){
      if(binaryMat.at<uchar>(i, j) == 0){
        if(i!=0 && component[i-1][j]!=0) {
           component[i][j] = component[i-1][j];
           if(j!=0 && component[i][j-1]!=0 && (component[i][j-1] != component[i-1][j])) {
             equivalence[component[i-1][j]][getLast(component[i-1][j])] = component[i][j-1];
           }
         }
         else if(j!=0 && component[i][j-1]!=0){
           component[i][j] = component[i][j-1];
           if(i!=0 && component[i-1][j]!=0 && component[i-1][j] != component[i][j-1])
             equivalence[component[i][j-1]][getLast(component[i][j-1])] = component[i-1][j];
         }
         else {
           equivalence[counter][0] = counter;
           component[i][j] = counter++;
         }
      } else component[i][j] = 0;
    }//close for
  }//close for

  printEquivalence();

  binaryMat = 255 - binaryMat;
  findContours(binaryMat, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  src = imread(argv[1]);

  for( size_t i = 0; i < contours.size(); i++ ) {
    approxPolyDP( Mat(contours[i]), contours_poly[i], 45, true );
    boundRect[i] = boundingRect( Mat(contours_poly[i]) );
  }
   
  for( size_t i = 0; i< contours.size(); i++ ) {
    rectangle( src, boundRect[i].tl(), boundRect[i].br(), Scalar(255,0,0), 2, 8, 0 );
  }

 imshow("output", src);
 imwrite("output.jpg", src);
   /*eotry*/

  Mat temp = imread(argv[1]);
  for(int i = 0; i < temp.rows ; i++){
    for(int j = 0; j < temp.cols ; j++){
  //     if(component[i][j] == 345) temp.at<Vec3b>(i,j)[1] = 255;
  //     if(component[i][j] == 345) temp.at<Vec3b>(i,j)[2] = 0;
  //     if(component[i][j] == 345) temp.at<Vec3b>(i,j)[0] = 0;
  //     if(component[i][j] == 16) temp.at<Vec3b>(i,j)[0] = 0;
  //     if(component[i][j] == 16) temp.at<Vec3b>(i,j)[2] = 255;
  //     if(component[i][j] == 16) temp.at<Vec3b>(i,j)[1] = 0;
    }//close for
  }//close for

  // imwrite("hehe.jpg",temp);

  waitKey(0);

  return 0;
}
