cmake_minimum_required(VERSION 2.6)
project( Camera )
find_package( OpenCV REQUIRED )
add_executable( Camera Camera.cpp )
target_link_libraries( Camera ${OpenCV_LIBS} )
