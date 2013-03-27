#include "highgui.h"
// not working
int g_slider_position = 0;
CvCapture* g_capture= NULL;
void onTrackbarSlide(int pos) {
  cvSetCaptureProperty(
		       g_capture,
		       CV_CAP_PROP_POS_FRAMES,
		       pos
		       );
}

int main( int argc, char** argv ) {
  cvNamedWindow( "Tracking", CV_WINDOW_AUTOSIZE );
  g_capture = cvCreateFileCapture( argv[1] );
  int frames = (int) cvGetCaptureProperty(
					  g_capture,
					  CV_CAP_PROP_FRAME_COUNT
					  );
  if( frames!= 0 ) {
    cvCreateTrackbar(
		     "Position",
		     "Tracking",
		     &g_slider_position,
		     frames,
		     onTrackbarSlide
		     );
  }
  IplImage* frame;
  // While loop (as in Example 2) capture & show video
  while(1) {
    frame = cvQueryFrame( g_capture );
    if( !frame ) break;
    cvShowImage( "Tracking", frame );
    char c = cvWaitKey(33);
    if( c == 27 ) break;
  }
  cvReleaseCapture( &g_capture );
  cvDestroyWindow( "Tracking" );

  // Release memory and destroy window

  return(0);
}

