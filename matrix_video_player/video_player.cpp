#include "video_player.h"

using namespace I2A;

I2A::Video::Video(std::string video_path, bool color, bool pixelise, bool resize, bool rand) :
	 video_path(video_path), color(color), resize(resize), pixelise(pixelise), rand(rand) {
	ascii_frames = new std::vector<std::string>;
	std::cout << "Reading video file..." << std::endl;
	cv::VideoCapture cap(video_path);
	init_video(cap);
}

I2A::Video::Video(cv::VideoCapture& cap, bool color, bool pixelise, bool resize) :
	 color(color), resize(resize), pixelise(pixelise) {
	ascii_frames = new std::vector<std::string>;
	std::cout << "Reading video file..." << std::endl;
	init_video(cap);
}

void I2A::Video::init_video(cv::VideoCapture& cap) const {
	if (!cap.isOpened()) {
		std::cout << "!!! Failed to open file" << std::endl;
		std::exit(-1);
	}
	const double out_fps = cap.get(cv::CAP_PROP_FPS);

	bool skip = false;
	cv::Mat frame;
	std::cout << "Processing frames..." << std::endl;
	while (true) {
		if (!cap.read(frame)) break;
		if (skip) {
			skip = !skip;
			continue;
		}
		process_frame(frame);
	}

	std::cout << std::endl
			  << "Resize the window so that the next picture is perfectly fit in the console" << std::endl
			  << "Press Enter when finished"  << std::endl
			  << "Press Enter to continue" << std::endl;

	std::getchar();
	std::cout << std::endl << ascii_frames->at(std::rand() % ascii_frames->size());
	std::getchar();

	system("cls");
	cv::Size size = hwnd2mat(GetConsoleWindow()).size();
	cv::VideoWriter video_writer;
	video_writer.open("out-video-"+std::to_string(std::rand())+".mp4", -1, out_fps, size, true);
	if (!video_writer.isOpened()) {
		std::cout << "Could not open the output video for write: " << std::endl;
		std::cout << "fps: " << out_fps << std::endl << "size: " << size.height << "x" << size.width << std::endl;
		std::exit(-1);
	}
	for (int i = 0; i < ascii_frames->size(); i++) {
		std::cout << std::endl << ascii_frames->at(i);
		Sleep(10);
		cv::Mat capture = hwnd2mat(GetConsoleWindow());
		video_writer << capture;
	}
	std::cout << "Finished writing video" << std::endl;

	delete(ascii_frames);
}

void I2A::Video::process_frame(cv::Mat & frame) const {
	Converter converter(frame, color, pixelise, resize, rand);
	ascii_frames->push_back( converter.get_ascii_image());
//	std::cout << "Processed frames: " << ascii_frames->size() << std::endl;
}
