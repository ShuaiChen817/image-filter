#include "filters.h"  
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <filesystem>

// Display the menu options
void displayMenu() {
    std::cout << "************ Image Filtering System! ************\n";
    std::cout << "1. High-pass Filter\n";
    std::cout << "2. Low-pass Filter\n";
    std::cout << "3. Bandpass Filter\n";
    std::cout << "4. Gaussian Filter\n";
    std::cout << "5. Laplace Filter\n";
    std::cout << "6. Exit the system\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::cout << "Welcome to the Image Filtering System!\n";

    // Get the input image path
    std::string imagePath;
    std::cout << "Enter the path to your image (or press Enter to use default): ";
    std::getline(std::cin, imagePath);
    if (imagePath.empty()) {
        imagePath = "../images_input/default_image.jpg"; // Default image path
    }

    // Check if the file exists
    if (!std::filesystem::exists(imagePath)) {
        std::cerr << "Error: File does not exist at " << imagePath << "\n";
        return -1;
    }

    // Load the input image
    cv::Mat inputImage = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (inputImage.empty()) {
        std::cerr << "Error: Could not open or find the image.\n";
        return -1;
    }

    std::cout << "Image loaded successfully! Dimensions: " 
              << inputImage.cols << "x" << inputImage.rows << " pixels.\n";

    // Check or create output directory
    if (!std::filesystem::exists("images_output")) {
        if (!std::filesystem::create_directory("images_output")) {
            std::cerr << "Error: Failed to create output directory.\n";
            return -1;
        }
    }

    int choice;
    while (true) {
        // Display the menu and get user's choice
        displayMenu();
        std::cin >> choice;

        cv::Mat outputImage;
        ConcreteFilter filter; // Using filters.h's ConcreteFilter

        switch (choice) {
            case 1: {
                float sigma;
                std::cout << "Enter sigma for High-pass Filter: ";
                std::cin >> sigma;
                if (sigma <= 0) {
                    std::cerr << "Error: Sigma must be greater than 0.\n";
                    continue;
                }
                filter.Ideal_Highpass_Filter(inputImage, outputImage, sigma);
                break;
            }
            case 2: {
                float sigma;
                std::cout << "Enter sigma for Low-pass Filter: ";
                std::cin >> sigma;
                if (sigma <= 0) {
                    std::cerr << "Error: Sigma must be greater than 0.\n";
                    continue;
                }
                filter.Ideal_Lowpass_Filter(inputImage, outputImage, sigma);
                break;
            }
            case 3: {
                float sigma_low, sigma_high;
                std::cout << "Enter sigma_low for Band-pass Filter: ";
                std::cin >> sigma_low;
                std::cout << "Enter sigma_high for Band-pass Filter: ";
                std::cin >> sigma_high;
                filter.Ideal_Bandpass_Filter(inputImage, outputImage, sigma_low, sigma_high);
                break;
                }
            case 4:
                filter.GaussianFilter(inputImage, outputImage);
                break;
            case 5:
                filter.LaplacianFilter(inputImage, outputImage);
                break;
            case 6:
                std::cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                continue;
        }

        // Validate the output image
        if (outputImage.empty()) {
            std::cerr << "Error: Filtered image is empty. Check your filter implementation.\n";
            continue;
        }

        // Save the filtered image
        std::string outputPath;
        if (choice == 1) {
            outputPath = "images_output/filtered_image_highpass.jpg";
        } else if (choice == 2) {
            outputPath = "images_output/filtered_image_lowpass.jpg";
        } else if (choice == 3) {
            outputPath = "images_output/filtered_image_bandpass.jpg";
        } else if (choice == 4) {
            outputPath = "images_output/filtered_image_gaussian.jpg";
        } else if (choice == 5) {
            outputPath = "images_output/filtered_image_laplacian.jpg";
        } else {
            outputPath = "images_output/filtered_image.jpg"; // Fallback
        }

        if (!cv::imwrite(outputPath, outputImage)) {
            std::cerr << "Error: Failed to save the filtered image to " << outputPath << "\n";
            continue;
        }

        std::cout << "Filtered image saved to " << outputPath << "\n";

        // Display success message
        std::cout << "Processing complete! You can view the result at " << outputPath << "\n";
    }

    return 0;
}
