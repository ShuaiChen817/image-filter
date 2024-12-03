#ifndef USERMENU_H
#define USERMENU_H

#include <iostream>
#include <string>

namespace Menu {

    // Function to display the menu options
    void displayMenu();

    // Function to get the input image path from the user
    std::string getInputImagePath();

    // Function to get the output image path from the user
    std::string getOutputImagePath();

} // namespace Menu

#endif // USERMENU_H
