# Matrix Media Player


Matrix Media Player is command line tool that converts videos and images to ascii art in the command line.
It can record the output and write to a video file.

## Building

The project requires OpenCV 3.0 or later.
Install OpenCV in Visual Studio using your method of choice. [(See vcpkg)](https://github.com/microsoft/vcpkg)

Clone this repository and open it in Visual Studio.

## Usage

For the moment the program only works on Windows. Maybe someone will port it to linux?

```
Usage: mxvp [Options..] (File)
Options:
         --no-color  : Prints without color
         --no-pixels : Prints everything with the same character (@)
         --no-resize : Doesn't resize the frames to fit the console
         --file (file path) : Input file path, image or video
```
Resize the command window so that the picture fits perfectly, when the recording starts do not move the window and keep it focused until the recording stops.
If you have problems create the video file, try running the program with admin privileges.

# Examples
### Video Default                          //    Video --no-pixels
![haha](examples/video-default.gif)  ![haha](examples/video-nopixels.gif)

# Images

### Default
![Default](examples/default.png)
### --no-pixels
![--no-pixels](examples/no-pixels.png)
### --no-color
![--no-color](examples/no-color.png)


