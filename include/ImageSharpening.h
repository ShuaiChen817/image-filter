#ifndef IMAGESHARPENING_HPP
#define IMAGESHARPENING_HPP

#include "FilterInterface.h"

class ImageSharpening : public FilterInterface {
private:
  int getUserChoice();

public:
  void imageFilter(Image &srcImage, Image &dstImage) override;
};

#endif // IMAGESHARPENING_HPP