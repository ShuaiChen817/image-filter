#include "Blurring.h"
#include "CombineFilter.h"
#include "EdgeDetection.h"
#include "FilterInterface.h"
#include "Image.h"
#include "ImageInterface.h"
#include "ImageSharpening.h"
#include "NoiseRemoval.h"
#include "UserMenu.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include <string>

int main() {
    std::cout << "************ Image Filtering System! ************\n";
    
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
        std::string outputPath = "../images_output/filtered_image.jpg";

        switch (choice) {
            case 1: {
                std::unique_ptr<FilterInterface> myFilter = std::make_unique<Blurring>();
                myFilter->imageFilter(srcImage, dstImage);
                cv::imwrite(outputPath, dstImage.getter());
                std::cout << "Image saved to: " << outputPath << std::endl;
                break;
            }
            case 2: {
                std::unique_ptr<FilterInterface> myFilter = std::make_unique<NoiseRemoval>();
                myFilter->imageFilter(srcImage, dstImage);
                cv::imwrite(outputPath, dstImage.getter());
                std::cout << "Image saved to: " << outputPath << std::endl;
                break;
            }
            case 3: {
                std::unique_ptr<FilterInterface> myFilter = std::make_unique<EdgeDetection>();
                myFilter->imageFilter(srcImage, dstImage);
                cv::imwrite(outputPath, dstImage.getter());
                std::cout << "Image saved to: " << outputPath << std::endl;
                break;
            }
            case 4: {
                std::unique_ptr<FilterInterface> myFilter = std::make_unique<ImageSharpening>();
                myFilter->imageFilter(srcImage, dstImage);
                cv::imwrite(outputPath, dstImage.getter());
                std::cout << "Image saved to: " << outputPath << std::endl;
                break;
            }
            case 5: {
                std::unique_ptr<FilterInterface> myFilter = std::make_unique<CombineFilter>();
                myFilter->imageFilter(srcImage, dstImage);
                cv::imwrite(outputPath, dstImage.getter());
                std::cout << "Image saved to: " << outputPath << std::endl;
                break;
            }
            case 6: {
                std::cout << "System will be closed!" << std::endl;
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please enter a number from 1 to 6.\n";
        }

        std::string input;
        std::cout << "Do you want to continue system? (Y/n): " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "No input entered. Using default value 'n'." << std::endl;
        } else {
            userInput = input[0];
            if (userInput == 'y' || userInput == 'Y') {
                std::cout << "You entered: " << userInput << std::endl;
            } else if (userInput == 'n' || userInput == 'N') {
                std::cout << "You entered: " << userInput << ", system will be closed!" << std::endl;
            } else {
                std::cout << "You entered an incorrect value, we will use the default value(n), system will be closed! " << std::endl;
            }
        }

    } while (userInput == 'y' || userInput == 'Y');

    return 0;
}