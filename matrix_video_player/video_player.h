#pragma once
#include "converter.h"

#ifdef WIN32
#include "screenshot.h"
#include <Windows.h>
#endif

#include <vector>


namespace I2A {

	struct win_console {
#ifdef WIN32
		HANDLE console_handle;
		DWORD dwBytesWritten = 0;
#endif
    };

class Video {

public:
	explicit Video(std::string video_path, bool color = true, bool pixelise = true, bool resize = true, bool rand = false);
	explicit Video(cv::VideoCapture& capture, bool color = true, bool pixelise = true, bool resize = true);

private: 
	void init_video(cv::VideoCapture& cap) const;
	void process_frame(cv::Mat& frame) const;

	std::string video_path;
	bool color, pixelise, resize, rand;
	std::vector<std::string>* ascii_frames;
};

}