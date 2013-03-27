#include "highgui.h"

const int frame_timer(1);
int main( int argc, char** argv ) {
  cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE );
  CvCapture* capture;

  // // with this code you can see that you can use weather a movie file or a camera, in the end is the same
  // if( argc==1 ) {
  //   capture = cvCreateCameraCapture(0);
  // } else {
  //   capture = cvCreateFileCapture( argv[1] );
  // }
  // assert( capture != NULL );

  capture = cvCreateCameraCapture(0); // inside the function is the id of the camera, your first camera is usually the number 0, the second 1 and so on
  IplImage* frame;
  while(1) {
    frame = cvQueryFrame( capture );
    if( !frame ) break;
    cvShowImage( "Camera", frame );
    char c = cvWaitKey(frame_timer);
    if( c == 27 ) break;
  }
  cvReleaseCapture( &capture );
  cvDestroyWindow( "Camera" );
}
