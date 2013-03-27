#include <cv.h>
#include <highgui.h>

IplImage* doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5 ) {
  // assert( in->width%2 == 0 && in->height%2 == 0 );
  IplImage* out = cvCreateImage(
				cvSize( in->width/2, in->height/2 ),
				in->depth,
				in->nChannels
				);
  cvPyrDown( in, out );
  return( out );
}

IplImage* doCanny(IplImage* in,double lowThresh,double highThresh, double aperture) {
  IplImage* out = cvCreateImage(
				cvGetSize( in ),
					IPL_DEPTH_8U,
					1
				);
  cvCanny( in, out, lowThresh, highThresh, aperture );
  return( out );
}

int main( int argc, char** argv ) {
  IplImage* image =cvLoadImage( argv[1] );
  cvNamedWindow( "in" );
  cvShowImage( "in", image );

  IplImage* out1 =doPyrDown(image);
  IplImage* out2 = doCanny( image, 10, 200, 3 );
  cvNamedWindow( "out1" );
  cvNamedWindow( "out2" );

  cvReleaseImage( &image );
  cvShowImage( "out1", out1 );
  cvReleaseImage( &out1 );
  cvShowImage( "out2", out2 );
  cvReleaseImage( &out2 );
  cvWaitKey( 0 );
  cvDestroyWindow( "in" );
  cvDestroyWindow( "out1" );
  cvDestroyWindow( "out2" );
}

