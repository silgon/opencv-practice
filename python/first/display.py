#!/usr/bin/python
import cv #Import functions from OpenCV
import sys
ll = sys.argv[1]#"/home/dante/Pictures/gg.jpg"
img = cv.LoadImage(ll)
cv.NamedWindow("Example", cv.CV_WINDOW_AUTOSIZE )
cv.ShowImage("Example", img )
cv.WaitKey(10000)
cv.DestroyWindow("Example")
