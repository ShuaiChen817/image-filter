#include "ImageInterface.h"
#include "opencv2/opencv.hpp"
#include <string>

ImageInterface::ImageInterface(const std::string &path) {
  _image = cv::imread(path);
}

ImageInterface::ImageInterface(const cv::Mat &image) : _image(image) {}

cv::Mat ImageInterface::getter() { return _image; }

void ImageInterface::setter(const cv::Mat &image) { _image = image; }
