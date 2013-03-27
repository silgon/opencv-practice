#include <cv.h>
#include <highgui.h>

const int frame_timer(1);

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
  cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
  CvCapture* capture;
  cvNamedWindow("Canny",CV_WINDOW_AUTOSIZE);

  capture = cvCreateCameraCapture(0); // inside the function is the id of the camera, your first camera is usually the number 0, the second 1 and so on
  IplImage* frame;
  IplImage* frame_canny;
  while(1) {
    frame = cvQueryFrame( capture );
    frame_canny=doCanny( frame, 10, 200, 3 );
    if( !frame ) break;
    cvShowImage( "Camera", frame );
    cvShowImage( "Canny", frame_canny );
    char c = cvWaitKey(frame_timer);
    if( c == 27 ) break;
  }
  cvReleaseCapture( &capture );
  cvDestroyWindow( "Camera" );
}
