// this resizes a picture
#include <cv.h>
#include <highgui.h>

IplImage* doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5 ) {
  assert( in->width%2 == 0 && in->height%2 == 0 );
  IplImage* out = cvCreateImage(
				cvSize( in->width/2, in->height/2 ),
				in->depth,
				in->nChannels
				);
  cvPyrDown( in, out );
  return( out );
}

int main( int argc, char** argv ) {
  IplImage* image =cvLoadImage( argv[1] );
  cvNamedWindow( "Example5-in" );
  cvNamedWindow( "Example5-out" );
  cvShowImage( "Example5-in", image );

  IplImage* out =doPyrDown(image);
  // // the next code does the same thing as the function above
  // IplImage* out = cvCreateImage(
  // 				cvSize( image->width/2, image->height/2 ),
  // 				image->depth,
  // 				image->nChannels
  // 				);
  // cvPyrDown( image, out );

  cvShowImage( "Example5-out", out );
  cvReleaseImage( &out );
  cvWaitKey( 0 );
  cvDestroyWindow( "Example5-in" );
  cvDestroyWindow( "Example5-out" );
}

