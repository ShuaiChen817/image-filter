#ifndef IMAGEINTERFACE_HPP
#define IMAGEINTERFACE_HPP

#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

// Image interface class
class ImageInterface {
protected:
  cv::Mat _image;

public:
  ImageInterface(const std::string &path);

  ImageInterface(const cv::Mat &image);

  // Pure virtual function for loading images from a path
  virtual void load(const std::string &path) = 0;

  virtual void save() const = 0;

  cv::Mat getter();

  // Setter function for the image
  void setter(const cv::Mat &image);

  // Virtual destructor with default implementation
  virtual ~ImageInterface() = default;
};

#endif // IMAGEINTERFACE_HPP