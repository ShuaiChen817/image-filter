#include "Blurring.h"

void Blurring::imageFilter(Image &srcImage, Image &dstImage) {
  // Gaussian Filter
  cv::Mat resultImage;
  int choice;
  choice = getUserChoice();

  switch (choice) {
  case 1: {
    GaussianFilter(srcImage, resultImage);
    dstImage.setter(resultImage);
    break;
  }
  case 2: {
    float sigma = 30.0;
    Ideal_Lowpass_Filter(srcImage, resultImage, sigma);
    dstImage.setter(resultImage);
    break;
  }
  }
}

int Blurring::getUserChoice() {
  int choice;
  bool validInput = false;
  std::cout << "There are some blurring methodes for you to choice! \n";
  std::cout << "1. Gaussian Filter \n";
  std::cout << "2. Ideal Low Pass Filter \n";
  std::cout << "Enter your choice: ";

  do {
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 ||
        choice > 2) {   // If the input fails
      std::cin.clear(); // Reset Input State
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Ignore characters after an incorrect entry until the next newline.
      std::cout << "Invalid input. Please enter a number(1 or 2)." << std::endl;
    } else {
      validInput = true;
    }
  } while (!validInput);

  return choice;
}