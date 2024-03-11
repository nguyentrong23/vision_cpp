#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{   
    std::cout << "Hello World!\n";
    Mat img = imread("temp_best.png");
    namedWindow("img", WINDOW_NORMAL);
    imshow("img", img);
    waitKey(0);
    return 0;

}