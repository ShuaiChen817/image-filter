#include "Image.h"

Image::Image(const std::string &path) : ImageInterface(path) {}

Image::Image(const cv::Mat &image) : ImageInterface(image) {}

/**
 * addGaussianNoise - Adds Gaussian noise to an image
 * @mean: Mean value of the Gaussian noise distribution
 * @stddev: Standard deviation of the Gaussian noise distribution
 *
 * This function applies Gaussian noise to a given image.
 * It can handle both grayscale and color images.
 */
void Image::addGaussianNoise(double mean, double stddev) {
  // Create a matrix to hold the Gaussian noise
  cv::Mat image = _image;
  cv::Mat noise(image.size(), image.type());
  // Generate Gaussian noise
  cv::randn(noise, cv::Scalar(mean), cv::Scalar(stddev));

  // Add noise to the original image
  for (int row = 0; row < image.rows; row++) {
    for (int col = 0; col < image.cols; col++) {
      for (int channel = 0; channel < image.channels(); channel++) {
        int val = image.at<cv::Vec3b>(row, col)[channel] +
                  noise.at<cv::Vec3b>(row, col)[channel];
        image.at<cv::Vec3b>(row, col)[channel] = cv::saturate_cast<uchar>(val);
      }
    }
  }

  setter(image);
  std::cout << "Gaussiannoise is successfully added to the image! "
            << std::endl;
  cv::imshow("GaussianNoise image", image);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * addSaltAndPepperNoise - Adds salt and pepper noise to an image
 * @noiseRatio: Proportion of the image pixels to be affected by the noise
 * @blackValue: The intensity value to be used for pepper noise
 * @whiteValue: The intensity value to be used for salt noise
 *
 * This function is used to add salt-and-pepper noise to images.
 */
void Image::addSaltAndPepperNoise(double noiseRatio, int blackValue,
                                  int whiteValue) {
  cv::Mat image = _image;
  // Calculate the number of pixels to be affected by noise
  size_t amount =
      static_cast<int>(noiseRatio * image.total() * image.channels());
  for (int i = 0; i < amount; ++i) {
    // Randomly decide whether it's salt or pepper
    int row = std::rand() % image.rows;
    int col = std::rand() % image.cols;
    int channel = image.channels() == 1 ? 0 : std::rand() % image.channels();

    // Randomly decide if it's salt or pepper
    uchar noiseValue = std::rand() % 2 == 0 ? blackValue : whiteValue;

    // Add noise to the original image
    if (image.channels() == 1) {
      // For grayscale images
      image.at<uchar>(row, col) = noiseValue;
    } else { // For color images
      image.at<cv::Vec3b>(row, col)[channel] = noiseValue;
    }
  }

  setter(image);
  std::cout << "Saltnoise and Peppernoise are successfully added to the image! "
            << std::endl;
  cv::imshow("SaltAndPepperNoise image", image);
  cv::waitKey(0);
  cv::destroyAllWindows();
}

void Image::load(const std::string &path) { _image = cv::imread(path); }

void Image::save() const {
  // Ask the user if they want to save the image
  std::cout << "Do you want to save the image? (y/n): ";
  char userInput;
  std::cin >> userInput;

  if (userInput == 'y' || userInput == 'Y') {
    std::string outputPath = Menu::getOutputImagePath();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // User chooses to save the image
    std::string fileName;
    std::cout << "Enter the file name (e.g., 'myimage'): ";
    // input imagename
    std::cin >> fileName;

    std::string filePath = outputPath + fileName + ".jpg";
    bool isSaved = cv::imwrite(filePath, _image);

    if (isSaved) {
      std::cout << "Image saved successfully at " << filePath << std::endl;
    } else {
      std::cout << "Error: Image not saved!" << std::endl;
    }
  } else {
    // User chooses not to save
    std::cout << "Image not saved." << std::endl;
  }
}