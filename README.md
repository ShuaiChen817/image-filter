# Group.90
## Project Name
Image Filters

## Team Members
Junle Li
Shuai Chen
Mingxuan Zhao

## Description
Welcome to the Group 90 Image Filtering System! This application provides a variety of image processing filters, such as blurring, noise removal, edge detection, image sharpening, and combined filtering.Users can use different filtering methods by entering different numbers. The final program will display both the original image and the filtered image.

## Features
- Read and display original images and filtered images
- Be prompted to select a filter to apply to the image
- Combine multiple image processing
- Save filtered image
- Visualization of analysis results

## Requirements
- Make sure you have opencv installed on Linux
- Make sure Cmake and C++ are installed

## Installation
1. Clone this repository to your system
`git clone https://gitlab.lrz.de/advprog2024/90.git`
2. If you want to recompile the program, delete the build folder and execute the following command
```
cd /path/to/your/project/build  # make sure you are in the build file
rm -rf *                        # delete all files in build 
cmake ..                        
make                            
```
3. After compilation, you can run the program using:
```
 ./main
```
4. After completing a function, you need to “ctrl + c” to force quit once and then re-execute to select another function.
```
 ./main
```
## Visualization of analysis results
Then the system will automatically display both of the original image and the filtered image.
## Usage
The image processing system works as follows:
1.  The system will load an image from the given input path.
    
2.  You will then be prompted to select a filter to apply to the image:
    
    - Blurring
    - Noise Removal
	- Edge Detection
	- Image Sharpening
	- CombineFilter

3.  After executing the programme, the system will automatically display the results.
    
4.  The system will ask if you want to continue with another filter. You can continue or exit the system.


## Structure
```
├── include
│   ├── Blurring.h
│   ├── CombineFilter.h
│   ├── EdgeDetection.h
│   ├── FilterInterface.h
│   ├── Image.h
│   ├── ImageInterface.h
│   ├── ImageSharpening.h
│   ├── NoiseRemoval.h
│   └── UserMenu.h
├── images_input
│   └── default.jpg
├── src
│   ├── Blurring.cpp
│   ├── CombineFilter.cpp
│   ├── EdgeDetection.cpp
│   ├── FilterInterface.cpp
│   ├── Image.cpp
│   ├── ImageInterface.cpp
│   ├── ImageSharpening.cpp
│   ├── NoiseRemoval.cpp
│   └── UserMenu.cpp
├── CMakeLists.txt
├── main.cpp
└── README.md
    
```
- **CMakeLists.txt**: The CMake configuration file used for building the project.
- **README.md**: Documentation file that provides an overview of the project and usage instructions.
- **images_input/default.jpg**: A default input image file used for testing image filtering functionalities.
- **include**: directory contains header files for the C++ project:
	-   **Blurring.h**: Header for the blurring image filter.
	-   **CombineFilter.h**: Header for a filter that combines multiple image 		processing techniques.
	-   **EdgeDetection.h**: Header for the edge detection filter.
	-   **FilterInterface.h**: Header for the interface that all image filters implement.
	-   **Image.h**: Header for an image class that encapsulates image data and operations.
	-   **ImageInterface.h**: Header for an interface for the Image class.
	-   **ImageSharpening.h**: Header for image sharpening filter.
	-   **NoiseRemoval.h**: Header for a filter that removes noise from images.
	-   **UserMenu.h**: Header forUserMenu.
- **src**: The src directory contains the main source files for the project:
	-   **Blurring.cpp**: Implementation of blurring image filter.
	-   **CombineFilter.cpp**: Implementation of the combined filter.
	-   **EdgeDetection.cpp**: Implementation of edge detection filter.
	-   **FilterInterface.cpp**: Implementation of common interface functions for image filters.
	-   **Image.cpp**: Implementation of the Image class.
	-   **ImageInterface.cpp**: Implementation of the Image interface functions.
	-   **ImageSharpening.cpp**: Implementation of image sharpening filter.
	-   **NoiseRemoval.cpp**: Implementation of the noise removal filter.
	-   **UserMenu.cpp**: Implementation of UserMenu.
- **main.cpp**: Executable file.