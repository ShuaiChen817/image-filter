#ifndef EDGEDETECTION_HPP
#define EDGEDETECTION_HPP

#include "FilterInterface.h"

class EdgeDetection : public FilterInterface {
public:
  void imageFilter(Image &srcImage, Image &dstImage) override;
};

#endif // EDGEDETECTION_HPP