#ifndef COMBINEFILTER_HPP
#define COMBINEFILTER_HPP

#include "FilterInterface.h"

class CombineFilter : public FilterInterface {
private:
  size_t getUserChoice();

public:
  void imageFilter(Image &srcImage, Image &dstImage) override;
};

#endif // COMBINEFILTER_HPP