#include "EdgeDetection.h"

void EdgeDetection::imageFilter(Image &srcImage, Image &dstImage) {
  cv::Mat resultImage;

  // Sobel Filter
  SobelFilter(srcImage, resultImage);
  dstImage.setter(resultImage);
}