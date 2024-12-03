#include "UserMenu.h"

namespace Menu {

// Display the menu options
void displayMenu() {
    std::cout << "************ Image Filtering System! ************\n";
    std::cout << "************ Please select a filter method: ************\n";
    std::cout << "************ 1. High-pass Filter ************\n";
    std::cout << "************ 2. Low-pass Filter ************\n";
    std::cout << "************ 3. Bandpass Filter ************\n";
    std::cout << "************ 4. Gaussian Filter ************\n";
    std::cout << "************ 5. Laplace Filter ************\n";
    std::cout << "************ 6. Exit the system ************\n";
    std::cout << "************ Enter your choice: ************" << std::endl;
}

// Get the input image path from the user
std::string getInputImagePath() {
    std::string inputPath;
    std::cout << "Enter the path to your image (or press Enter to use default): ";
    std::getline(std::cin, inputPath);
    if (inputPath.empty()) {
        inputPath = "images_input/default.jpg"; // Default input path
    }
    return inputPath;
}

// Get the output image path from the user
std::string getOutputImagePath() {
    return "images_output/filtered_image.jpg"; // Default output path
}

} // namespace Menu
