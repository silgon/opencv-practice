#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

#define MAX_COUNT 500
char rawWindow[] = "Raw Video";
char opticalFlowWindow[] = "Optical Flow Window";
char imageFileName[32];
long imageIndex = 0;
char keyPressed;

int main() {
	VideoCapture cap(0);

	Mat frame, grayFrames, rgbFrames, prevGrayFrame;
	Mat opticalFlow = Mat(cap.get(CV_CAP_PROP_FRAME_HEIGHT),
						  cap.get(CV_CAP_PROP_FRAME_HEIGHT), CV_32FC3);

	vector<Point2f> points1;
	vector<Point2f> points2;

	Point2f diff;

	vector<uchar> status;
	vector<float> err;

	RNG rng(12345);
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
						  rng.uniform(0, 255));
	bool needToInit = true;

	int i, k;
	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	Size subPixWinSize(10, 10), winSize(31, 31);
	namedWindow(rawWindow, CV_WINDOW_AUTOSIZE);
	double angle;

	while (1) {
		cap >> frame;
		frame.copyTo(rgbFrames);
		cvtColor(rgbFrames, grayFrames, CV_BGR2GRAY);

		if (needToInit) {
			goodFeaturesToTrack(grayFrames, points1, MAX_COUNT, 0.01, 5, Mat(),
								3, 0, 0.04);
			needToInit = false;
		} else if (!points2.empty()) {
			cout << "\n\n\nCalculating  calcOpticalFlowPyrLK\n\n\n\n\n";
			calcOpticalFlowPyrLK(prevGrayFrame, grayFrames, points2, points1,
								 status, err, winSize, 3, termcrit, 0, 0.001);

			for (i = k = 0; i < points2.size(); i++) {
				cout << "Optical Flow Difference... X is "
					 << int(points1[i].x - points2[i].x) << "\t Y is "
					 << int(points1[i].y - points2[i].y) << "\t\t" << i
					 << "\n";

				if ((points1[i].x - points2[i].x) > 0) {
					line(rgbFrames, points1[i], points2[i], Scalar(0, 0, 255),
						 1, 1, 0);

					circle(rgbFrames, points1[i], 2, Scalar(255, 0, 0), 1, 1,
						   0);

					line(opticalFlow, points1[i], points2[i], Scalar(0, 0, 255),
						 1, 1, 0);
					circle(opticalFlow, points1[i], 1, Scalar(255, 0, 0), 1, 1,
						   0);
				} else {
					line(rgbFrames, points1[i], points2[i], Scalar(0, 255, 0),
						 1, 1, 0);

					circle(rgbFrames, points1[i], 2, Scalar(255, 0, 0), 1, 1,
						   0);

					line(opticalFlow, points1[i], points2[i], Scalar(0, 255, 0),
						 1, 1, 0);
					circle(opticalFlow, points1[i], 1, Scalar(255, 0, 0), 1, 1,
						   0);
				}
				points1[k++] = points1[i];

			}

			goodFeaturesToTrack(grayFrames, points1, MAX_COUNT, 0.01, 10, Mat(),
								3, 0, 0.04);

		}

		imshow(rawWindow, rgbFrames);
		imshow(opticalFlowWindow, opticalFlow);

		std::swap(points2, points1);
		points1.clear();
		grayFrames.copyTo(prevGrayFrame);

		keyPressed = waitKey(10);
		if (keyPressed == 27) {
			break;
		} else if (keyPressed == 'r') {
			opticalFlow = Mat(cap.get(CV_CAP_PROP_FRAME_HEIGHT),
							  cap.get(CV_CAP_PROP_FRAME_HEIGHT), CV_32FC3);
		}

	}
}
