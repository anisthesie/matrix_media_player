#include "converter.h"

using namespace I2A;

/*-----------------------------------------------------------------------------
Return Value : Nothing
Description  : Single argument constructor for the converter class
-----------------------------------------------------------------------------*/

constexpr int MAX_SIZE = 900;


Converter::Converter(cv::Mat& p_image, bool color, bool pixelise, bool resize) :
	square_size(10UL),
	ascii_image(""),
	color(color),
	resize(resize),
	pixelise(pixelise) {

	coloured_image = p_image;
	cv::cvtColor(p_image, image, cv::COLOR_BGR2GRAY);

	if (image_is_valid()) {

		if (resize && (image.size().width > MAX_SIZE || image.size().height > MAX_SIZE)) {
			bool horizontal = image.size().width > image.size().height;
			const double resize_ratio = (double)MAX_SIZE / (horizontal ? image.size().width : image.size().height);
			cv::resize(coloured_image, coloured_image, cv::Size(), resize_ratio, resize_ratio);
			cv::resize(image, image, cv::Size(), resize_ratio, resize_ratio );
		}
		convert_image();
	}
}

Converter::Converter(std::string path, bool color, bool pixelise , bool resize) :
    square_size(10UL),
    ascii_image(""),
	color(color),
	resize(resize),
	pixelise(pixelise)
{
    image = imread(path, cv::IMREAD_GRAYSCALE);
	coloured_image = cv::imread(path);

    if (image_is_valid()) {

		if (resize && (image.size().width > MAX_SIZE || image.size().height > MAX_SIZE)) {
			bool horizontal = image.size().width > image.size().height;
			const double resize_ratio = (double)MAX_SIZE / (horizontal ? image.size().width : image.size().height);
			cv::resize(coloured_image, coloured_image, cv::Size(), resize_ratio, resize_ratio);
			cv::resize(image, image, cv::Size(), resize_ratio, resize_ratio);
		}
        convert_image();
    }
}


/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
-----------------------------------------------------------------------------*/
Converter::~Converter()
{

}


/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
-----------------------------------------------------------------------------*/
bool Converter::image_is_valid() const noexcept
{
    return !image.empty();
}


/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
-----------------------------------------------------------------------------*/
void Converter::print_image() const noexcept
{
    std::cout << ascii_image << std::endl;
}


/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
-----------------------------------------------------------------------------*/
void Converter::display_image() const noexcept
{
    cv::namedWindow(window_name);
    cv::imshow(window_name, image);

    cv::waitKey(0); // Wait for any keystroke in the window

    cv::destroyWindow(window_name);
}


/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
-----------------------------------------------------------------------------*/
void Converter::set_square_size(const UInt32 square) noexcept
{
    square_size = square;
}


/*-----------------------------------------------------------------------------
Return Value : Nothing
Description  : 
-----------------------------------------------------------------------------*/
void Converter::convert_image() noexcept
{
	cv::waitKey();
    ascii_image.clear();

    UInt32 row_count = image.rows - (image.rows % square_size);
    UInt32 col_count = image.cols - (image.cols % square_size);
	

    for (UInt32 row = 0UL; row < row_count; row += square_size)
    {
        for(UInt32 col = 0UL; col < col_count; col += square_size)
        {
			ascii_image += average_to_ascii(calculate_average(row, col));
        }

        ascii_image += "\n";
    }
}

cv::String I2A::Converter::get_ascii_image() const {
	return ascii_image;
}

/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
-----------------------------------------------------------------------------*/
average Converter::calculate_average(UInt32 row, UInt32 col) const noexcept {
	average avr;
    UInt32 sum = 0UL;
	UInt32 total = 0;

    for (UInt32 i = 0UL; i < square_size; ++i)
    {
        for(UInt32 j = 0UL; j < square_size; ++j)
        {

            sum += static_cast<UInt32>(image.at<UInt8>(row + i, col + j));
			if (color) {
				auto p = coloured_image.ptr<cv::Point3_<uchar> >(row + i, col + j);

				avr.rgb.r += p->z;
				avr.rgb.g += p->y;
				avr.rgb.b += p->x;

				total++;
			}
        }
    }
	if (color) {
		avr.rgb.r /= total;
		avr.rgb.g /= total;
		avr.rgb.b /= total;
	}
    avr.sum =  (sum) / (square_size * square_size);
	return avr;
}


/*-----------------------------------------------------------------------------
Return Value : 
Description  : 
Note         : Characters here: http://paulbourke.net/dataformats/asciiart/
-----------------------------------------------------------------------------*/
std::string Converter::average_to_ascii(average avr) const noexcept
{
    std::string character = "";
	
	if (color) {
		character += "\x1b[38;2;";
		character += std::to_string(avr.rgb.r);
		character += ";";
		character += std::to_string(avr.rgb.g);
		character += ";";
		character += std::to_string(avr.rgb.b);
		character += "m";
	}

	if (pixelise) {
		if (avr.sum <= 31UL)
		{
			character += "@";
		}
		else if (avr.sum <= 56UL)
		{
			character += "%";
		}
		else if (avr.sum <= 81UL)
		{
			character += "#";
		}
		else if (avr.sum <= 106UL)
		{
			character += "*";
		}
		else if (avr.sum <= 131UL)
		{
			character += "+";
		}
		else if (avr.sum <= 156UL)
		{
			character += "=";
		}
		else if (avr.sum <= 181UL)
		{
			character += "-";
		}
		else if (avr.sum <= 206UL)
		{
			character += ":";
		}
		else if (avr.sum <= 231UL)
		{
			character += ".";
		}
		else
		{
			character += " ";
		}
	}
	else character += "@";

	if(color) character += "\x1b[0m";

    return character;
}
