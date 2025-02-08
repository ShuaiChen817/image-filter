#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "ImageInterface.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <random>
#include <string>
#include "UserMenu.h"

// Image inter face class
class Image : public ImageInterface {
public:
  Image(const std::string &path);

  Image(const cv::Mat &image);

  void addSaltAndPepperNoise(double noiseRatio = 0.2, int blackValue = 0,
                             int whiteValue = 255);

  void addGaussianNoise(double mean = 0.0, double stddev = 20.0);

  void load(const std::string &path) override;

};

#endif // IMAGE_HPP