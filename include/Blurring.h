#ifndef BLURRING_HPP
#define BLURRING_HPP

#include "FilterInterface.h"

class Blurring : public FilterInterface {
private:
  int getUserChoice();

public:
  void imageFilter(Image &srcImage, Image &dstImage) override;
};

#endif // BLURRING_HPP