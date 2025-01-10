#include "FilterInterface.h"

/**
 * GaussianFilter - Applies a Gaussian filter to an image
 * @srcImage: Source image
 * @dstImage: Destination image where the result is stored
 *
 *
 * This function applies a Gaussian blur to the source image using the specified
 * kernel size and standard deviations in the X and Y directions. The result is
 * stored in dstImage. A larger kernel size will result in a more blurred image.
 */
void FilterInterface::GaussianFilter(Image &srcImage, cv::Mat &dstImage) {
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

/**
 * MedianFilter - Applies a median filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 *
 *
 * This function applies a median blur to the source image using the specified
 * kernel size. The median filter is a non-linear digital filtering technique,
 * often used to remove noise.
 */
void FilterInterface::MedianFilter(Image &srcImage, cv::Mat &dstImage) {
  int KernelSize; // KernelSize: Size of the median filter kernel. It must be an
                  // odd number.
  std::cout << "Start Median filter......\n";
  do {
    std::cout << "Please give an odd number as a kernel size (e.g. 3, 5...):\n";
    std::cin >> KernelSize;

    if (KernelSize % 2 == 0) {
      std::cout << "Kernel size must be an odd number. Please enter again.\n";
    }

  } while (KernelSize % 2 == 0);
  // Apply the medianBlur
  cv::medianBlur(srcImage.getter(), dstImage, KernelSize);

  // Concatenate and display the result
  cv::Mat result;
  cv::hconcat(srcImage.getter(), dstImage, result);
  cv::imshow("Median Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * BilateralFilter - Applies a bilateral filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 *
 * This function applies a bilateral filter to the source image. The bilateral
 * filter is a non-linear, edge-preserving, and noise-reducing smoothing filter.
 * It replaces the intensity of each pixel with a weighted average of intensity
 * values from nearby pixels. This weight can be based on a Gaussian
 * distribution.
 */
void FilterInterface::BilateralFilter(Image &srcImage, cv::Mat &dstImage) {
  cv::Mat src = srcImage.getter();
  cv::Mat temp;

  // Adjust the image type if necessary
  if (src.type() != CV_8UC1 && src.type() != CV_8UC3) {
    int dstType = src.channels() == 3 ? CV_8UC3 : CV_8UC1;
    src.convertTo(temp, dstType);
  } else {
    temp = src.clone(); //  Clone the source image if no type conversion is
                        //  necessary
  }
  // Apply bilateral filter
  cv::bilateralFilter(temp, dstImage, 5, 150, 150);

  // Concatenate and display the result
  cv::Mat result;
  cv::hconcat(srcImage.getter(), dstImage, result);
  cv::imshow("Bilateral Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * LaplacianFilter - Applies a Laplacian filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 *
 * This function applies a Laplacian filter to the source image.
 * The Laplacian filter is a second-order derivative filter, used to find areas
 * of rapid change (edges) in images. It highlights regions of rapid intensity
 * change and is therefore often used for edge detection.
 */
void FilterInterface::LaplacianFilter(Image &srcImage, cv::Mat &dstImage) {

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

/**
 * SobelFilter - Applies a Sobel filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 *
 * This function applies the Sobel operator to the source image. The Sobel
 * operator is used within edge detection algorithms, and creates an image
 * emphasizing edges. The function calculates the gradient of the image
 * intensity in both the x and y directions. The gradients in each direction are
 * then combined to give the final gradient magnitude which highlights the
 * edges.
 */
void FilterInterface::SobelFilter(Image &srcImage, cv::Mat &dstImage) {

  cv::Mat grad_x, grad_y;
  cv::Mat abs_grad_x, abs_grad_y;

  // use default value.
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  // Calculate the x and y gradients using Sobel operator
  cv::Sobel(srcImage.getter(), grad_x, ddepth, 1, 0, 3, scale, delta);
  cv::convertScaleAbs(grad_x, abs_grad_x);
  cv::Sobel(srcImage.getter(), grad_y, ddepth, 0, 1, 3, scale, delta);
  cv::convertScaleAbs(grad_y, abs_grad_y);
  // Combine the gradients
  cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstImage);

  // Concatenate and display the result
  cv::Mat result;
  cv::hconcat(srcImage.getter(), dstImage, result);
  cv::imshow("Sobel Filter Result", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * Image_make_border - Optimizes the size of an image for Discrete Fourier
 * Transform (DFT)
 * @srcImage: Source image to be padded
 * @return: Returns the image after size optimization and padding adjustments.
 *
 * This function calculates the optimal size for DFT of the image and then pads
 * the image to match this optimal size. Padding is done by adding zero pixels
 * around the border of the image. The function first uses
 * `cv::getOptimalDFTSize` for both rows and columns to get the nearest optimal
 * size. It then creates a new image (padded) with this optimal size, filling
 * the extra border space with zeros. Finally, the image is converted to a
 * single channel, 32-bit floating point format (if not already in that format),
 * which is a suitable format for DFT operations.
 */
cv::Mat FilterInterface::Image_make_border(cv::Mat &srcImage) {

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

/**
 * Shifttransfunction - Shifts the zero-frequency component to the center of the
 * spectrum
 * @plane0： Real part of the Fourier-transformed image
 * @plane1: Imaginary part of the Fourier-transformed image
 *
 * This function is used to shift the quadrants of the Fourier image so that the
 * origin (zero frequency) is at the center of the image. It makes the spectrum
 * more intuitive to analyze. The function takes the real and imaginary parts of
 * a Fourier-transformed image, repositions the quadrants to center the low
 * frequencies, and applies the same transformation to both the real and
 * imaginary parts.
 */
void FilterInterface::Shifttransfunction(cv::Mat &plane0, cv::Mat &plane1) {

  // Center of the spectrum
  int cx = plane0.cols / 2;
  int cy = plane0.rows / 2;
  // Quadrant repositioning for the real part
  cv::Mat part1_r(plane0, cv::Rect(0, 0, cx, cy));
  cv::Mat part2_r(plane0, cv::Rect(cx, 0, cx, cy));
  cv::Mat part3_r(plane0, cv::Rect(0, cy, cx, cy));
  cv::Mat part4_r(plane0, cv::Rect(cx, cy, cx, cy));

  cv::Mat temp;
  // Swap quadrants: top-left and bottom-right
  part1_r.copyTo(temp);
  part4_r.copyTo(part1_r);
  temp.copyTo(part4_r);
  // Swap quadrants: top-right and bottom-left
  part2_r.copyTo(temp);
  part3_r.copyTo(part2_r);
  temp.copyTo(part3_r);

  // Quadrant repositioning for the imaginary part
  cv::Mat part1_i(plane1, cv::Rect(0, 0, cx, cy));
  cv::Mat part2_i(plane1, cv::Rect(cx, 0, cx, cy));
  cv::Mat part3_i(plane1, cv::Rect(0, cy, cx, cy));
  cv::Mat part4_i(plane1, cv::Rect(cx, cy, cx, cy));

  // Swap the top-left and the bottom-right quadrants
  part1_i.copyTo(temp);
  part4_i.copyTo(part1_i);
  temp.copyTo(part4_i);
  // Swap the top-right and the bottom-left quadrants
  part2_i.copyTo(temp);
  part3_i.copyTo(part2_i);
  temp.copyTo(part3_i);
}

/**
 * Frequency_Filter - Applies a frequency domain filter to an image
 * @padded: Padded source image
 * @blur: Frequency domain filter kernel
 * @return：Returns the image after frequency domain filtering, which is
 * normalized to a range of 0 to 1, suitable for display.
 *
 * This function applies a frequency domain filter to an image. The process
 * involves several steps:
 * 1. Create a complex image from the padded source image. This is done by
 * merging the padded image (as the real part) with an image of zeros (as the
 * imaginary part).
 * 2. Perform a Discrete Fourier Transform (DFT) on the complex image.
 * 3. Shift the zero-frequency component to the center of the spectrum.
 * 4. Multiply the real and imaginary parts of the transformed image with the
 * filter kernel.
 * 5. Shift the spectrum back so the zero-frequency component is at the original
 * position.
 * 6. Merge the modified real and imaginary parts and perform an inverse DFT.
 * 7. Split the result to obtain just the real part (magnitude) of the filtered
 * image.
 * 8. Normalize the magnitude image to a range of 0 to 1 for display.
 *
 * The result is an image that has been filtered in the frequency domain, which
 * can be used for various purposes like blurring, sharpening, or other
 * frequency-based image manipulations.
 */
cv::Mat FilterInterface::Frequency_Filter(cv::Mat &padded, cv::Mat &blur) {

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

/**
 * Ideal_Low_Kernel - Creates an ideal low-pass filter kernel
 * @padded: Padded image for which the filter kernel is to be created
 * @sigma: The cut-off frequency for the low-pass filter
 * @return: The ideal low-pass filter kernel as a cv::Mat
 *
 * This function creates an ideal low-pass filter kernel for a given image size.
 * An ideal low-pass filter allows frequencies lower than a certain threshold
 * (sigma) to pass through while blocking higher frequencies. The filter is
 * represented as a matrix (cv::Mat) where each element's value is determined
 * based on its distance from the center of the frequency spectrum. Elements
 * within the cut-off frequency radius (sigma) are set to 1, allowing those
 * frequencies to pass, while elements outside this radius are set to 0,
 * effectively blocking those frequencies.
 */
cv::Mat FilterInterface::Ideal_Low_Kernel(cv::Mat &padded, float sigma) {

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
void FilterInterface::Ideal_Lowpass_Filter(Image &srcImage, cv::Mat &dstImage,
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

/**
 * Ideal_High_Kernel - Creates an ideal high-pass filter kernel
 * @padded: Padded image for which the filter kernel is to be created
 * @sigma: The cut-off frequency for the high-pass filter
 * @return: The ideal high-pass filter kernel as a cv::Mat
 *
 * This function creates an ideal high-pass filter kernel for a given image
 * size. An ideal high-pass filter blocks frequencies lower than a certain
 * threshold (sigma) while allowing higher frequencies to pass through. The
 * filter is represented as a matrix (cv::Mat) where each element's value is
 * determined based on its distance from the center of the frequency spectrum.
 * Elements within the cut-off frequency radius (sigma) are set to 0, blocking
 * those frequencies, while elements outside this radius are set to 1, allowing
 * those frequencies to pass.
 */
cv::Mat FilterInterface::Ideal_High_Kernel(cv::Mat &padded, float sigma) {

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

/**
 * Ideal_Highpass_Filter - Applies an ideal high-pass filter to an image
 * @srcImage: Source image to apply the filter on
 * @dstImage: Destination image where the filtered result will be stored
 * @sigma: The cut-off frequency for the high-pass filter
 *
 * This function applies an ideal high-pass filter to the source image. The
 * ideal high-pass filter is used to remove low-frequency content from the
 * image, such as smooth variations in intensity, while preserving the
 * high-frequency content, such as edges or fine details.
 */
void FilterInterface::Ideal_Highpass_Filter(Image &srcImage, cv::Mat &dstImage,
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

/**
 * Ideal_Bandpass_Kernel - Creates an ideal bandpass filter kernel
 * @padded: Padded image for which the filter kernel is to be created
 * @sigma_low: The lower cut-off frequency for the bandpass filter
 * @sigma_high: The higher cut-off frequency for the bandpass filter
 * @return: The ideal bandpass filter kernel as a cv::Mat
 *
 * This function creates an ideal bandpass filter kernel for a given image size.
 * An ideal bandpass filter allows only the frequencies within a specific range
 * (between sigma_low and sigma_high) to pass through, while blocking
 * frequencies outside this range. The kernel is created by iterating over each
 * pixel and setting the pixel value to 1 if its distance from the center is
 * within the range defined by sigma_low and sigma_high, and to 0 otherwise.
 * This effectively creates a filter that permits a band of frequencies,
 * specified by the sigma_low and sigma_high thresholds, to pass through, while
 * blocking others.
 */
cv::Mat FilterInterface::Ideal_Bandpass_Kernel(cv::Mat &padded, float sigma_low,
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
void FilterInterface::Ideal_Bandpass_Filter(Image &srcImage, cv::Mat &dstImage,
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

