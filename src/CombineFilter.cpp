#include "CombineFilter.h"

void CombineFilter::imageFilter(Image &srcImage, Image &dstImage) {
  int choice;
  size_t filterNum;
  dstImage.setter(srcImage.getter());
  cv::Mat resultImage;

  filterNum = getUserChoice();

  std::cout << "Start to makr your filter!";
  for (int i = 0; i < filterNum; i++) {
    std::cout << "This is " << i + 1
              << ".filter, please give your choice(1-8): \n";
    std::cin >> choice;
    switch (choice) {
    case 1: {
      GaussianFilter(dstImage, resultImage);
      dstImage.setter(resultImage);
      break;
    }
    case 2: {
      MedianFilter(dstImage, resultImage);
      dstImage.setter(resultImage);
      break;
    }
    case 3: {
      BilateralFilter(dstImage, resultImage);
      dstImage.setter(resultImage);
      break;
    }
    case 4: {
      LaplacianFilter(dstImage, resultImage);
      dstImage.setter(resultImage);
      break;
    }
    case 5: {
      SobelFilter(dstImage, resultImage);
      dstImage.setter(resultImage);
      break;
    }
    case 6: {
      float sigma = 30.0;
      Ideal_Lowpass_Filter(dstImage, resultImage, sigma);
      dstImage.setter(resultImage);
      break;
    }
    case 7: {
      float sigma = 60.0;
      Ideal_Highpass_Filter(dstImage, resultImage, sigma);
      dstImage.setter(resultImage);
      break;
    }
    case 8: {
      float sigma1 = 30.0;
      float sigma2 = 60.0;
      Ideal_Bandpass_Filter(dstImage, resultImage, sigma1, sigma2);
      dstImage.setter(resultImage);
      break;
    }
    default:
      std::cout << "Invalid choice. Please enter a number from 1 to 8.\n";
    }
  }
}

size_t CombineFilter::getUserChoice() {
  std::cout << "There are some filters: \n";
  std::cout << "1.Gaussian Filter \n";
  std::cout << "2.Median Filter \n";
  std::cout << "3.Bilateral Filter \n";
  std::cout << "4.Laplacian Filter \n";
  std::cout << "5.Sobel Filter \n";
  std::cout << "6.Ideal_Lowpass_Filter \n";
  std::cout << "7.Ideal_Highpass_Filter \n";
  std::cout << "8.Ideal_Bandpass_Filter \n";
  std::cout << "You can choose some and combine them to make your own Filter!"
            << std::endl;
  size_t filterNum;
  bool validInput = false;
  do {
    std::cout << "Please firstly given the number of filters: \n";
    std::cin >> filterNum;

    if (std::cin.fail() ||
        filterNum < 1) { // If the input fails
      std::cin.clear();  // Reset Input State
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Ignore characters after an incorrect entry until the next newline.
      std::cout << "Invalid input. Please enter a IntNumber." << std::endl;
    } else {
      validInput = true;
    }
  } while (!validInput);

  return filterNum;
}