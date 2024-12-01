# Group 90
## Project Name
Image Filters

## Team Members
Junle Li
Mingxuan Zhao
Shuai Chen

## Description
Welcome to the Group 90 Image Processing System! This application provides a variety of image processing filters, such as
highpass filter, lowpass filter, bandpass filter, gaussian filter, laplace filter. Users can use different filtering methods by entering different numbers. The final program will display both the original image and the filtered image.

## Features
- Read and display original images and filtered images


```
- Be prompted to select a filter to apply to the image
- Combine multiple image processing
- Save filtered image
- Visualization of analysis results
## Requirements
- Make sure you have opencv installed on Linux
- Make sure Cmake and C++ are installed

## Installation
1. Clone this repository to your system.
`git clone https://gitlab.lrz.de/advprog2024/90.git`
2. If you want to recompile the program, delete the build folder and execute the following command
```
mkdir build && cd build
cmake ..
make
```
3. After compilation, you can run the program using:
```
 ./main 
```
## Visualization of analysis results

1. After run the programm, you can see the analysis of the performance in file gmon.out. Convert it to .txt.
```
gprof -b ./main  gmon.out  > result.txt
vim result.txt
```
2. Visualization of analysis results
```
sudo apt-get install graphviz
chmod +x gprof2dot/gprof2dot.py
git clone https://github.com/jrfonseca/gprof2dot.git
cat result.txt | python3 gprof2dot/gprof2dot.py | dot -Tpng -o output.png
```
Then you can see the visualization of analysis results in file output.png
## Usage
The image processing system works as follows:

1.  The system will load an image from the given input path.
    

2.  You will then be prompted to select a filter to apply to the image:
    - Highpass Filter
    - Lowpass Filter
    - Bandpass Filter
    - Gaussian Filter
    - Laplace Filter
    
3.  After applying the selected filter, the system will save the output image to the specified output path.
    
4.  The system will ask if you want to continue with another filter. You can continue or exit the system.


## Structure
```
├── images_input
├── images_output
├── CMakeLists.txt
├── README.md
├── filters.h
├── UserMenu.h
├── filters.cpp
├── UserMenu.cpp
├── main.cpp

    
```

