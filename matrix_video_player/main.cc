#include <iostream>

#include "video_player.h"
#include "input_parser.h"

inline void print_help() {
	std::cout << "Usage: mxvp [Options..] (File)" << std::endl
		<< "Options:" << std::endl
		<< "\t --no-color  : Prints without color" << std::endl
		<< "\t --no-pixels : Prints everything with the same character (@)" << std::endl
		<< "\t --no-resize : Doesn't resize the frames to fit the console" << std::endl
        << "\t --rand      : Print with random characters" << std::endl
		<< "\t --file (file path) : Input file path, image or video" << std::endl;
}

int main(int argc, char **argv) {

	// Enable ANSI for windows cmd.
    #ifdef WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= 0x0004;
	SetConsoleMode(hOut, dwMode);
    #endif

	InputParser input(argc, argv);
	if (input.cmdOptionExists("-h")) {
		print_help();
		return 1;
	}
	srand(time(0));

	const bool& color = !input.cmdOptionExists("--no-color");
	const bool& pixelise = !input.cmdOptionExists("--no-pixels");
	const bool& resize = !input.cmdOptionExists("--no-resize");
	const bool& rand = input.cmdOptionExists("--rand");

	const std::string &filename = input.getCmdOption("--file");
	if (!filename.empty()) {
		cv::Mat mat = cv::imread(filename);
		if (mat.empty()) {
			I2A::Video video(filename, color, pixelise, resize, rand);
			return 0;
			}

		
		I2A::Converter converter(mat, color, pixelise, resize, rand);
		converter.print_image();
	}
	else print_help();
	return 0;
}