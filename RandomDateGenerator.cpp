#include <iostream>
#include "RandomDateGenerator.h"

/*
g++ -std=c++11 RandomDateGenerator.cpp -o RandomDateGenerator
*/

int main() {
    // Create a new instance of the RandomDateGenerator class
    RandomDateGenerator dateGenerator("2022-01-01", "2022-12-31");

    // Generate a vector of 5 random dates
    std::vector<std::string> randomDates = dateGenerator.generateDates(5);

    // Print the random dates to the console
    std::cout << "Random Dates:" << std::endl;
    for (const auto& date : randomDates) {
        std::cout << date << std::endl;
    }

    return 0;
}
