#include "ImageSharpening.h"

void ImageSharpening::imageFilter(Image &srcImage, Image &dstImage) {
  cv::Mat resultImage;
  int choice;
  choice = getUserChoice();

  switch (choice) {
  case 1: {
    // LaplacianFilter
    LaplacianFilter(srcImage, resultImage);
    dstImage.setter(resultImage);
    break;
  }
  case 2: {
    // Ideal_Highpass_Filter
    float sigma = 60.0;
    Ideal_Highpass_Filter(srcImage, resultImage, sigma);
    dstImage.setter(resultImage);
    break;
  }
  }
}

int ImageSharpening::getUserChoice() {
  int choice;
  bool validInput = false;
  std::cout << "There are some imagesharpening methodes for you to choice! \n";
  std::cout << "1.Laplacian Filter \n";
  std::cout << "2.Ideal High Pass Filter \n";
  std::cout << "Enter your choice: " << std::endl;

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