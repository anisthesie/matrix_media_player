#pragma once
#include "converter.h"
#include "screenshot.h"

#include <vector>

#include <opencv2\opencv.hpp>

#include <Windows.h>

namespace I2A {

	struct win_console {
		HANDLE console_handle;
		DWORD dwBytesWritten = 0;
	};

class Video {

public:
	explicit Video(std::string video_path, bool color = true, bool pixelise = true, bool resize = true);
	explicit Video(cv::VideoCapture& capture, bool color = true, bool pixelise = true, bool resize = true);

private: 
	void init_video(cv::VideoCapture& cap) const;
	void process_frame(cv::Mat& frame) const;

	std::string video_path;
	bool color, pixelise, resize;
	std::vector<std::string>* ascii_frames;
};

}