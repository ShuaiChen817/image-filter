#ifndef FILTERINTERFACE_HPP
#define FILTERINTERFACE_HPP

#include "Image.h"
#include "ImageInterface.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

// filter interface class
class FilterInterface {
protected:
  void GaussianFilter(Image &srcImage, cv::Mat &dstImage);

  void MedianFilter(Image &srcImage, cv::Mat &dstImage);

  void BilateralFilter(Image &srcImage, cv::Mat &dstImage);

  void LaplacianFilter(Image &srcImage, cv::Mat &dstImage);

  void SobelFilter(Image &srcImage, cv::Mat &dstImage);

  cv::Mat Image_make_border(cv::Mat &srcImage);

  void Shifttransfunction(cv::Mat &plane0, cv::Mat &plane1);

  cv::Mat Frequency_Filter(cv::Mat &padded, cv::Mat &blur);

  cv::Mat Ideal_Low_Kernel(cv::Mat &padded, float sigma);

  void Ideal_Lowpass_Filter(Image &srcImage, cv::Mat &dstImage, float sigma);

  cv::Mat Ideal_High_Kernel(cv::Mat &padded, float sigma);

  void Ideal_Highpass_Filter(Image &srcImage, cv::Mat &dstImage, float sigma);

  cv::Mat Ideal_Bandpass_Kernel(cv::Mat &padded, float sigma_low,
                                float sigma_high);

  void Ideal_Bandpass_Filter(Image &srcImage, cv::Mat &dstImage,
                             float sigma_low, float sigma_high);

public:
  virtual void imageFilter(Image &srcImage, Image &dstImage) = 0;

  virtual ~FilterInterface() = default;
};

#endif // FILTERINTERFACE_HPP