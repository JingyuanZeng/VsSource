#include "pch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

const char* keys =
"{help h usage ? | | Usage examples: \n\t\t./mask-rcnn.out --image=traffic.jpg \n\t\t./mask-rcnn.out --video=sample.mp4}"
"{image i        |<none>| input image   }"
"{video v       |<none>| input video   }"
;
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Use this script to show frames in OpenCV.");
	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	// Open a video file or an image file or a camera stream.
	string strOld, str, outputFile;
	VideoCapture cap;

	Mat frame;
	// Create a window
	static const string kWinName = "showFrame_ZJY";
	namedWindow(kWinName, WINDOW_NORMAL);

	// Get the video writer initialized to save the output video
	if (parser.has("video")) {
		str = parser.get<String>("video");
		ifstream ifile(str);
		if (!ifile) throw("error");
		cap.open(str);
	}
	else { cap.open(0); }

	// Process frames.
	while (1) {
		cap >> frame;
		// Stop the program if reached end of video
		if (frame.empty()) {
			cout << "Reach the end of the video !!!" << endl;
			break;
		}
		imshow(kWinName, frame);
		char c = waitKey(33);
		if (c == 27) break;
		cv::waitKey(1000);
	}
	cap.release();
	return 0;
}

