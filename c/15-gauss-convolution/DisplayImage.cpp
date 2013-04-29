#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;

/// Global variables
Mat src, imGauss, imConv,imResult,detected_edges;

int gauss;
int const max_gauss = 200;
int const kernel_size_gauss=3;
int conv=3;
int const max_conv = 50;
int kernel_size_conv;
Mat kernel_conv;
Point anchor_conv;

int ratio=3;
/** Function Headers */
void getZones( int, void* );

int main( int argc, char** argv )
{
	/// Load an image
	src = imread( argv[1] ,CV_LOAD_IMAGE_GRAYSCALE);

	if( !src.data )
		{ return -1; }

	/// Create windows
	namedWindow( "Result", CV_WINDOW_AUTOSIZE );

	/// Create Trackbar
	createTrackbar( "Gauss GoD\t", "Result",
					&gauss, max_gauss,
					getZones );

	createTrackbar( "Convolution\t", "Result",
					&conv, max_conv,
					getZones );


	/// Default start
	getZones( 0, 0 );

	waitKey(0);
	return 0;
}

/**  @function getZones  */
void getZones( int, void* )
{
	blur( src, imGauss, Size(3,3) );
	Canny( imGauss, imGauss, gauss, gauss*ratio, kernel_size_gauss );
	anchor_conv = Point( -1, -1 );
	/// Update kernel size for a normalized box filter
	kernel_size_conv = conv;
	int delta = 0; // number of pixels added after convolution
	int ddepth = -1; // depth in bits (8bits, 16bits, etc) value -1 is the same as the preceded image
	kernel_conv = Mat::ones( kernel_size_conv, kernel_size_conv, CV_32F )/ (float)(kernel_size_conv*kernel_size_conv);
	filter2D(imGauss, imConv, ddepth , kernel_conv, anchor_conv, delta, BORDER_DEFAULT );
	// std::cout << kernel_conv << std::endl;
	imshow( "Result", imConv);
}

