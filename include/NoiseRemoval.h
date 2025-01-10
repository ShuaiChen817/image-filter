#ifndef NOISEREMOVAL_HPP
#define NOISEREMOVAL_HPP

#include "FilterInterface.h"

class NoiseRemoval : public FilterInterface {
private:
  int getUserChoice();

public:
  void imageFilter(Image &srcImage, Image &dstImage) override;
};

#endif // NOISEREMOVAL_HPP