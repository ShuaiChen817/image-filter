
#include "UserMenu.h"

namespace Menu {
// Define a function to display the menu
void displayMenu() {
  std::cout << "************ Image Filtering System! ************\n";
  std::cout << "************ Please select a filter method: ************\n";
  std::cout << "************ 1. IdealHighPass ************\n";
  std::cout << "************ 2. IdealLowPass ************\n";
  std::cout << "************ 3. IdealBandPass ************\n";
  std::cout << "************ 4. Gaussian ************\n";
  std::cout << "************ 5. Laplace ************\n";
  std::cout << "************ 6. Exit the system ************\n";
  std::cout << "************ Enter your choice: ************" << std::endl;
}

std::string getInputImagePath() {
  std::string inputPath;
  std::cout << "Enter the input image path or press enter to use default image "
               "('../images_input/1.jpg'):\n";
  std::getline(std::cin, inputPath);
  if (inputPath.empty()) {
    inputPath = "../images_input/1.jpg"; // default path
  }
  return inputPath;
}

std::string getOutputImagePath() {
  std::string outputPath;
  std::cout
      << "Enter the output image directory or press enter to use default path"
         "('../images_output/'):\n";
  std::getline(std::cin, outputPath); // Use getline to read an entire line
  if (outputPath.empty()) {
    outputPath = "../images_output/"; // default path
  }
  return outputPath;
}
