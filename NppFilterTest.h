

#ifndef	TEST_NPP_FILTER_CONV_H
#define TEST_NPP_FILTER_CONV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>  
#include <bitset>
#include <limits>
#include <ctime>

#include <stdio.h>
#include <stdlib.h>
#include <atlstr.h>
#include <stdarg.h> 
#include <conio.h>
#include <signal.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/video/video.hpp>  
#include <opencv2/videoio/videoio.hpp>  
#include <opencv2/videoio/legacy/constants_c.h>  
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs/legacy/constants_c.h>  

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <npp.h> // provided in CUDA SDK



#define CV_VERSION_ID	CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
#if defined(_DEBUG)||defined(DEBUG)
#define cvLIB(name) "opencv_" name CV_VERSION_ID "d"
#define RUNNING_MODE_VERBOSE_ON		"DEBUG"
#else
#define cvLIB(name) "opencv_" name CV_VERSION_ID
#define RUNNING_MODE_VERBOSE_ON		"RELEASE"
#endif
#pragma comment(lib, cvLIB("world"))

#pragma comment(lib, "nppc.lib")
#pragma comment(lib, "nppial.lib")
#pragma comment(lib, "nppicc.lib")
#pragma comment(lib, "nppidei.lib")
#pragma comment(lib, "nppif.lib")
#pragma comment(lib, "nppig.lib")
#pragma comment(lib, "nppim.lib")
#pragma comment(lib, "nppist.lib")
#pragma comment(lib, "nppisu.lib")
#pragma comment(lib, "nppitc.lib")
#pragma comment(lib, "npps.lib")

typedef unsigned char byte;
int NppMinMaxTest(void);
int test_nppiFilter(void);

#endif

