# Group.90
## Project Name
Image Filters

## Team Members
- Junle Li
- Shuai Chen
- Mingxuan Zhao

## Description
Welcome to the Group 90 Image Filtering System! This application provides a variety of image processing filters, such as High-pass Filter, Low-pass Filter, Bandpass Filter, Gaussian Filter and Laplace Filter. Users can use different filtering methods by entering different numbers. The final program will display both the original image and the filtered image.

## Features
- Read and display original images and filtered images
- Be prompted to select a filter to apply to the image
- Combine multiple image processing
- Save filtered image
- Visualization of analysis results
## Requirements
- Make sure you have opencv installed on Linux
- Make sure Cmake and C++ are installed
- We recommand the initial setting Parameters as follows:
1. High-pass Filter(Sigma: 20)
2. Low-pass Filter(Sigma: 20)
3. Bandpass Filter(Sigma_low: 20  Sigma_high: 150)


## Installation
1. Clone this repository to your system.
`git clone https://gitlab.lrz.de/advprog2024/90.git`
2. If you want to recompile the program, delete the build folder and execute the following command
```
cd ~/Image_filtering/build
ninja clean
cmake .. -G "Ninja"
ninja
```
3. After compilation, you can run the program using:
```
 ./image_filtering 
```
## Visualization of analysis results

Then you can see the visualization of analysis results in ../Image_filtering/build/images_output.jpg
## Usage
The image processing system works as follows:

1.  The system will load an image from the given input path.
    
2.  You will then be prompted to select a filter to apply to the image:
    
    - High-pass Filter
    - Low-pass Filter
	- Bandpass Filter
	- Gaussian Filter
	- Laplace Filter

3.  After applying the selected filter, the system will save the output image to the specified output path.
    
4.  The system will ask if you want to continue with another filter. You can continue or exit the system.


## Structure
```
├── CMakeLists.txt
├── README.md
├── src
│   ├── filters.h
│   ├── UserMenu.h
│   ├── filters.cpp
│   ├── main.cpp
│   └── UserMenu.cpp
├── images_input
│   └── default.jpg

    
```
- **CMakeLists.txt**: The CMake configuration file used for building the project.
- **README.md**: Documentation file that provides an overview of the project and usage instructions.
- **images_input/default.jpg**: A default input image file used for testing image filtering functionalities.
- **src**: The src directory contains the main source files and headers for the project:
	-   **filters.h**: Header file defining the image filtering functionalities.
	-   **UserMenu.h**: Header file defining the functionalities for the user menu.
	-   **filters.cpp**: Source file implementing the image filtering functionalities.
	-   **UserMenu.cpp**: Source file implementing the user menu functionalities.
	-   **main.cpp**: The main program file, which serves as the entry point and manages the control flow.