#ifndef FILTERS_HPP 
#define FILTERS_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

// Filter interface class
class FilterInterface {
public:  // 修改了以下部分
    cv::Mat Image_make_border(const cv::Mat &srcImage);  // 改为public
    cv::Mat Ideal_Low_Kernel(const cv::Mat &padded, float sigma);  // 改为public

    void Ideal_Lowpass_Filter(const cv::Mat &srcImage, cv::Mat &dstImage, float sigma);
    void Ideal_Highpass_Filter(const cv::Mat &srcImage, cv::Mat &dstImage, float sigma);
    void Ideal_Bandpass_Filter(const cv::Mat &srcImage, cv::Mat &dstImage, float sigma_low, float sigma_high);

protected:
    void GaussianFilter(const cv::Mat &srcImage, cv::Mat &dstImage);
    void LaplacianFilter(const cv::Mat &srcImage, cv::Mat &dstImage);

    cv::Mat Frequency_Filter(cv::Mat &padded, const cv::Mat &kernel);
    cv::Mat Ideal_High_Kernel(const cv::Mat &padded, float sigma);
    cv::Mat Ideal_Bandpass_Kernel(const cv::Mat &padded, float sigma_low, float sigma_high);

public:
    virtual void imageFilter(const cv::Mat &srcImage, cv::Mat &dstImage) = 0;
    virtual ~FilterInterface() = default;
};

// Concrete implementation of FilterInterface
class ConcreteFilter : public FilterInterface {
public:
    void imageFilter(const cv::Mat &srcImage, cv::Mat &dstImage) override {
        GaussianFilter(srcImage, dstImage); // Default implementation
    }

    // Publicly expose filtering methods
    using FilterInterface::Ideal_Highpass_Filter;
    using FilterInterface::Ideal_Lowpass_Filter;
    using FilterInterface::Ideal_Bandpass_Filter;
    using FilterInterface::GaussianFilter;
    using FilterInterface::LaplacianFilter;
    using FilterInterface::Image_make_border;  // 公开Image_make_border
    using FilterInterface::Ideal_Low_Kernel;   // 公开Ideal_Low_Kernel
};

#endif // FILTERS_HPP
