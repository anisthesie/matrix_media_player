#ifndef CONVERTER_H
#define CONVERTER_H

// STL Includes
#include <string>

// opencv Includes
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Project Includes
#include "converter-types.h"

/*-----------------------------------------------------------------------------
Description  : Top level class used primarily to convert an image into an ascii
                 representation of that image.
-----------------------------------------------------------------------------*/
namespace I2A
{
	struct rgb {
		int r, g, b;
	};
	struct average {
		UInt8 sum;
		rgb clr;
	};
    class Converter
    {
        public:
			cv::String get_ascii_image() const;
            explicit Converter(std::string path, bool color, bool pixelise = true, bool resize = true);
			explicit Converter(cv::Mat& image, bool color, bool pixelise = true, bool resize = true, bool rand = false);

            virtual ~Converter();

            bool image_is_valid() const noexcept;

            void print_image() const noexcept;
            void display_image() const noexcept;

            void set_square_size(const UInt32 square) noexcept;

        private:
			const std::string window_name = "Matrix player";
            void convert_image() noexcept;
            average calculate_average(UInt32 row, UInt32 col) const noexcept;
			std::string average_to_ascii(average avr) const noexcept;

            cv::Mat image, coloured_image;
            UInt32 square_size;
            std::string ascii_image;
			bool color, resize, pixelise, rand;
    };
};

#endif