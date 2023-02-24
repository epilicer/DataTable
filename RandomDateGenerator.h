/*
Random date generator using the C++11 chrono library that generates random 
dates between a given start and end time

RandomDateGenerator generator("2022-01-01", "2022-12-31");
std::string random_date = generator.generate_date();
std::cout << "Random date: " << random_date << std::endl;
*/

#include <chrono>
#include <random>
#include <iostream>

class RandomDateGenerator {
public:
    RandomDateGenerator(const std::string& start, const std::string& end) {
        start_tp_ = convert_to_timepoint(start);
        end_tp_ = convert_to_timepoint(end);
    }

    std::string generate_date() {
        // Get the duration range between the start and end timepoints
        auto duration_range = std::chrono::duration_cast<std::chrono::seconds>(end_tp_ - start_tp_).count();

        // Generate a random number between 0 and the duration range
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, duration_range);
        auto rand_seconds = std::chrono::seconds(dis(gen));

        // Add the random duration to the start timepoint to get the random date
        auto rand_tp = start_tp_ + rand_seconds;

        return convert_to_string(rand_tp);
    }

private:
    std::chrono::system_clock::time_point convert_to_timepoint(const std::string& date_str) {
        std::tm tm = {};
        std::istringstream ss(date_str);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    std::string convert_to_string(const std::chrono::system_clock::time_point& tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        return oss.str();
    }

    std::chrono::system_clock::time_point start_tp_;
    std::chrono::system_clock::time_point end_tp_;
};
