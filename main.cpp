#include "filters.h"
#include "UserMenu.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include <string>

int main() {

  std::cout << "--------Welcome to Group 90!--------\n";
  // Read the source image file.
  std::string inputPath = Menu::getInputImagePath();
  Image srcImage(inputPath);


  if (srcImage.getter().empty()) {
    std::cout << "Could not load image ...\n" << std::endl;
    return -1;
  }
  std::cout << "Image successfully loaded!\n" << std::endl;


  char userInput = 'n';
  do {
    int choice;
    Menu::displayMenu();
    std::cin >> choice;

    // Initialize a variable for saving the output image.
    cv::Mat resultImage;
    Image dstImage(resultImage);

    switch (choice) {
    case 1: {
      std::unique_ptr<filters> myFilter = std::make_unique<IdealHighPass>();
      myFilter->imageFilter(srcImage, dstImage);
      dstImage.save();
      break;
    }
    case 2: {
      std::unique_ptr<filters> myFilter =
          std::make_unique<IdealLowPass>();
      myFilter->imageFilter(srcImage, dstImage);
      dstImage.save();
      break;
    }
    case 3: {
      std::unique_ptr<filters> myFilter =
          std::make_unique<IdealBandPass>();
      myFilter->imageFilter(srcImage, dstImage);
      dstImage.save();
      break;
    }
    case 4: {
      std::unique_ptr<filters> myFilter =
          std::make_unique<Gaussian>();
      myFilter->imageFilter(srcImage, dstImage);
      dstImage.save();
      break;
    }
    case 5: {
      std::unique_ptr<filters> myFilter =
          std::make_unique<Laplace>();
      myFilter->imageFilter(srcImage, dstImage);
      dstImage.save();
      break;
    }
    case 6: {
      std::cout << "system will be closed!" << std::endl;
      return 0;
    }
    default:
      std::cout << "Invalid choice. Please enter a number from 1 to 6.\n";
    }

    std::string input;
    std::cout << "Do you want to continue system? (Y/n): " << std::endl;
    // Clear any errors
    // Skip any remaining input to prepare for the next input
    std::cin.clear(); // Clear error state
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'); // Ignore the rest of the line until a newline character
    std::getline(std::cin, input);

    // Check if input is empty
    if (input.empty()) {
      // If the string is empty, use the default value
      std::cout << "No input entered. Using default value 'n'." << std::endl;
    } else {
      // If the string is not empty, use the first character of the input
      userInput = input[0];
      if (userInput == 'y' || userInput == 'Y') {
        std::cout << "You entered: " << userInput << std::endl;
      } else if (userInput == 'n' || userInput == 'N') {
        std::cout << "You entered: " << userInput << ", system will be closed!"
                  << std::endl;
      } else {
        std::cout << "You entered an incorrect value, we will use the default "
                     "value(n), system will be closed! "
                  << std::endl;
      }
    }

  } while (userInput == 'y' || userInput == 'Y');

  return 0;
}

  