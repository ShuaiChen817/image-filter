#include "filters.h"
cv::Mat filters::Ideal_High_Kernel(cv::Mat &padded, float sigma) {

  // Create an empty matrix for the high-pass filter kernel
  cv::Mat ideal_high_pass(padded.size(), CV_32FC1);
  float d0 = sigma;

  // Iterate through each element and set values based on distance from center
  for (int i = 0; i < padded.rows; i++) {
    for (int j = 0; j < padded.cols; j++) {
      // Calculate the distance from the center
      double d =
          sqrt(pow((i - padded.rows / 2), 2) + pow((j - padded.cols / 2), 2));

      // Set the filter value based on the distance
      if (d <= d0) {
        ideal_high_pass.at<float>(i, j) = 0;
      } else {
        ideal_high_pass.at<float>(i, j) = 1;
      }
    }
  }
  return ideal_high_pass;
}


void filters::Ideal_Highpass_Filter(Image &srcImage, cv::Mat &dstImage,
                                            float sigma) {
  cv::Mat srcGray;
  if (srcImage.getter().channels() == 3) {
    cv::cvtColor(srcImage.getter(), srcGray, cv::COLOR_BGR2GRAY);
  } else {
    srcGray = srcImage.getter().clone();
  }

  // Pad the source image to an optimal size for DFT
  cv::Mat padded = Image_make_border(srcGray);

  // Create the ideal high-pass filter kernel
  cv::Mat ideal_kernel = Ideal_High_Kernel(padded, sigma);

  // Apply the frequency filter
  dstImage = Frequency_Filter(padded, ideal_kernel);

  // Crop the filtered image to original size
  dstImage = dstImage(cv::Rect(0, 0, srcGray.cols, srcGray.rows));

  // Normalize and convert image format for display
  cv::Mat normalizedImage, ucharImage;
  cv::normalize(dstImage, normalizedImage, 0, 255, cv::NORM_MINMAX, CV_32FC1);
  normalizedImage.convertTo(ucharImage, CV_8U);
  dstImage = ucharImage;

  // Concatenate and display the result
  cv::Mat result;
  cv::hconcat(srcGray, ucharImage, result);
  cv::imshow("Ideal Highpass Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

cv::Mat filters::Ideal_Low_Kernel(cv::Mat &padded, float sigma) {

  // Create an empty matrix for the low-pass filter kernel
  cv::Mat ideal_low_pass(padded.size(), CV_32FC1);
  float d0 = sigma;

  // Iterate through each element and set values based on distance from center
  for (int i = 0; i < padded.rows; i++) {
    for (int j = 0; j < padded.cols; j++) {
      // Calculate the distance from the center
      double d =
          sqrt(pow((i - padded.rows / 2), 2) + pow((j - padded.cols / 2), 2));
      // Set the filter value based on the distance
      if (d <= d0) {
        ideal_low_pass.at<float>(i, j) = 1;
      } else {
        ideal_low_pass.at<float>(i, j) = 0;
      }
    }
  }
  return ideal_low_pass;
}

/**
 * Ideal_Lowpass_Filter - Applies an ideal low-pass filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 * @sigma: The cut-off frequency for the low-pass filter
 *
 * This function applies an ideal low-pass filter to the source image. The ideal
 * low-pass filter is used to remove high-frequency content from the image, such
 * as noise, while preserving the low-frequency content, such as main features
 * or shapes.
 */
void filters::Ideal_Lowpass_Filter(Image &srcImage, cv::Mat &dstImage,
                                           float sigma) {
  cv::Mat srcGray;
  if (srcImage.getter().channels() == 3) {
    cv::cvtColor(srcImage.getter(), srcGray, cv::COLOR_BGR2GRAY);
  } else {
    srcGray = srcImage.getter().clone();
  }

  // Pad the source image to an optimal size for DFT
  cv::Mat padded = Image_make_border(srcGray);

  // Create the ideal low-pass filter kernel
  cv::Mat ideal_kernel = Ideal_Low_Kernel(padded, sigma);

  // Apply the frequency filter
  dstImage = Frequency_Filter(padded, ideal_kernel);

  // Crop the filtered image to original size
  dstImage = dstImage(cv::Rect(0, 0, srcGray.cols, srcGray.rows));

  // Normalize and convert image format for display
  cv::Mat normalizedImage, ucharImage;
  cv::normalize(dstImage, normalizedImage, 0, 255, cv::NORM_MINMAX, CV_32FC1);
  normalizedImage.convertTo(ucharImage, CV_8U);
  dstImage = ucharImage;

  cv::Mat result;
  cv::hconcat(srcGray, ucharImage, result);
  cv::imshow("Ideal Lowpass Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

cv::Mat filters::Ideal_Bandpass_Kernel(cv::Mat &padded, float sigma_low,
                                               float sigma_high) {

  // Create an empty matrix for the bandpass filter kernel
  cv::Mat bandpass_kernel(padded.size(), CV_32FC1);

  // Iterate through each element and set values based on distance from center
  for (int i = 0; i < padded.rows; i++) {
    for (int j = 0; j < padded.cols; j++) {
      // Calculate the distance from the center
      double d =
          sqrt(pow((i - padded.rows / 2), 2) + pow((j - padded.cols / 2), 2));

      // Set the filter value based on the distance
      if (d >= sigma_low && d <= sigma_high) {
        bandpass_kernel.at<float>(i, j) = 1;
      } else {
        bandpass_kernel.at<float>(i, j) = 0;
      }
    }
  }

  return bandpass_kernel;
}

/**
 * Ideal_Bandpass_Filter - Applies an ideal bandpass filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 * @sigma_low: Lower cut-off frequency for the bandpass filter
 * @sigma_high: Higher cut-off frequency for the bandpass filter
 *
 * This function applies an ideal bandpass filter to the source image. An ideal
 * bandpass filter allows frequencies within a specified range (between
 * sigma_low and sigma_high) to pass through while blocking frequencies outside
 * this range.
 */
void filters::Ideal_Bandpass_Filter(Image &srcImage, cv::Mat &dstImage,
                                            float sigma_low, float sigma_high) {
  cv::Mat srcGray;
  if (srcImage.getter().channels() == 3) {
    cv::cvtColor(srcImage.getter(), srcGray, cv::COLOR_BGR2GRAY);
  } else {
    srcGray = srcImage.getter().clone();
  }

  // Pad the source image to an optimal size for DFT
  cv::Mat padded = Image_make_border(srcGray);

  // Create the ideal bandpass filter kernel
  cv::Mat bandpass_kernel =
      Ideal_Bandpass_Kernel(padded, sigma_low, sigma_high);

  // Apply the frequency filter
  dstImage = Frequency_Filter(padded, bandpass_kernel);

  // Crop the filtered image to original size
  dstImage = dstImage(cv::Rect(0, 0, srcGray.cols, srcGray.rows));

  // Normalize and convert image format for display
  cv::Mat normalizedImage, ucharImage;
  cv::normalize(dstImage, normalizedImage, 0, 255, cv::NORM_MINMAX, CV_32FC1);
  normalizedImage.convertTo(ucharImage, CV_8U);
  dstImage = ucharImage;

  // Concatenate and display the result
  cv::Mat result;
  cv::hconcat(srcGray, ucharImage, result);
  cv::imshow("Ideal Bandpass Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

void filters::GaussianFilter(Image &srcImage, cv::Mat &dstImage) {
  // KernelSize: Size of the Gaussian kernel. It should be odd and positive.
  // xValue: Gaussian kernel standard deviation in the X direction
  // yValue: Gaussian kernel standard deviation in the Y direction
  int KernelSize, xValue, yValue;
  std::cout << "Start Gaussian filter......\n";
  do {
    std::cout << "Please give an odd number as a kernel size (e.g. 3, 5...):\n";
    std::cin >> KernelSize;

    if (KernelSize % 2 == 0) {
      std::cout << "Kernel size must be an odd number. Please enter again.\n";
    }

  } while (KernelSize % 2 == 0);

  std::cout << "Please give a X Gaussian kernel standard deviation :\n";
  std::cin >> xValue;

  std::cout << "Please give a Y Gaussian kernel standard deviation :\n";
  std::cin >> yValue;

  cv::Size kernel(KernelSize, KernelSize);
  // Apply the GaussianBlur
  cv::GaussianBlur(srcImage.getter(), dstImage, kernel, xValue, yValue);

  cv::Mat result;
  // concatenates the source and destination images and displays the result.
  cv::hconcat(srcImage.getter(), dstImage, result);
  cv::imshow("Gaussian Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

void filters::LaplacianFilter(Image &srcImage, cv::Mat &dstImage) {

  // Convert to grayscale if the image is colored
  cv::Mat srcGray;
  if (srcImage.getter().channels() == 3) {
    cv::cvtColor(srcImage.getter(), srcGray, cv::COLOR_BGR2GRAY);
  } else {
    srcGray = srcImage.getter().clone();
  }

  // Apply the Laplacian filter
  cv::Mat grad;
  cv::Laplacian(srcGray, grad, CV_8U);
  convertScaleAbs(grad, dstImage);

  // Concatenate and display the result
  cv::Mat result;
  cv::hconcat(srcGray, dstImage, result);
  cv::imshow("Laplacian Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

cv::Mat filters::Image_make_border(cv::Mat &srcImage) {

  // Calculate the optimal width and height for DFT
  int w = cv::getOptimalDFTSize(srcImage.cols);
  int h = cv::getOptimalDFTSize(srcImage.rows);

  // Pad the source image to the optimal size with zero border
  cv::Mat padded;
  copyMakeBorder(srcImage, padded, 0, h - srcImage.rows, 0, w - srcImage.cols,
                 cv::BORDER_CONSTANT, cv::Scalar::all(0));
  // Convert the padded image to 32-bit float single channel, if necessary
  padded.convertTo(padded, CV_32FC1);
  return padded;
}

cv::Mat filters::Frequency_Filter(cv::Mat &padded, cv::Mat &blur) {

  // Step 1: Create a complex image from padded source image
  cv::Mat plane[] = {padded, cv::Mat::zeros(padded.size(), CV_32FC1)};
  cv::Mat complexImage;
  cv::merge(plane, 2, complexImage);

  // Step 2: Perform DFT
  cv::dft(complexImage, complexImage);
  split(complexImage, plane);

  // Step 3: Shift the zero frequency component to the center
  Shifttransfunction(plane[0], plane[1]);

  // Step 4: Apply the filter in the frequency domain
  cv::Mat blur_r, blur_i, BLUR;
  cv::multiply(plane[0], blur, blur_r);
  cv::multiply(plane[1], blur, blur_i);
  cv::Mat plane1[] = {blur_r, blur_i};

  // Step 5: Shift the spectrum back to original position
  Shifttransfunction(plane1[0], plane1[1]);

  // Step 6: Merge and perform inverse DFT
  cv::merge(plane1, 2, BLUR);
  cv::idft(BLUR, BLUR);

  // Step 7: Extract the magnitude (real part)
  cv::split(BLUR, plane);
  cv::magnitude(plane[0], plane[1], plane[0]);

  // Step 8: Normalize for display
  cv::normalize(plane[0], plane[0], 0, 1, cv::NORM_MINMAX);
  return plane[0];
}