#include "filters.h"

// Create border for frequency domain operations
cv::Mat FilterInterface::Image_make_border(const cv::Mat &srcImage) {
    int w = cv::getOptimalDFTSize(srcImage.cols);
    int h = cv::getOptimalDFTSize(srcImage.rows);
    cv::Mat padded;
    cv::copyMakeBorder(srcImage, padded, 0, h - srcImage.rows, 0, w - srcImage.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    padded.convertTo(padded, CV_32FC1);
    return padded;
}

// Apply a frequency domain filter
cv::Mat FilterInterface::Frequency_Filter(cv::Mat &padded, const cv::Mat &kernel) {
    cv::Mat planes[] = {padded, cv::Mat::zeros(padded.size(), CV_32FC1)};
    cv::Mat complexImage;
    cv::merge(planes, 2, complexImage);
    cv::dft(complexImage, complexImage);
    cv::split(complexImage, planes);

    cv::Mat filteredReal, filteredImaginary;
    cv::multiply(planes[0], kernel, filteredReal);
    cv::multiply(planes[1], kernel, filteredImaginary);
    cv::Mat filtered[] = {filteredReal, filteredImaginary};
    cv::merge(filtered, 2, complexImage);
    cv::idft(complexImage, complexImage);
    cv::split(complexImage, planes);

    return planes[0];
}

// Generate an improved low-pass filter kernel (Gaussian-like decay)
cv::Mat FilterInterface::Ideal_Low_Kernel(const cv::Mat &padded, float sigma) {
    cv::Mat kernel(padded.size(), CV_32FC1);
    int centerX = padded.cols / 6 ;
    int centerY = padded.rows / 6 ;

    for (int i = 0; i < padded.rows; i++) {
        for (int j = 0; j < padded.cols; j++) {
            double d = sqrt(pow(i - centerY, 2) + pow(j - centerX, 2));
            kernel.at<float>(i, j) = exp(-(d * d) / (2 * sigma * sigma));
        }
    }

    return kernel;
}

// Apply an ideal low-pass filter
void FilterInterface::Ideal_Lowpass_Filter(const cv::Mat &srcImage, cv::Mat &dstImage, float sigma) {
    if (sigma <= 0) {
        std::cerr << "Error: Sigma must be greater than 0.\n";
        return;
    }

    cv::Mat srcGray;
    if (srcImage.channels() == 3) {
        cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
    } else {
        srcGray = srcImage.clone();
    }

    cv::Mat padded = Image_make_border(srcGray);
    cv::Mat kernel = Ideal_Low_Kernel(padded, sigma);
    dstImage = Frequency_Filter(padded, kernel);
    dstImage = dstImage(cv::Rect(0, 0, srcGray.cols, srcGray.rows));

    // Normalize the filtered image to display properly
    cv::normalize(dstImage, dstImage, 0, 255, cv::NORM_MINMAX);
    dstImage.convertTo(dstImage, CV_8UC1);
}
// Generate an improved high-pass filter kernel 
cv::Mat FilterInterface::Ideal_High_Kernel(const cv::Mat &padded, float sigma) {
    cv::Mat kernel(padded.size(), CV_32FC1);
    int centerX = padded.cols / 6 * 5 ;
    int centerY = padded.rows / 6 * 5 ;

    for (int i = 0; i < padded.rows; i++) {
        for (int j = 0; j < padded.cols; j++) {
            double d = sqrt(pow(i - centerY, 2) + pow(j - centerX, 2));
            kernel.at<float>(i, j) = exp(-(d * d) / (2 * sigma * sigma));
        }
    }

    return kernel;
}

// Apply an ideal high-pass filter
void FilterInterface::Ideal_Highpass_Filter(const cv::Mat &srcImage, cv::Mat &dstImage, float sigma) {
    if (sigma <= 0) {
        std::cerr << "Error: Sigma must be greater than 0.\n";
        return;
    }

    cv::Mat srcGray;
    if (srcImage.channels() == 3) {
        cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
    } else {
        srcGray = srcImage.clone();
    }

    cv::Mat padded = Image_make_border(srcGray);
    cv::Mat kernel = Ideal_High_Kernel(padded, sigma);
    dstImage = Frequency_Filter(padded, kernel);
    dstImage = dstImage(cv::Rect(0, 0, srcGray.cols, srcGray.rows));

    // Normalize the filtered image to display properly
    cv::normalize(dstImage, dstImage, 0, 255, cv::NORM_MINMAX);
    dstImage.convertTo(dstImage, CV_8UC1);
}

// Generate an improved band-pass filter kernel
cv::Mat FilterInterface::Ideal_Bandpass_Kernel(const cv::Mat &padded, float sigma_low, float sigma_high) {
    cv::Mat kernel(padded.size(), CV_32FC1);
    int centerX = padded.cols / 2;
    int centerY = padded.rows / 2;

    for (int i = 0; i < padded.rows; i++) {
        for (int j = 0; j < padded.cols; j++) {
            double d = sqrt(pow(i - centerY, 2) + pow(j - centerX, 2));
            if (d >= sigma_low && d <= sigma_high) {
                kernel.at<float>(i, j) = 1.0f;
            } else {
                kernel.at<float>(i, j) = 0.0f;
            }
        }
    }

    return kernel;
}

// Apply an improved band-pass filter
void FilterInterface::Ideal_Bandpass_Filter(const cv::Mat &srcImage, cv::Mat &dstImage, float sigma_low, float sigma_high) {
    if (sigma_low <= 0 || sigma_high <= sigma_low) {
        std::cerr << "Error: Invalid frequency range. Ensure 0 < sigma_low < sigma_high.\n";
        return;
    }

    cv::Mat srcGray;
    if (srcImage.channels() == 3) {
        cv::cvtColor(srcImage, srcGray, cv::COLOR_BGR2GRAY);
    } else {
        srcGray = srcImage.clone();
    }

    // Create border for frequency transformation
    cv::Mat padded = Image_make_border(srcGray);
    cv::Mat kernel = Ideal_Bandpass_Kernel(padded, sigma_low, sigma_high);

    // Apply frequency filter
    dstImage = Frequency_Filter(padded, kernel);
    dstImage = dstImage(cv::Rect(0, 0, srcGray.cols, srcGray.rows));

    // Normalize the filtered image to display properly
    cv::normalize(dstImage, dstImage, 0, 255, cv::NORM_MINMAX);
    dstImage.convertTo(dstImage, CV_8UC1);
}


// Apply a Gaussian filter in spatial domain
void FilterInterface::GaussianFilter(const cv::Mat &srcImage, cv::Mat &dstImage) {
    cv::GaussianBlur(srcImage, dstImage, cv::Size(5, 5), 1.5);
}

// Apply a Laplacian filter in spatial domain
void FilterInterface::LaplacianFilter(const cv::Mat &srcImage, cv::Mat &dstImage) {
    cv::Laplacian(srcImage, dstImage, CV_16S, 1);
    cv::convertScaleAbs(dstImage, dstImage);
}
